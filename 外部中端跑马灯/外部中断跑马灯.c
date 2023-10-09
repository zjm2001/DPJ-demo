#include "iocc2530.h"
#define LED5 P1_3
#define LED6 P1_4
#define LED3 P1_0
#define LED4 P1_1

// ******************************************�ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}
//********************************************��ʼ��
void Init_Port(){
       P1SEL &= ~0x1b;        //0001  1011
       P1DIR |= 0x1b;
       P1 &= ~0x1b;          //��ȫ�ر�     
}
// ***********************************
void Led_con(){
  LED3 = 1;
  Delay(50000);
  LED4=1;
  Delay(50000);
   LED3 = 0;
  Delay(50000);
  LED4=0;
  Delay(50000);
}
//************************************* �ⲿ�жϳ�ʼ������
void Init_INTP(){
 IEN1 |= 0X20;          
 P0IEN |= 0X02;         
 IEN2 |=  0X10;      
 P1IEN |= 0X04;
 PICTL |= 0X01;
 PICTL |= 0X02;
 EA = 1;
 }
// *****�ⲿ�ж�0������
#pragma vector = P0INT_VECTOR   
__interrupt void Int0_Sevice(){
   LED5 = ~LED5;
   P0IFG &= ~0X02;  
   P0IF = 0;
}

// *****�ⲿ�ж�1������
#pragma vector = P1INT_VECTOR   
__interrupt void Int1_Sevice(){
   LED6 = ~LED6;
   P1IFG &= ~0X04;
   P1IF = 0;
}
void main(){
 Init_Port();
 Init_INTP();
  while(1){
   Led_con();
  }
}