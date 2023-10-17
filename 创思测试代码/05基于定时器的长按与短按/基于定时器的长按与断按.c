#include <ioCC2530.h>
#define D1   P1_0	  //����LED1ΪP10�ڿ���
#define D2   P1_1	  //����LED2ΪP11�ڿ���
#define s1   P0_1       //���尴��s1
unsigned int count = 0;  
unsigned char key = 0;
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}
//��ʼ���ƹ�Ͱ�ť
void Init_con(){
   P1SEL &=~0X03;   //����Ϊͨ��io��
   P1DIR |= 0x03; //P10��P11����Ϊ���  0000 0011
   D1=1;
   D2=1;  //���״̬
   
   //s1
   P0SEL &= ~0X02;
   P0DIR &= ~0x02;     //��P0_1��Ϊ���뷽��
   P0INP &= ~0x02;     //��P0_1����Ϊ������/����
   P2INP &= ~0x20;     //��P0_1����Ϊ������
}
//��ʼ����ʱ��

void Init_Timers(){
   T1CC0L = 0Xd4;  //�ڰ�λ
   T1CC0H = 0X30;  //�߰�λ
   T1CCTL0 |= 0x04;   //����ͨ�� 0 �ıȽ�ģʽ
   T1IE = 1;  //������ʱ��һ�ж�ʹ��
   EA= 1;  //���жϿ���
   T1CTL = 0X0E; //128 ��Ƶ��Ϊ��ʱ����ʱ��Դ������ģʽΪģģʽ

}

#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice(){
  if(key == 1){
      count++;
  }
}
//����ɨ�躯��
void Scon_Keys(){
  if(s1 == 0){
   Delay(200);
   if(s1 == 0){
    count=0; //�������������
    key=1;
    while(s1 == 0);
    key=0;
    if(count > 5){
     //��ʾ����
      D1= ~D1;
    }else{
     //��ʾ�̰�
       D2= ~D2;
    }
   }
  }
}
//������
void main(){
  Init_con();
 Init_Timers();
  while(1){
   Scon_Keys();
  }
}