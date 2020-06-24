#include <stdlib.h>

// macro defining the number of 0xCC's found in the .text section, over written by anti-debug.sh
#define count 1

extern volatile char* _start; // start of .text section, defined in ld linker script ( ld --verbose | less )
extern volatile char* __etext; // end of .fini section, also defined in ld liner script

void __attribute__((constructor)) detect_breakpoints(){
  int counter = 0;
  char* start = (char*)&_start;                             
  char* end = (char*)&__etext;                              
  unsigned char int3 = 0xCC;

  // check each byte of executable code for a possible int3, 0xCC, if so increment counter
  while(start != end){                                     
    if(((*(volatile unsigned*)start++) & 0xFF) == int3){     
      counter++;
    }
  }
  if(counter != count){
    exit(0); // exit program if a breakpoint is detected, maybe adjust to delete executable file instead??
  }
}
