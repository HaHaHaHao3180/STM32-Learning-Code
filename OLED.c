#include "stm32f10x.h"// Device header
#include"Delay.h"//延时函数头文件
#include"OLED.h"

int main(void)
 {
	 OLED_Init();
	 
	 
	 OLED_ShowString(1,1,"Hi!I'm zhanghao.");
	 Delay_s(2);
	 OLED_ShowHexNum(2,1,0X4F5DA2,6);
	 Delay_s(2);
	 OLED_ShowBinNum(3,1,0X208,12);
	 OLED_ShowBinNum(4,1,0X522,12);
	 Delay_s(3);
	 OLED_Clear();
	 OLED_ShowString(1,1,"It means");
	 OLED_ShowString(2,4,"I Love you");
	 OLED_ShowString(3,5,"forever");
	 Delay_s(5);
	 OLED_Clear();
	 OLED_ShowString(1,6,"***  ***");
	 OLED_ShowString(2,5,"**********");
     OLED_ShowString(3,6,"********");
	 OLED_ShowString(4,7,"******");
	 Delay_ms(800);
	 OLED_Clear();
     OLED_ShowString(1,6,"********");
     OLED_ShowString(2,7,"******");	 
     OLED_ShowString(3,8,"****");
	 OLED_ShowString(4,9,"**");
     Delay_ms(500);
	 OLED_Clear();
	 
	while(1)
	 {
		 
	 }
 }
