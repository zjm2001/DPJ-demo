#include <ioCC2530.h>
#define LED1   P1_0	  //����LED1ΪP10�ڿ���
#define LED2   P1_1	  //����LED2ΪP11�ڿ���
#define LED3   P0_4	  //����LED3ΪP04�ڿ���
unsigned int i;
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}
//��ʼ���ƹ�Ĵ���
void Init_led(){
   P1DIR |= 0x13; //P10��P11����Ϊ���
   P0DIR |= 0x10; //P04����Ϊ���
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;	    //LED�Ƴ�ʼ��Ϊ��
}

//�ƹ��⺯��
void led(){
  LED1 = 0;
  LED2 = 0;
  LED3 = 0;	//ȫ��
  Delay(60000);
  Delay(60000);
  LED1 = 1;
  LED2 = 1;
  LED3 = 1;	    //LED�Ƴ�ʼ��Ϊ��
  Delay(60000);
  Delay(60000);
  
}

//���Ź���ʼ��

void Init_WDT(){
  WDCTL = 0x08;      // 0000 1000���Ź�ģʽһ����
  
}
//ι�����к���(���򵽴�1s��������)
void Feed_dog(){
  WDCTL |= 0xa0;
  WDCTL |= 0x50;
}
//��ι���ĵƹ�չʾ
void Shan_dog(){
    LED1 = 0;
    Delay(60000);
    Delay(60000);
    LED1 = 1;
    Delay(60000);
    Delay(60000);
    Feed_dog();
 
}
//����ι���ĵƹ�չʾ
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
    
    //��������״̬��ȫ����ȫ��   Ȼ��һ����˸8��  2����˸��1������������¿�ʼ����
  }
}