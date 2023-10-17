#include <ioCC2530.h>
#define D1   P1_0	  //定义LED1为P10口控制
#define D2   P1_1	  //定义LED2为P11口控制
unsigned int count = 0;
unsigned int count1 = 0;
//初始化灯光
void Init_con(){
   // P1SEL默认都是通用io
    P1SEL &=~0X03;
    P1DIR |= 0x03; //P10、P11定义为输出  0000 0011
    D1 = 1;
    D2 = 1;
}
 //初始化定时器3倒计数模式
void Init_Timer3(){
  T3CC0=0X7D;  //设置倒计数的起始值125 计算得来
  T3IE = 1 ;   //设置定时器3的中断使能
  EA=1;        //打开总中断
  T3CTL = 0XFD;     //1111 1101   128下的分频倒计数模式
}

//定时器4的模模式
void Init_Timer4(){
  T4CC0=0X7D;  //设置倒计数的起始值125 计算得来
  T4IE = 1 ;   //设置定时器4的中断使能
  T4CCTL0 |= 0x04;      //使用模模式必须开启通道的比较模式
  EA=1;        //打开总中断
  T4CTL = 0XFE;     //1111 1110   128下的分频倒模模式
}

#pragma vector = T3_VECTOR
__interrupt void Timer3_Sevice(){
 count++;
 if(count == 1000){
  D1= ~D1;
  count=0;
 }
 T3CTL = 0XFD;  //倒计数模式进入中断后会停止需要重新开启
}

#pragma vector = T4_VECTOR
__interrupt void Timer4_Sevice(){
 count1++;
 if(count1 == 4000){
  D2= ~D2;
  count1=0;
 }
}

void main(){
   Init_con();
   Init_Timer3();
   Init_Timer4();
   while(1){}

}