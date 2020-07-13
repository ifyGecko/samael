#include <stdlib.h>
#include <stdio.h>

#define fwd_head_mv '>'
#define bck_head_mv '<'
#define inc_at_head '+'
#define dec_at_head '-'
#define print_at_head '.'
#define start_loop '['
#define end_loop ']'

char* head;

void ebfin_init(unsigned int tape_size){
  head = (char*)calloc(tape_size, sizeof(char));
}

void ebfin_halt(){
  free(head);
}

void ebfin_eval(char* c){
  for(int i = 0 ; c[i] != '\0' ; ++i){
    if(c[i] == fwd_head_mv) ++head;
    else if(c[i] == bck_head_mv) --head;
    else if(c[i] == inc_at_head) ++*head;
    else if(c[i] == dec_at_head) --*head;
    else if(c[i] == print_at_head) putchar(*head);
    else if(c[i] == start_loop){
      if(*head == 0){
	int j = 1;
	while(j > 0){
	  i++;
	  if(c[i] == '[') j++;
	  if(c[i] == ']') j--;
	}
      }
    }
    else if(c[i] == end_loop){
      if(*head != 0){
	int j = 1;
	while(j > 0){
	  i--;
	  if(c[i] == '[') j--;
	  if(c[i] == ']') j++;
	}
      }
    }
  }
}
