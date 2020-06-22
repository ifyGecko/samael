#include <stdio.h>
#include <stdlib.h>

extern volatile char* _start;
extern volatile char* __etext;

void __attribute__((constructor)) detect_breakpoints(){                        
  char* start = (char*)&_start;                             
  char* end = (char*)&__etext;                              
  volatile unsigned char int3 = 0x66;
  
  while(start != end) {                                     
    if(((*(volatile unsigned*)start++) & 0xFF) == (int3 + int3)){     
      exit(0);
    }
  }
}
