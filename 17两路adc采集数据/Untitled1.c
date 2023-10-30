#include <ioCC2530.h>
#include "stdio.h"
#include "DHT11.h"
unsigned int adc_value,one=0,two=99;
unsigned char count = 0;
unsigned char str[64];
//��ʱ
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
            // ��ѭ����������ʱ
        }
    }
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


//-------------------------
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
    count++;
  
  }
int start_adc(unsigned char channel){
   ADCCON3 = (0X80 | 0X20 |channel);
   while((ADCCON1 &0x80) != 0x80);
  //��������
   adc_value = ADCH;
   adc_value= (adc_value << 8) | ADCL;
   adc_value=adc_value >> 2;
   return adc_value;
}

//������
void main(){
  uchar temp[3]; 
  uchar humidity[3];
  Set_Click(32);  //����32
  Init_uart0(); //���ڳ�ʼ��
  Init_Timer1();
  while(1){
    if(count==10){
      APCFG  |= 0x40;   //����p0_7λ����//0100 0000
      one = start_adc(0x07);
    }else if(count==20){
     APCFG  |= 0x01;   //����p0_1λ����
     two= start_adc(0x01);
     
    }else if(count == 30){
    sprintf((char *)str,"���������:%d  %d  \r\n",one,two);
    UR0_SendString(str);
     count=0;
    }
    
   DHT11();//��ȡ��ʪ��
   temp[0]=wendu_shi+0x30; 
   temp[1]=wendu_ge+0x30; 
   humidity[0]=shidu_shi+0x30; 
   humidity[1]=shidu_ge+0x30;
    int number,number2;
    int tens = temp[0] - '0';  // ��ʮλ�� ASCII ��ת��Ϊ����
    int ones = temp[1] - '0';  // ����λ�� ASCII ��ת��Ϊ����
    number = (tens * 10) + ones;  // ����õ����յ���ֵ
    int tens2 = humidity[0] - '0';  // ��ʮλ�� ASCII ��ת��Ϊ����
    int ones2 = humidity[1] - '0';  // ����λ�� ASCII ��ת��Ϊ����
    number2 = (tens2 * 10) + ones2;  // ����õ����յ���ֵ
    sprintf((char *)str,"���������:%d  %d  \r\n",number,number2);
    UR0_SendString(str);
    delay_ms(100);
        
  }
  
}