#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"   
#include "ps2.h" 
#include "keyboard.h"
//https://wenku.baidu.com/view/0308d6890508763230121203.html


PS2dev kbd;

int main(void) {
	delay_init();	    	 //��ʱ������ʼ��	
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	// LCD_Init();			   	//��ʼ��LCD     
	kbd.keyboard_init();

	while (1) {
		unsigned char led;
		if (kbd.keyboard_handle(&led))
			LED1 = !LED1;

		//		LCD_ShowNum(2, 3, t, 6, 24);
		//		t++;
		//		POINT_COLOR = t;
		// delay_ms(100);
		//		if (t % 20 == 0) {
		//			LED0 = !LED0;
		//		}
	}
}
