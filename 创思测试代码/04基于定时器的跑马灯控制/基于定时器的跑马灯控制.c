#include <ioCC2530.h>
#define D1   P1_0	  //����LED1ΪP10�ڿ���
#define D2   P1_1	  //����LED2ΪP11�ڿ���
#define D3   P0_4	  //����LED3ΪP04�ڿ���
#define s1   P0_1
 unsigned char count = 0;
 unsigned char key = 0;
  unsigned char time = 0;
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}
//��ʼ���ƹ�Ͱ����ĺ���
void Init_con(){
   // P1SELĬ�϶���ͨ��io
    P1SEL &=~0X03;
    P1DIR |= 0x03; //P10��P11����Ϊ���  0000 0011
    P0SEL &= ~0X10;
    P0DIR |= 0x10; //P04����Ϊ��� 0001 0000
    D1 = 1;
    D2 = 1;
    D3 = 1;	    //LED�Ƴ�ʼ��Ϊ��
    //s1
   P0SEL &= ~0x02;     //��P0_1��Ϊͨ��I/O�˿� 
   P0DIR &= ~0x02;     //��P0_1��Ϊ���뷽��
   P0INP &= ~0x02;     //��P0_1����Ϊ������/����
   P2INP &= ~0x20;     //��P0_1����Ϊ������
    
}
 //��ʼ����ʱ��
void Init_Timer1(){
  
   T1CC0L = 0Xd4;
   T1CC0H = 0X30;
   T1CCTL0 |=0X04;
   T1IE = 1; //������ʱ��һ�ж�
   EA=1;     //�������ж�
   T1CTL = 0X0E; //128 ��Ƶ��Ϊ��ʱ����ʱ��Դ������ģʽΪģģʽ
}

#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice(){
  if(time == 1){
      count++;
  }

}

void led(){
  if(key == 1){
  //��һ��
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
    //�ڶ���
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
//����ɨ�躯��
void key_scan(){
  if(s1==0){
  Delay(200);
  if(s1 == 0){
   while(s1 == 0);
   time=1;//��ʼ�ۼ�count
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