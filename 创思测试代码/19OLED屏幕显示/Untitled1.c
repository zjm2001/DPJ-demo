#include <ioCC2530.h>
#include "LCD.h"
//延时
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
            // 空循环，用于延时
        }
    }
}
void main()
{
       
     int t = 15;
    LCD_Init();                      //oled 初始化  
    LCD_CLS();                      //屏全亮 
    LCD_welcome();
   
    LCD_P8x16Str(95, 3, "81");
    LCD_P8x16Str(40, 5, "30");
    LCD_P8x16Str(95, 5, "14");
    while(1)
   
    {
      t++;
       delay_ms(10); 
        LCD_bl(40, 3, t);
        
    }
}   