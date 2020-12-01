#include "hw_config.h"
#include "usb_lib.h"
#include "usb_istr.h"

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
/* Private function prototypes ----------------------------------------------- */
/* Private functions --------------------------------------------------------- */
/*******************************************************************************
 * Function Name  : EP1_OUT_Callback.
 * Description    : EP1 OUT Callback Routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 ****************************************************************************** */
void EP1_IN_Callback(void) {
}

void EP1_OUT_Callback(void) {
	u8 DataLen; //����������ݵĳ���
	u8 DataBuffer[64]; //����������ݵĻ�����
	DataLen = GetEPRxCount(ENDP1); //��ȡ�յ��ĳ���
	PMAToUserBufferCopy(DataBuffer, ENDP1_RXADDR, DataLen); //��������
	SetEPRxValid(ENDP1); //���ö˵���Ч���Խ�����һ������
	if(DataLen==1) //�յ�һ�ֽڵ��������
	{
		//D0λ��ʾ���ּ��̵ƣ�D1λ��ʾ��д��ĸ������
		if(DataBuffer[0]&0x01)  //���ּ��̵���
		{
		// GPIOC->BSRR=(1<<6); //��LED3
		}
		else
		{
		//GPIOC->BRR=(1<<6); //��LED3
		}
		if(DataBuffer[0]&0x02) //��д��ĸ������
		{
		//GPIOC->BSRR=(1<<7); //��LED2
		}
		else
		{
		//GPIOC->BRR=(1<<7); //��LED2
		}
	}
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*** */
