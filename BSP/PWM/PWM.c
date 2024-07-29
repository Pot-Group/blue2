#include "PWM.h"

/*
        电机B为右电机(TIMG12)                电机A为左电机(TIMG6)              
        BIN2：PA14                     		BIN1: PA25
        AIN2: PA22                    		AIN1: PA21
*/

void PwmA_Duty_Set(float Duty,uint8_t channel)				//PWM频率为1kHz
//timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
{
	uint32_t CompareValue = 4000 - Duty;
	switch(channel){
		case 0:
			DL_TimerG_setCaptureCompareValue(PWM_MotorA_INST,CompareValue,GPIO_PWM_MotorA_C0_IDX);			
			break;
		case 1:
			DL_TimerG_setCaptureCompareValue(PWM_MotorA_INST,CompareValue,GPIO_PWM_MotorA_C1_IDX);
			break;
	}
}

void PwmB_Duty_Set(float Duty,uint8_t channel)				//PWM频率为1kHz
//timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
{

	uint32_t CompareValue = 4000 - (1 - Duty) * 4000;
	
	switch(channel){
		case 0:
			DL_TimerG_setCaptureCompareValue(PWM_MotorB_INST,CompareValue,GPIO_PWM_MotorB_C0_IDX);			
			break;
		case 1:
			DL_TimerG_setCaptureCompareValue(PWM_MotorB_INST,CompareValue,GPIO_PWM_MotorB_C1_IDX);
			break;
	}
}


