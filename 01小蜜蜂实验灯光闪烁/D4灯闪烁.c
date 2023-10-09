#include "iocc2530.h"
#define D4 P1_1     //宏定义D4口
// 延迟函数
void Delay(unsigned int t)
{
  while(t--);
}

//端口初始化函数
void Init_Prot(){
  P1SEL &= ~0x02;     //0000 0010 //取0设置1为通用i/o端口
  P1DIR |= 0x02;      //取1号位取1设置输出
  
}
//led闪烁函数
void Init_Led(){
  D4 =~D4;
  Delay(60000);
}

void main(){
  Init_Prot();
  while(1){
    Init_Led();
  }
}