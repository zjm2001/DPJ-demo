#include <ioCC2530.h>
#include "LCD.h"
int adc_value,one=0,two=99 ,t=11;
//延时
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
            // 空循环，用于延时
        }
    }
}
int start_adc(unsigned char channel){
   ADCCON3 = (0X80 | 0X20 |channel);
   while((ADCCON1 &0x80) != 0x80);
  //读出数据
   adc_value = ADCH;
   adc_value= (adc_value << 8) | ADCL;
   adc_value=adc_value >> 2;
   return adc_value;
}
void main()
{
       
    LCD_Init();                      //oled 初始化  
    LCD_CLS();                      //屏全亮 
   LCD_welcome();
    //LCD_P8x16Str(95, 3, "81");
   // LCD_P8x16Str(40, 5, "30");
    //LCD_P8x16Str(95, 5, "14");
    while(1)
   
    {
     APCFG  |= 0x40;   //定义p0_7位口子//0100 0000
     one = start_adc(0x07);
     one=(10000-one)/100;
      delay_ms(50);
      APCFG  |= 0x00;   //定义p0_1位口子
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