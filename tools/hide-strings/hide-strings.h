#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* head;
char* start;

void __attribute__((constructor)) bf_init(){
  head = (char*)malloc(0xFF * sizeof(char));
  start = head;
}

static inline __attribute__((always_inline)) char* bf_eval(char* c){
  head = start;
  memset(head, 0, 0xFF);
  for(int i = 0 ; c[i] != '0' ; ++i){
    if(c[i] == '>') ++head;
    else if(c[i] == '<') --head;
    else if(c[i] == '+') ++*head;
    else if(c[i] == '-') --*head;
  }
  return start;
}
