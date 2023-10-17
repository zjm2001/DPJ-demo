#include <ioCC2530.h>
#define D1   P1_0	  //����LED1ΪP10�ڿ���
#define D2   P1_1	  //����LED2ΪP11�ڿ���
unsigned int count = 0;
unsigned int count1 = 0;
//��ʼ���ƹ�
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

//��ʱ��4��ģģʽ
void Init_Timer4(){
  T4CC0=0X7D;  //���õ���������ʼֵ125 �������
  T4IE = 1 ;   //���ö�ʱ��4���ж�ʹ��
  T4CCTL0 |= 0x04;      //ʹ��ģģʽ���뿪��ͨ���ıȽ�ģʽ
  EA=1;        //�����ж�
  T4CTL = 0XFE;     //1111 1110   128�µķ�Ƶ��ģģʽ
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