#include <ioCC2530.h>
#include "LCD.h"
int adc_value,one=0,two=99 ,t=11;
//��ʱ
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
            // ��ѭ����������ʱ
        }
    }
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
void main()
{
       
    LCD_Init();                      //oled ��ʼ��  
    LCD_CLS();                      //��ȫ�� 
   LCD_welcome();
    //LCD_P8x16Str(95, 3, "81");
   // LCD_P8x16Str(40, 5, "30");
    //LCD_P8x16Str(95, 5, "14");
    while(1)
   
    {
     APCFG  |= 0x40;   //����p0_7λ����//0100 0000
     one = start_adc(0x07);
     one=(10000-one)/100;
      delay_ms(50);
      APCFG  |= 0x00;   //����p0_1λ����
     two= start_adc(0x00);
     two=two/100;
    
     t++;
     delay_ms(50);
     LCD_bl(40, 5, one);
     LCD_bl(40, 3, t);
     LCD_bl(95, 5, two);
        delay_ms(50);
    }
}   