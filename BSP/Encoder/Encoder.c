#include "Encoder.h"
#include <string.h>
#include "stdio.h"

volatile int32_t Left_Count = 0;
volatile int32_t Right_Count = 0;

unsigned char Flag_2ms,
							Flag_6ms,
							Flag_20ms, 
							Flag_50ms; 

int16_t	 Encoder_left_out = 0,
		 Encoder_right_out = 0;

void Encoder_Get(){	
			static float low_pass = 0.7;
			int16_t Encoder_left = 0,
										 Encoder_right = 0;
	
	
			Encoder_left_out = Read_Speed(1);				 
			//Encoder_left_out = Encoder_left_out * low_pass + Encoder_left * (1 - low_pass);
			Left_Count = 0;
	
			Encoder_right_out = Read_Speed(2);
			//Encoder_right_out =Encoder_right_out Encoder_right_out * low_pass + Encoder_right * (1 - low_pass);
			Right_Count = 0;
   
//			printf("Encoder_left_out: %d\n",Encoder_left_out); 
//			printf("Encoder_right_out: %d\n",Encoder_right_out);
	
//	printf("Encoder_right_out: %d\n",(Encoder_right+Encoder_left)/2);
}


//void Encoder_count_clear(int32_t *count){
//		*count = 0;		
//}

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

//TIM0���жϷ�����
//void TIMER_0_INST_IRQHandler(void)
//{
//		unsigned char T_2ms;
//    unsigned char T_6ms;
//		unsigned char T_20ms;
//		unsigned char T_50ms;
//	
//    //��������˶�ʱ���ж�
//    switch( DL_TimerG_getPendingInterrupt(TIMER_0_INST) ){
//			case DL_TIMER_IIDX_ZERO://�����0����ж�
//					T_2ms ++;
//					T_6ms ++;
//					T_20ms ++;	
//					T_50ms ++;break;            
//			default:								//�����Ķ�ʱ���ж�
//            break;
//			} 
//		if(T_2ms == 2) { 
//			Flag_2ms = 1;
//		  T_2ms = 0;   
//		}
//		if(T_6ms == 6) {
//			Flag_6ms = 1;
//			T_6ms = 0;
//		}
//		if(T_20ms == 20) {
//			Flag_20ms = 1;
//			T_20ms = 0;
//		}
//		if(T_50ms == 50) {
//			Flag_50ms = 1;
//			T_50ms = 0;
//		}
//}
//�ⲿ�жϷ�����
void GROUP1_IRQHandler(void)
{
	uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB,GPIO_Encoder_PIN_Left_A_PIN | GPIO_Encoder_PIN_Right_A_PIN | GPIO_Encoder_PIN_Left_B_PIN | GPIO_Encoder_PIN_Left_B_PIN);
	
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



