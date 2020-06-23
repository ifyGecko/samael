#include <stdio.h>
#include <stdlib.h>

#define count 1

extern volatile char* _start;
extern volatile char* __etext;

void __attribute__((constructor)) detect_breakpoints(){
  int counter = 0;
  char* start = (char*)&_start;                             
  char* end = (char*)&__etext;                              
  unsigned char int3 = 0xCC;
  
  while(start != end) {                                     
    if(((*(volatile unsigned*)start++) & 0xFF) == int3){     
      counter++;
    }
  }
  if(counter != count){
    exit(0);
  }
}
