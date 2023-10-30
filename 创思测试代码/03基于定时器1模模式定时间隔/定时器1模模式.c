#include <ioCC2530.h>
#define D1   P1_0	  //定义LED1为P10口控制
#define D2   P1_1	  //定义LED2为P11口控制
//灯光初始化
//===========初始化
void Init_Port(){
 P1SEL &= ~0X03;   //设置通用i/o口      
 P1DIR |= 0X03;    //作为通用i/o时的输出端口
 P1 |=0x03;       //灯关关闭状态
}
//-------------------------
//初始化定时器
void Init_Timer1(){
  //1.设置最大计数器值 0x30d4  0.1s(先低八位再高八位)
   T1CC0L = 0Xd4;
   T1CC0H = 0X30;
  //2.开启通道0的比较模式因为这是中断一的模模式
   T1CCTL0 |=0X04;
  //3.使能定时器响应中断控制
     T1IE = 1; //开启定时器一中断
     EA=1;     //开启总中断
  //4.启动定时器
     T1CTL = 0X0E; //128 分频作为定时器的时钟源，工作模式为模模式
}

 unsigned char count = 0;
//定时器1服务函数
#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice(){
    //清除定时器1通道0中断标志(可写可不写会自动清除)
    //T1STAT &= ~0x01;
    count++;
    if(count == 10){
      //一秒钟
     D1 = 0;
    }
    if(count == 40){
      //四秒亮灯2
     D2 = 0;
     
    }
    if(count == 50){
     //五秒两个等都熄灭且计数从新开始
      D1=1;
      D2=1;
      count= 0; //清零
    }
   
  }
//-------------------------

void main(){
  Init_Port();
  Init_Timer1();
  while(1){
  }
}