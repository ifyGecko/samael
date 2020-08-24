#ifndef OBFUSCATOR_H
#define OBFUSCATOR_H

volatile int int0 = 8340;
volatile int int1 = 2983;
volatile int int2 = 6243;
volatile int int3 = 2398;
volatile int int4 = 9483;

volatile char char0 = 'd';
volatile char char1 = 'e';
volatile char char2 = 'h';
volatile char char3 = 'l';
volatile char char4 = 'v';

volatile float float0 = 0.23432;
volatile float float1 = 943.2348;
volatile float float2 = 223.23432;
volatile float float3 = 984.8283;
volatile float float4 = 49.9949;

volatile double double0 = 4324.23432;
volatile double double1 = 84844.4322;
volatile double double2 = 99373.22;
volatile double double3 = 575757.233;
volatile double double4 = 383893.33333;

volatile int zero = 0;
volatile int one = 1;

void __attribute__((naked)) foo_0(){
  asm volatile(".byte 0x90\n\t"
	       ".byte 0x90\n\t");
}

void __attribute__((always_inline)) static inline foobar_0(){
  asm volatile(".byte 0x48\n\t"
	       ".byte 0xb8\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xeb\n\t"
	       ".byte 0x0f\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0x48\n\t"
	       ".byte 0x31\n\t"
	       ".byte 0xc0\n\t"
	       ".byte 0xeb\n\t"
	       ".byte 0xf7\n\t"
	       ".byte 0xe8\n\t"
	       ".byte 0x10\n\t"
	       ".byte 0x25\n\t"
	       ".byte 0x00\n\t"
	       ".byte 0x04\n\t"
	       ".byte 0x00\n\t"
	       ".byte 0x00\n\t");  
}

void __attribute__((always_inline)) static inline foobar_1(){
  asm volatile(".byte 0x48\n\t"
	       ".byte 0xb8\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xeb\n\t"
	       ".byte 0x0f\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0x48\n\t"
	       ".byte 0x31\n\t"
	       ".byte 0xc0\n\t"
	       ".byte 0xeb\n\t"
	       ".byte 0xf7\n\t"
	       ".byte 0xe8\n\t"
	       ".byte 0x10\n\t"
	       ".byte 0x25\n\t"
	       ".byte 0x00\n\t"
	       ".byte 0x04\n\t"
	       ".byte 0x00\n\t"
	       ".byte 0x00\n\t");
}

void __attribute__((always_inline)) static inline foobar_2(){
  asm volatile(".byte 0x48\n\t"
	       ".byte 0xb8\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xeb\n\t"
	       ".byte 0x0f\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0x48\n\t"
	       ".byte 0x31\n\t"
	       ".byte 0xc0\n\t"
	       ".byte 0xeb\n\t"
	       ".byte 0xf7\n\t"
	       ".byte 0xe8\n\t"
	       ".byte 0x10\n\t"
	       ".byte 0x25\n\t"
	       ".byte 0x67\n\t"
	       ".byte 0x4f\n\t"
	       ".byte 0xf4\n\t"
	       ".byte 0x99\n\t");
}

void __attribute__((always_inline)) static inline foobar_3(){
  asm volatile(".byte 0x48\n\t"
	       ".byte 0xb8\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xeb\n\t"
	       ".byte 0x0f\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0x48\n\t"
	       ".byte 0x31\n\t"
	       ".byte 0xc0\n\t"
	       ".byte 0xeb\n\t"
	       ".byte 0xf7\n\t"
	       ".byte 0xe8\n\t"
	       ".byte 0x10\n\t"
	       ".byte 0x25\n\t"
	       ".byte 0x33\n\t"
	       ".byte 0x23\n\t"
	       ".byte 0x87\n\t"
	       ".byte 0xff\n\t");
}

void __attribute__((always_inline)) static inline foobar_4(){
  asm volatile(".byte 0x48\n\t"
	       ".byte 0xb8\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xeb\n\t"
	       ".byte 0x0f\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0xff\n\t"
	       ".byte 0x48\n\t"
	       ".byte 0x31\n\t"
	       ".byte 0xc0\n\t"
	       ".byte 0xeb\n\t"
	       ".byte 0xf7\n\t"
	       ".byte 0xe8\n\t"
	       ".byte 0x10\n\t"
	       ".byte 0x32\n\t"
	       ".byte 0x13\n\t"
	       ".byte 0x11\n\t"
	       ".byte 0x09\n\t"
	       ".byte 0x90\n\t");
}

void func0(){
  volatile int a = 66;
  volatile int b = 44;
  a+=b;
  if(zero){
    b-=12321;
    a+=b;
    a*=b;
    b+=(a%32);
    foobar_1();
    volatile char b[5] = { 'a', 'k', 'f', 'w', 'f' };
    for(int i = 0; i < 5; ++i){
      b[i]+=32;
      foobar_4();
    }
  }
  b-=a%10;
  b+=b;
  a*=2;
}

void func1(){
  volatile int i = int0 += 999;
  volatile int j = 100 % 543 + int3;
  while(zero){
    foobar_2();
    volatile char a = 'j';
    volatile int v = 324532 - char2;
    v += a;
    foobar_1();
  }
  volatile int a = 13;
  if(zero){
    foobar_4();
    volatile int h = 77;
    if(char0^h == float2){
      volatile char p[7] = { 'f', 't', 'q', 'y', 'z', 'a', 'p' };
      foobar_3();
      for(int j = 0; j < 7; ++j){
	foobar_4();
	p[j]^=2;
	p[j]-=2;
	p[j]*=3;
      }
    }
  }else{
    volatile float l = 111.9403;
    volatile char m = 'm';
    l = j * l + m;
  }
  a += int3^char0;
}

void func2(){
  volatile int a = 24532 - char4;
  while(zero){
    if(a == 2*zero){
      volatile int b = 23 + char1;
      b += a;
      foobar_2();
      b += 888;
      foobar_0();
    }
  }
  if(zero){
    foobar_3();
    a = 3214 / 99;
  }
}

void func3(){
  volatile int a = 3;
  volatile char b = '*';
  if(zero){
    foobar_1();
    a = 2304;
    foobar_2();
    foobar_3();
  }
  a = b = a * 24839 * b;
}

void func4(){
  volatile int a = 3;
  if(zero){
    foobar_4();
    a = 2090;
    foobar_0();
  }
  a = 8282 % 23;
}

#endif
