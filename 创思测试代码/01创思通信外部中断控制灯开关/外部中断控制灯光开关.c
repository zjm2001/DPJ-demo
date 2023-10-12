#include "iocc2530.h"
#define D1 P1_0
#define D2 P1_1
// 延迟函数
void Delay(unsigned int t)
{
  while(t--);
}
//===========初始化
void Init_Port(){
 P1SEL &= ~0X03;   //设置通用i/o口      
 P1DIR |= 0X03;    //作为通用i/o时的输出端口
 P1 |=0x03;       //灯关关闭状态
}
void Init_INTP0(){
  //1.使能端口组的外部中断
  IEN1 |= 0x20;//开P0端口组中断  //IEN1可位寻址也可使用 P0IE=1
  //2.使能具体引脚的外部中断
  P0IEN |=0X02;
  //3.设置外部中断的信号触发类型
  PICTL |=0X01;
  //开启总中断
  EA =1;
  
}
//============
//p0口响应中断后的中断符函数
#pragma vector = P0INT_VECTOR
__interrupt void Service_INTP0(){
  //判断那个引脚触发的中断请求
  if((P0IFG & 0X02) ==  0X02){
    Delay(200);
    D1 = ~D1;
  }
  P0IFG=0;
  P0IF=0;
}

void main(){
  Init_Port();
  Init_INTP0();
  while(1){
    D2=0;
    Delay(60000);
    D2=1;
    Delay(60000);
 
  }
}