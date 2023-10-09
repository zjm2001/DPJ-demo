#include "iocc2530.h"
#define sw2 P0_1
unsigned char F_led = 1;
unsigned int count = 0;
// 延迟函数
void Delay(unsigned int t)
{
  while(t--);
}
//初始化
void Init_Port(){
       P1SEL &= ~0x1b;        //0001  1011
       P1DIR |= 0x1b;
       P1 &= ~0x1b;          //灯全关闭
      
       P0SEL &= ~0X02;  //配置p0的端口1置0为通用i/0端口
       P0DIR &= ~0X02;  //输入状态
       P0INP &= ~0x02;   // 配置上拉/下拉
       P2INP &= ~0X20;  //配置上拉
         
}

// 初始化检测灯的好坏
void Led_con(){
   P1 |= 0x1b; //所有灯全亮
   Delay(60000);
   Delay(60000);
   P1 &= ~0x1b;   //全灭
}

//led亮灯
void Led(){
 Delay(300);
 if(F_led == 1){
  count++;
 }
 
 if(count == 1){
  P1 = 0x02;      //0000 0010  d4灯亮
 }
 else if(count == 201){
  P1 = 0x01;      //0000 0001  d3灯亮
 }
 else if(count == 401){
    P1 = 0x10;      //0001 0000  d6灯亮
 }
 else if(count == 601){
    P1 = 0x08;      //0000 1000  d5灯亮
 }
 else if(count == 801){
     count=0;
 }
}

//按键检测函数
void keys(){
  if(sw2 == 0){
    Delay(200);
    if(sw2 == 0){
      while(sw2 == 0){
      Led();
      }
      if(F_led == 0){
        F_led = 1;
      }else if(F_led == 1){
         F_led = 0;
      }
    }
  }
}
void main(){
 Init_Port();
 Led_con();
  while(1){
    Led();
    keys();
  }
}