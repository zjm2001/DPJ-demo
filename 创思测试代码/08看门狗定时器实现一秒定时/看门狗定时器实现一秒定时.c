#include <ioCC2530.h>
#define D1   P1_0	  //定义LED1为P10口控制
#define D2   P1_1	  //定义LED2为P11口控制
//初始化灯光
void Init_con(){
   // P1SEL默认都是通用io
    P1SEL &=~0X03;
    P1DIR |= 0x03; //P10、P11定义为输出  0000 0011
    D1 = 1;
    D2 = 1;
}
//看门狗中断寄存器初始化
void Init_WDI(){
    WDCTL =0x0c;      //0000 1100   设置为定时器模式时间间隔1s 
    IEN2  |= 0X20;    //0010 0000   IEN2的第五位是看门狗定时器的中断使能(不可位寻址)
    EA = 1;
}

#pragma vector = WDT_VECTOR
__interrupt void WDI_Sevice(){
   WDTIF=0;  //手动清除寄存器
   D1 = ~D1;
}
void main(){
   Init_con();
   Init_WDI();
   while(1){}

}