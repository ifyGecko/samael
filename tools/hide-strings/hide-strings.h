#include <stdlib.h>
#include <stdio.h>

#define fwd_head_mv '>'
#define bck_head_mv '<'
#define inc_at_head '+'
#define dec_at_head '-'
#define print_at_head '.'
#define loop_start '['
#define loop_end ']'

char* head;

void ebfin_init(unsigned int tape_size){
  head = (char*)calloc(tape_size, sizeof(char));
}

void ebfin_halt(){
  free(head);
}

void ebfin_eval(char* c){
  for(int i = 0 ; c[i] != '\0' ; ++i){
    if(c[i] == '>') ++head;
    else if(c[i] == '<') --head;
    else if(c[i] == '+') ++*head;
    else if(c[i] == '-') --*head;
    else if(c[i] == '.') putchar(*head);
    else if(c[i] == '['){
      if(*head == 0){
	int j = 1;
	while(j > 0){
	  i++;
	  if(c[i] == '[') j++;
	  if(c[i] == ']') j--;
	}
      }
    }
    else if(c[i] == ']'){
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
