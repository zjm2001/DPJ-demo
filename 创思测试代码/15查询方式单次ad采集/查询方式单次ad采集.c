#include <ioCC2530.h>
#include "stdio.h"
unsigned int adc_value;
unsigned char str[64];
void Init_Port(){
 P1SEL &= ~0X03;   //����ͨ��i/o��      
 P1DIR |= 0X03;    //��Ϊͨ��i/oʱ������˿�
 P1 |=0x03;       //�ƹعر�״̬
}
void Set_Click(unsigned char clk){
  if(clk==16){
    CLKCONCMD |= 0x40;        
    while(!(CLKCONSTA & 0x40));    
    CLKCONCMD |= 0x01;    
  }else if(clk == 32){
    CLKCONCMD &= ~0x40;        
    while(CLKCONSTA & 0x40);    
    CLKCONCMD &= ~0x07;     
  }
}
void Init_uart0(){
  PERCFG &= ~0X01;    
  P0SEL |= 0X0C;   
  U0BAUD = 216;
  U0GCR = 11;
  U0UCR |= 0X80;
  U0CSR |=  0XC0;
  UTX0IF = 0;  //�����TX�����жϱ�־
  URX0IF = 0;  //�����TX�����жϱ�־
  URX0IE = 1;  //�����ж�ʹ�ܱ�־λ  IEN0�ĵ�2λ(��λѰַ)
  EA = 1;      //���ж�
}
void UR0_SendByte(unsigned char dat){
   U0DBUF = dat;
   while(UTX0IF == 0);  //�ȴ�TX�жϱ�־�������ݷ������ 
   UTX0IF = 0;           //���TX�жϱ�־��׼����һ�η���
}
void UR0_SendString(unsigned char * str){
  while(*str != '\0')       //����һ���ַ���
  {
    UR0_SendByte(*str++);    //��������ַ����е��ֽ�
  }
}
void init_adc(){
   APCFG  |= 0x10;   //����p0_4λ����//0001 0000
   
}
void init_wdt(){
   WDCTL = 0X0C; 
}
void  start_adc(){
   ADCCON3 = (0X80 | 0X20 |0X04);
   while((ADCCON1 &0x80) != 0x80);
  //��������
   adc_value = ADCH;
   adc_value= (adc_value << 8) | ADCL;
   adc_value=adc_value >> 2;
   // adc_value=10000-adc_value;
  // adc_value=adc_value/100;
   sprintf((char *)str,"ain4���������:%d\r\n",adc_value);
   UR0_SendString(str);
}
//������
void main(){
  Init_Port();
  Set_Click(32);  //����32
  Init_uart0(); //���ڳ�ʼ��
  init_adc();
  init_wdt();
  while(1){
    
    if(WDTIF == 1){
     WDTIF = 0;
     start_adc();
    }
    if(adc_value<30){
    P1_0=0;  //����
    }else{
     P1_0=1;
    }
    
   
  }
  
}