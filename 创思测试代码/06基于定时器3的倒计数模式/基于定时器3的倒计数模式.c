#include <ioCC2530.h>
#define D1   P1_0	  //����LED1ΪP10�ڿ���
#define D2   P1_1	  //����LED2ΪP11�ڿ���
unsigned int count = 0;
//��ʼ���ƹ�Ͱ����ĺ���
void Init_con(){
   // P1SELĬ�϶���ͨ��io
    P1SEL &=~0X03;
    P1DIR |= 0x03; //P10��P11����Ϊ���  0000 0011
    D1 = 1;
    D2 = 1;
}

 //��ʼ����ʱ��3������ģʽ
void Init_Timer3(){
  T3CC0=0X7D;  //���õ���������ʼֵ125 �������
  T3IE = 1 ;   //���ö�ʱ��3���ж�ʹ��
  EA=1;        //�����ж�
  T3CTL = 0XFD;     //1111 1101   128�µķ�Ƶ������ģʽ
}
#pragma vector = T3_VECTOR
__interrupt void Timer3_Sevice(){
 count++;
 if(count == 1000){
  D1= ~D1;
  count=0;
 }
 T3CTL = 0XFD;  //������ģʽ�����жϺ��ֹͣ��Ҫ���¿���
}

void main(){
   Init_con();
   Init_Timer3();
   while(1){}

}

