#include <ioCC2530.h>
#define D1   P1_0	  //����LED1ΪP10�ڿ���
#define D2   P1_1	  //����LED2ΪP11�ڿ���
//��ʼ���ƹ�
void Init_con(){
   // P1SELĬ�϶���ͨ��io
    P1SEL &=~0X03;
    P1DIR |= 0x03; //P10��P11����Ϊ���  0000 0011
    D1 = 1;
    D2 = 1;
}
//���Ź��жϼĴ�����ʼ��
void Init_WDI(){
    WDCTL =0x0c;      //0000 1100   ����Ϊ��ʱ��ģʽʱ����1s 
    IEN2  |= 0X20;    //0010 0000   IEN2�ĵ���λ�ǿ��Ź���ʱ�����ж�ʹ��(����λѰַ)
    EA = 1;
}

#pragma vector = WDT_VECTOR
__interrupt void WDI_Sevice(){
   WDTIF=0;  //�ֶ�����Ĵ���
   D1 = ~D1;
}
void main(){
   Init_con();
   Init_WDI();
   while(1){}

}