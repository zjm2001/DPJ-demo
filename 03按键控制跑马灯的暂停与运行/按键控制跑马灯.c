#include "iocc2530.h"
#define sw2 P0_1
unsigned char F_led = 1;
unsigned int count = 0;
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}
//��ʼ��
void Init_Port(){
       P1SEL &= ~0x1b;        //0001  1011
       P1DIR |= 0x1b;
       P1 &= ~0x1b;          //��ȫ�ر�
      
       P0SEL &= ~0X02;  //����p0�Ķ˿�1��0Ϊͨ��i/0�˿�
       P0DIR &= ~0X02;  //����״̬
       P0INP &= ~0x02;   // ��������/����
       P2INP &= ~0X20;  //��������
         
}

// ��ʼ�����Ƶĺû�
void Led_con(){
   P1 |= 0x1b; //���е�ȫ��
   Delay(60000);
   Delay(60000);
   P1 &= ~0x1b;   //ȫ��
}

//led����
void Led(){
 Delay(300);
 if(F_led == 1){
  count++;
 }
 
 if(count == 1){
  P1 = 0x02;      //0000 0010  d4����
 }
 else if(count == 201){
  P1 = 0x01;      //0000 0001  d3����
 }
 else if(count == 401){
    P1 = 0x10;      //0001 0000  d6����
 }
 else if(count == 601){
    P1 = 0x08;      //0000 1000  d5����
 }
 else if(count == 801){
     count=0;
 }
}

//������⺯��
void keys(){
  if(sw2 == 0){
    Delay(200);
    if(sw2 == 0){
      while(sw2 == 0){
      Led();
      }
      if(F_led == 0){
        F_led = 1;
      }else if(F_led == 1){
         F_led = 0;
      }
    }
  }
}
void main(){
 Init_Port();
 Led_con();
  while(1){
    Led();
    keys();
  }
}