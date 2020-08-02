#include <stdlib.h>

static inline __attribute__((always_inline)) char* bf_eval(char* c){
  char* head = (char*)calloc(0xFF, sizeof(char));
  char* start = head;
  for(int i = 0 ; c[i] != '\0' ; ++i){
    if(c[i] == '>'){
      ++head;
    }else if(c[i] == '<'){
      --head;
    }else if(c[i] == '+'){
      ++*head;
    }else if(c[i] == '-'){
      --*head;
    }
  }
  return start;
}
