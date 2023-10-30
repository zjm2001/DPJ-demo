#include <ioCC2530.h>
#define D1   P1_0	  //����LED1ΪP10�ڿ���
#define D2   P1_1	  //����LED2ΪP11�ڿ���
unsigned char dat;
unsigned char key=0;
//��ʼ���ƹ�Ͱ����ĺ���
void Init_con(){
   // P1SELĬ�϶���ͨ��io
    P1SEL &=~0X03;
    P1DIR |= 0x03; //P10��P11����Ϊ���  0000 0011
    D1 = 1;
    D2 = 1;  
}
//�л�ʱ�ӵ�ѡ����
void Set_Click(unsigned char clk){
  if(clk==16){
    //�л���16HMz
    CLKCONCMD |= 0x40;        
    while(!(CLKCONSTA & 0x40));    
    CLKCONCMD |= 0x01;    
  }else if(clk == 32){
    //�л���32HMz
    CLKCONCMD &= ~0x40;        
    while(CLKCONSTA & 0x40);    
    CLKCONCMD &= ~0x07;     
  }
}
void Init_uart0(){
  PERCFG &= ~0X01;    //��ʼ����ʱ��1ͨ��0������ӳ�䱸��λ��1
  P0SEL |= 0X0C;   // 0000 1100
  U0BAUD = 216;
  U0GCR = 11;
  U0UCR |= 0X80;
  U0CSR |=  0XC0;
  //ʹ���ж����Ϳ���λ
  UTX0IF = 0;  //�����TX�����жϱ�־
  URX0IF = 0;  //�����TX�����жϱ�־
  URX0IE = 1;  //�����ж�ʹ�ܱ�־λ  IEN0�ĵ�2λ(��λѰַ)
  EA = 1;      //���ж�
}
//���ͺ���
void UR0_SendByte(unsigned char dat){
   U0DBUF = dat;
   while(UTX0IF == 0);  //�ȴ�TX�жϱ�־�������ݷ������ 
   UTX0IF = 0;           //���TX�жϱ�־��׼����һ�η���
}
void UR0_SendString(unsigned char * str)
{
  while(*str != '\0')       //����һ���ַ���
  {
    UR0_SendByte(*str++);    //��������ַ����е��ֽ�
  }
}
//�����жϺ���
#pragma vector = URX0_VECTOR
__interrupt void se_URX0() {
  dat =U0DBUF;
  key=1;
 
}
//led ��ʾ����
void led_run(){
  switch(dat){
  case 0XA1:
    D1=0;
    UR0_SendString("D1��");
    break;
  case 0XA2:
    D1=1;
    UR0_SendString("D1��");
    break;
  case 0XB1:
    D2=0;
    UR0_SendString("D2��");
    break;
  case 0XB2:
    D2=1;
    UR0_SendString("D2��");
    break;
  default:
     UR0_SendString("����");
     break;
  }
}
//������
void main(){
  Set_Click(32);  //����32
  Init_con();
  Init_uart0(); //���ڳ�ʼ��
  while(1){
    if(key==1){
      key=0;
      led_run();
    }
  }
  
}