#include "Motor.h"

/*
        电机A为左电机(TIMG6)     			电机B为右电机(TIMG12)                  
        AIN2: PA22                    		AIN1: PA21		
        BIN2：PA14                 		BIN1: PA25 | PA31
*/

uint8_t direction = 0;											//电机状态标志位   1正转    0反转
uint8_t STAO = 0;   											//启停标志位       1启动    0停止
uint16_t Vlocity_init = 3200;										//速度变量

/*
*装载函数
*入口函数：运算后的PID值
*/
//void Load(int Moto1,int Moto2)				//Moto1为左电机，Moto2为右
//{
//	//1.这里可判断电机的极性，研究正负号对应的电机正反转
//	if(Moto1 > 0)		Ain1 = 1,Ain2 = 0;				//反转
//	else 				Ain1 = 0,Ain2 = 1;
//	A1 = Ain1;
//	A2 = Ain2;
//	//2.研究PWM值，第二个参数的值由于为输入的PWM值，需要为正数
//	TIM_SetCompare2(TIM3,GPF_abs(Moto1));
//	
//	if(Moto2 > 0)	Bin1 = 1,Bin2 = 0;				//正转
//	else 				Bin1 = 0,Bin2 = 1;
//	B1 = Bin1;
//	B2 = Bin2;
//	TIM_SetCompare1(TIM3,GPF_abs(Moto2));
//}

//绝对值函数
int GPF_abs(int x)
{
	if(x > 0) return x;
	else return -x;
}

/*
*占空比限幅函数
*入口函数：speed
*出口函数：PWM值
*/
float Duty_Limit(int16_t Duty)
{
	
		if(Duty >= 1023)
			Duty =  4000;	
		else
				Duty = Vlocity_init - Vlocity_init * Duty / 1023;
			//Duty = (Duty * 4000) / 1023;

//		if(Duty >= 4000)
//			 Duty =  4000;	
		
		return Duty;
}


void Motor_straight(float speed)										//电机直行,两轮正转
{
	PwmA_Duty_Set(0,0);																
	PwmA_Duty_Set(Duty_Limit(speed),1);

	PwmB_Duty_Set(0,0);
	PwmB_Duty_Set(Duty_Limit(speed),1);
	
}



void Motor_Turnleft(float speed)										//方向左转，左电机反转，右电机正转

{
	PwmA_Duty_Set(0,0);																
	PwmA_Duty_Set(Duty_Limit(0),1);

	PwmB_Duty_Set(0,0);
	PwmB_Duty_Set(Duty_Limit(speed),1);

}


void Motor_TurnRight(float speed)										//方向右转，左电机正转，右电机反转

{
	PwmA_Duty_Set(0,0);																
	PwmA_Duty_Set(Duty_Limit(speed),1);

	PwmB_Duty_Set(0,0);
	PwmB_Duty_Set(Duty_Limit(0),1);

}

void Motor_Stop(float speed)
{
	PwmA_Duty_Set(Duty_Limit(speed),0);											//PA21 = 0 | PA22 = 1为停转														
	PwmA_Duty_Set(Duty_Limit(speed),1);				

	PwmB_Duty_Set(Duty_Limit(speed),0);											//PA25 = 0 | PA14 = 1为停转
	PwmB_Duty_Set(Duty_Limit(speed),1);

}