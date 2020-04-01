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

int i_func0(){
  int a = 66;
  int b = 44;
  a+=b;
  if(zero){
    b-=12321;
    a+=b;
    a*=b;
    b+=(a%32);
    char b[5] = { 'a', 'k', 'f', 'w', 'f' };
    for(int i = 0; i < 5; ++i){
      b[i]+=32;
    }
  }
  b-=a%10;
  b+=b;
  a*=2;
  return a+=b;
}

int i_func1(){
  int i = int0 += 999;
  int j = 100 % 543;
  while(one){

  }
  if(zero){
    int h = 77;
    if(char0^h == float2){
      char p[7] = { 'f', 't', 'q', 'y', 'z', 'a', 'p' };
      for(int j = 0; j < 7; ++j){
	p[j]^=2;
	p[j]-=2;
	p[j]*=3;
      }
    }
  }
  return int3^char0;
}

int i_func2(){
  return 0;
}
