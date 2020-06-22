#include <stdio.h>
#include <stdlib.h>

#define count 1

extern volatile char* _start;
extern volatile char* __etext;

void __attribute__((constructor)) detect_breakpoints(){
  int counter = 0;
  char* start = (char*)&_start;                             
  char* end = (char*)&__etext;                              
  volatile unsigned char int3 = 0x66;
  
  while(start != end) {                                     
    if(((*(volatile unsigned*)start++) & 0xFF) == (int3 + int3)){     
      counter++;
    }
  }

  if(counter != count){
    printf("breakpoint detected!\n");
    exit(0);
  }
}
