#include "Encoder.h"

volatile int32_t Left_Count = 0;
volatile int32_t Right_Count = 0;

/**************
编码器
速度读取函数
入口参数为：编码器值
返回参数为：存入的速度
(由于编码器读到的原始数据都是距离，所以可以对其进行求微分，即差值除周期。)
**************/
int Read_Speed(int Encoder_Num)										//读取编码器速度
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

//TIM0的中断服务函数
void TIMER_0_INST_IRQHandler(void)
{
    //如果产生了定时器中断
    switch( DL_TimerG_getPendingInterrupt(TIMER_0_INST) )
    {
        case DL_TIMER_IIDX_ZERO://如果是0溢出中断
//            uart0_send_char(Right_Count);			
//            uart0_send_char(Left_Count);
			Left_Count = 0;
			Right_Count = 0;
            break;

			default://其他的定时器中断
            break;
    }
}

//外部中断服务函数
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



