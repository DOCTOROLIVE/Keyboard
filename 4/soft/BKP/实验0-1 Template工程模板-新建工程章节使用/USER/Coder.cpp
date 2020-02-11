//# include "sys.h"
//# include "usart.h"
# include "delay.h"
# include "led.h"
# include "key.h"
//# include "usb_lib.h"
//# include "hw_config.h"
//# include "usb_pwr.h"
//# include "timer.h"

int main(void) {
	delay_init(); // ��ʱ��ʼ��
	LED_Init(); // LED��ʼ��
	KeyInit(); // ������ʼ��

	delay_ms(300);
	//USB_Port_Set(0); // USB�ȶϿ�
	delay_ms(300);
	//USB_Port_Set(1); // USB�ٴ�����
	//USB_Interrupts_Config(); // USB����
	//Set_USBClock();
	//USB_Init();

	while (1) {
		u8 Buf[8] = {0, 0, 0, 0, 0, 0, 0, 0}, key = KeyScan();
		if (key & 1)
			Buf[0] = 1;
		if (key & 2)
			Buf[2] = 4;
		if (key & 4)
			Buf[3] = 6;
		if (key & 8)
			Buf[4] = 25;
		//Joystick_Send(Buf[0], Buf[1], Buf[2], Buf[3], Buf[4], Buf[5], Buf[6],
		//	Buf[7]);
	}
}
