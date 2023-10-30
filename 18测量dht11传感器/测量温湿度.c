#include <ioCC2530.h>
#include "DHT11.h"
#include "stdio.h"
#include "LCD.h"
unsigned char str[64];
unsigned int adc_value,one=0,two=99;

//��ʱ
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
            // ��ѭ����������ʱ
        }
    }
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
//ad����
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
    LCD_Init();                      //oled ��ʼ��  
    LCD_CLS();                      //��ȫ�� 
    LCD_welcome();
  Set_Click(32);  //����32
  Init_uart0(); //���ڳ�ʼ��
  while(1){

   DHT11();//��ȡ��ʪ��
//����ʪ�ȵ�ת�����ַ��� 
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
    //��һ��һ��ad�ɼ�
        APCFG  |= 0x04;   //����p0_2λ����//0000 0100
        one = start_adc(0x02);
        one=one%4000/10;
       delay_ms(100);
     //�ڶ����ɼ�
       APCFG  |= 0x01;   //����p0_1λ����
       two= start_adc(0x01);
       two=10000-two;
       two=two/100;
       delay_ms(100);
    //LCD_bl(40, 3, number);
   // LCD_P8x16Str(95, 3, "81");
    //LCD_P8x16Str(40, 5, "30");
    //LCD_P8x16Str(95, 5, "14");
   sprintf((char *)str,"%d  %d  %d  %d \r\n",number,number2,one,two);
   UR0_SendString(str);
   delay_ms(100);


  }
  
}