#include <ioCC2530.h>
#define D1   P1_0	  //定义LED1为P10口控制
#define D2   P1_1	  //定义LED2为P11口控制
#define D3   P0_4	  //定义LED3为P04口控制
#define s1   P0_1
 unsigned char count = 0;
 unsigned char key = 0;
  unsigned char time = 0;
// 延迟函数
void Delay(unsigned int t)
{
  while(t--);
}
//初始化灯光和按键的函数
void Init_con(){
   // P1SEL默认都是通用io
    P1SEL &=~0X03;
    P1DIR |= 0x03; //P10、P11定义为输出  0000 0011
    P0SEL &= ~0X10;
    P0DIR |= 0x10; //P04定义为输出 0001 0000
    D1 = 1;
    D2 = 1;
    D3 = 1;	    //LED灯初始化为灭
    //s1
   P0SEL &= ~0x02;     //将P0_1设为通用I/O端口 
   P0DIR &= ~0x02;     //将P0_1设为输入方向
   P0INP &= ~0x02;     //将P0_1配置为：上拉/下拉
   P2INP &= ~0x20;     //将P0_1配置为：上拉
    
}
 //初始化定时器
void Init_Timer1(){
  
   T1CC0L = 0Xd4;
   T1CC0H = 0X30;
   T1CCTL0 |=0X04;
   T1IE = 1; //开启定时器一中断
   EA=1;     //开启总中断
   T1CTL = 0X0E; //128 分频作为定时器的时钟源，工作模式为模模式
}

#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice(){
  if(time == 1){
      count++;
  }

}

void led(){
  if(key == 1){
  //第一次
    if(count == 10){
     D1=0;
    }else if(count == 20){
     D2=0;
    }else if(count == 30){
     D3=0;
    }else if(count == 40){
     time=0;
     count=0;
     D3=1;
     D1=1;
     D2=1;
    }
  }else if(key==2){
    //第二次
      if(count == 10){
     D3=0;
    }else if(count == 20){
     D2=0;
    }else if(count == 30){
     D1=0;
    }else if(count == 40){
     time=0;
     count=0;
     key=0;
     D3=1;
     D1=1;
     D2=1;
    }
  }
}
//按键扫描函数
void key_scan(){
  if(s1==0){
  Delay(200);
  if(s1 == 0){
   while(s1 == 0);
   time=1;//开始累计count
   if(key==0){
    key=1;
   }else if(key == 1){
    key=2;
   }
  }
  }

}
void main(){
  Init_con();
  Init_Timer1();
  while(1){
    key_scan();
    led();
  }
}