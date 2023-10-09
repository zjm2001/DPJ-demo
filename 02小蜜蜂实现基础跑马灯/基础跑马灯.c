#include "iocc2530.h"
// 延迟函数
void Delay(unsigned int t)
{
  while(t--);
}
//初始化
void Init_Port(){
       P1SEL &= ~0x1b;        //0001  1011
       P1DIR |= 0x1b;
}
//led亮灯
void Led(){
    unsigned char i;
  //设置pX端口
  // 0000 0010(0x02)   0000 0011(0x03)  0001 0011(0x13)   0001 1011(0x1b)  //依次开灯  4 3 6 5
  // 0001 1001(0x19)   0001 1000(0x18)  0000 1000(0x08)   0000 0000(0x00)  //依次熄灯  4 3 6 5
 unsigned stat[8]={0x02,0x03,0x13,0x1b,0x19,0x18,0x08,0x00};    
    for(i=0;i<8;i++)
    {
      P1=stat[i];
      Delay(60000);
      Delay(60000);
    }
}
void main(){
 Init_Port();
  while(1){
    Led();
  }
}