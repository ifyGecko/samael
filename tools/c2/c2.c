#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h>


#define port 1234
#define addr INADDR_ANY

void main(){
  int host_sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in host_addr;
  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(port);
  host_addr.sin_addr.s_addr = addr;
  bind(host_sock, (struct sockaddr *)&host_addr, sizeof(host_addr));
  listen(host_sock, 0);

  system("cd ../../payloads; make obfuscated; ls | grep .so > /tmp/tmp.txt");

  FILE *fp;
  char buff[255];
  int i = 0;
  
  fp = fopen("/tmp/tmp.txt", "r");
  fscanf(fp, "%s", buff);
  while(!feof(fp)){    
    printf("%d : %s\n", i++, buff);
    fscanf(fp, "%s", buff);
  }
  fclose(fp);
  
  
  int client_sock = accept(host_sock, NULL, NULL);
  if(client_sock > 0){
    
  }
}
