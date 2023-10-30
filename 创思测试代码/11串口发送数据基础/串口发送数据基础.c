#include <ioCC2530.h>
#define D1   P1_0	  //����LED1ΪP10�ڿ���
#define D2   P1_1	  //����LED2ΪP11�ڿ���

//�ƹ��ʼ��
void led_con(){
   P1SEL &=~0X03;   //����Ϊͨ��io��
   P1DIR |= 0x03; //P10��P11����Ϊ���  0000 0011
   D1=1;
   D2=1;  //���״̬ 
}
//���Ź�
void Init_WDT(){
  WDCTL = 0X0C;   //0000 1100
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
//===================================
void Init_uart0(){
   //1. io�����ŵ�����λ��
  PERCFG &= ~0X01;    //��ʼ����ʱ��1ͨ��0������ӳ�䱸��λ��1
  P0SEL |= 0X0C;   // 0000 1100
  // 2.����������
  U0BAUD = 216;
  U0GCR = 11;
  // 3. UART����
  U0UCR |= 0X80;
  //4. ������״̬�Ĵ���
  U0CSR |=  0XC0;
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
//===================================
//������
void main(){
  Set_Click(32);  //����32
  led_con();  //�ƹ��ʼ��
  Init_uart0(); //���ڳ�ʼ��
  Init_WDT();  //���Ź���ʼ��
  while(1){
    if(WDTIF == 1){
     D1=0;
     WDTIF = 0;
     UR0_SendString("���ͳɹ� ddd!!! \r\n");
     D1=1;
     
    }
  }
}