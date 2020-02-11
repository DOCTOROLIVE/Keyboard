#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"

int main(void) {		
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	LED_Init();		  		
	LED0=0;					//�ȵ������
  USB_Init();
  KEY_Init();
	
  while (1)
  {
    
				LED1=0;
			if(!KEY0)
        Joystick_Send(6),Joystick_Send(0);
			else LED0 = 1;
}
}
