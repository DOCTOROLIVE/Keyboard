#include "key.h"
#include "led.h"
#include <stdbool.h>
#include <system.h>
#include <altera_avalon_uart_regs.h>
#include <priv/alt_legacy_irq.h>

//static bool key_status[103];

void UART_Irq_Handler(void* isr_context) {
	alt_u8 rx_dat = IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);  //��ȡ��������
	// key_status[rx_dat & KEY_ID_MASK] = rx_dat & KEY_DOWN_MASK;
	// SET_LED(KEY2LED[rx_dat & KEY_ID_MASK], 0xffffffu*(rx_dat & KEY_DOWN_MASK));
//	printf("key: 0x%x\n", rx_dat);
	IOWR_ALTERA_AVALON_UART_STATUS(UART_0_BASE, 0x0);  //����жϱ�־�Ĵ���
}

void key_init(void) {
	IOWR_ALTERA_AVALON_UART_STATUS(UART_0_BASE, 0x0);  //����жϱ�־�Ĵ���
	alt_irq_register(UART_0_IRQ, NULL, UART_Irq_Handler);  //ע���ж�
	IOWR_ALTERA_AVALON_UART_CONTROL(UART_0_BASE, 0x0080);  //����UART�����ж�
}
