#include <ioCC2530.h>
#define LED1   P1_0	  //定义LED1为P10口控制
#define LED2   P1_1	  //定义LED2为P11口控制
#define LED3   P0_4	  //定义LED3为P04口控制
unsigned char key=1;  //定义一个开关一样的东西
// 延迟函数
void Delay(unsigned int t)
{
  while(t--){
  while(key == 0);
  }
}
//初始化灯光寄存器
void Init_led(){
   P1DIR |= 0x13; //P10、P11定义为输出
   P0DIR |= 0x10; //P04定义为输出
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;	    //LED灯初始化为灭
}
//中断使能初始化-----------------------------
void Init_INTP2(){
  //1.使能端口组的外部中断(p2_0)
   IEN2 |= 0x02;
  //2.使能具体引脚的外部中断
  P2IEN |=0X01;
  //3.设置外部中断的信号触发类型
  PICTL |=0X01;
  //开启总中断
  EA =1;
  
}
#pragma vector = P2INT_VECTOR
__interrupt void selev_init() 
{
  if((P2IFG & 0x01)== 0x01){
    if(key == 1){
     key=0;
    }else{
     key=1;
    }
  }
   P2IFG = 0; 
   P2IF = 0; 
}
//-------------------------------------
void led(){
   LED1 = 0;
    LED2 = 1;
    LED3 = 1;	
  Delay(60000);
  Delay(60000);
    LED1 = 1;
    LED2 = 0;
    LED3 = 1;	
  Delay(60000);
  Delay(60000);
    LED1 = 1;
    LED2 = 1;
    LED3 = 0;	
  Delay(60000);
  Delay(60000);

}
void main(){
  Init_led();
  Init_INTP2();
  while(1){
     led();
  }
}