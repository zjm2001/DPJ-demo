#include <ioCC2530.h>
#define LED1   P1_0	  //定义LED1为P10口控制
#define LED2   P1_1	  //定义LED2为P11口控制
#define LED3   P0_4	  //定义LED3为P04口控制
unsigned int i;
// 延迟函数
void Delay(unsigned int t)
{
  while(t--);
}
//初始化灯光寄存器
void Init_led(){
   P1DIR |= 0x13; //P10、P11定义为输出
   P0DIR |= 0x10; //P04定义为输出
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;	    //LED灯初始化为灭
}

//灯光检测函数
void led(){
  LED1 = 0;
  LED2 = 0;
  LED3 = 0;	//全亮
  Delay(60000);
  Delay(60000);
  LED1 = 1;
  LED2 = 1;
  LED3 = 1;	    //LED灯初始化为灭
  Delay(60000);
  Delay(60000);
  
}

//看门狗初始化

void Init_WDT(){
  WDCTL = 0x08;      // 0000 1000看门狗模式一秒钟
  
}
//喂狗序列函数(程序到达1s不会重置)
void Feed_dog(){
  WDCTL |= 0xa0;
  WDCTL |= 0x50;
}
//带喂狗的灯光展示
void Shan_dog(){
    LED1 = 0;
    Delay(60000);
    Delay(60000);
    LED1 = 1;
    Delay(60000);
    Delay(60000);
    Feed_dog();
 
}
//不带喂狗的灯光展示
void Shan(){
    LED2 = 0;
    Delay(60000);
    Delay(60000);
    LED2 = 1;
    Delay(60000);
    Delay(60000);
}
main(){
  Init_led();
  Init_WDT();
  led();
  while(1){
    for(i=0; i<8;i++){
      Shan_dog();
    }
     for(i=0; i<8;i++){
      Shan();
    }
    
    //程序运行状态先全亮再全灭   然后一灯闪烁8次  2灯闪烁到1秒程序重置重新开始运行
  }
}