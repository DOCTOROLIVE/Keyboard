#include "delay.h"

void delay_init(void) {
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

void delay_us(u32 nus) {
    SysTick->LOAD = nus * 9; // ʱ�����
    SysTick->VAL = 0x00; // ��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // ��ʼ����
    while ((SysTick->CTRL & 0x01) && !(SysTick->CTRL & (1 << 16))) {
    } // �ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // �رռ�����
    SysTick->VAL = 0X00; // ��ռ�����
}

void delay_ms(u32 nms) {
    while (nms--) {
        delay_us(1000);
    }
}
