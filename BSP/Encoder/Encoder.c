#include "Encoder.h"

volatile int32_t Left_Count = 0;
volatile int32_t Right_Count = 0;

/**************
������
�ٶȶ�ȡ����
��ڲ���Ϊ��������ֵ
���ز���Ϊ��������ٶ�
(���ڱ�����������ԭʼ���ݶ��Ǿ��룬���Կ��Զ��������΢�֣�����ֵ�����ڡ�)
**************/
int Read_Speed(int Encoder_Num)										//��ȡ�������ٶ�
{
	int value_1;
	switch(Encoder_Num)
	{
		case 1:
			value_1 = Left_Count;
			break;
		case 2:
			value_1 = Right_Count;
			break;
	}
	return value_1;
}





//�ⲿ�жϷ�����
void GROUP1_IRQHandler(void)
{
	uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB,GPIO_Encoder_PIN_Left_A_PIN | GPIO_Encoder_PIN_Right_A_PIN | 
	GPIO_Encoder_PIN_Left_B_PIN | GPIO_Encoder_PIN_Left_B_PIN);
	
	if(gpioB & GPIO_Encoder_PIN_Left_A_PIN)						
	{
		if(DL_GPIO_readPins(GPIO_Encoder_PORT,GPIO_Encoder_PIN_Left_B_PIN))
		{
			Right_Count--;
		}
		else 
		{
			Right_Count++;
		}
		DL_GPIO_clearInterruptStatus(GPIO_Encoder_PORT,GPIO_Encoder_PIN_Left_A_PIN);
	}
	
	if(gpioB & GPIO_Encoder_PIN_Right_A_PIN)						
	{
		if(DL_GPIO_readPins(GPIO_Encoder_PORT,GPIO_Encoder_PIN_Right_B_PIN))
		{
			Left_Count--;
		}
		else 
		{
			Left_Count++;
		}
		DL_GPIO_clearInterruptStatus(GPIO_Encoder_PORT,GPIO_Encoder_PIN_Right_A_PIN);
	}

}



