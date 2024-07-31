#include "Motor.h"

/*
        ���AΪ����(TIMG6)     			���BΪ�ҵ��(TIMG12)                  
        AIN2: PA22                    		AIN1: PA21		
        BIN2��PA14                 		BIN1: PA25 | PA31
*/

uint8_t direction = 0;											//���״̬��־λ   1��ת    0��ת
uint8_t STAO = 0;   											//��ͣ��־λ       1����    0ֹͣ
uint16_t Vlocity_init = 3000;										//�ٶȱ���

/*
*װ�غ���
*��ں�����������PIDֵ
*/
//void Load(int Moto1,int Moto2)				//Moto1Ϊ������Moto2Ϊ��
//{
//	//1.������жϵ���ļ��ԣ��о������Ŷ�Ӧ�ĵ������ת
//	if(Moto1 > 0)		Ain1 = 1,Ain2 = 0;				//��ת
//	else 				Ain1 = 0,Ain2 = 1;
//	A1 = Ain1;
//	A2 = Ain2;
//	//2.�о�PWMֵ���ڶ���������ֵ����Ϊ�����PWMֵ����ҪΪ����
//	TIM_SetCompare2(TIM3,GPF_abs(Moto1));
//	
//	if(Moto2 > 0)	Bin1 = 1,Bin2 = 0;				//��ת
//	else 				Bin1 = 0,Bin2 = 1;
//	B1 = Bin1;
//	B2 = Bin2;
//	TIM_SetCompare1(TIM3,GPF_abs(Moto2));
//}

//����ֵ����
int GPF_abs(int x)
{
	if(x > 0) return x;
	else return -x;
}

/*
*ռ�ձ��޷�����
*��ں�����speed
*���ں�����PWMֵ
*/
int Duty_Limit(int16_t Duty)
{
	
		if(Duty >= 4000) Duty =  4000;	
		else if(Duty < 0) Duty = 0;
		else return Duty;				
	
		return Duty;
}

/*
***  ����PWM����
*/
void Moter_Left_Pwm(uint16_t duty){
	PwmA_Duty_Set(0,0);																
	PwmA_Duty_Set(Duty_Limit(duty),1);

}


/*
***  ���һ�PWM����
*/
void Moter_Right_Pwm(uint16_t duty){
	PwmB_Duty_Set(0,0);
	PwmB_Duty_Set(Duty_Limit(duty),1);

}


void Motor_straight(int speed)										//���ֱ��,������ת
{
	PwmA_Duty_Set(0,0);																
	PwmA_Duty_Set(Duty_Limit(speed),1);

	PwmB_Duty_Set(0,0);
	PwmB_Duty_Set(Duty_Limit(speed),1);
	
}



void Motor_TurnRight(int speed)										//������ת��������ת���ҵ����ת

{
	int dutyA = 0,
		dutyB = 0;
	dutyA = Vlocity_init + speed;
	dutyB = Vlocity_init - speed;
	PwmA_Duty_Set(0,0);																
	PwmA_Duty_Set(Duty_Limit(dutyA),1);

	PwmB_Duty_Set(0,0);
	PwmB_Duty_Set(Duty_Limit(dutyB),1);

}


void Motor_Turnleft(int speed)										//������ת��������ת���ҵ����ת

{
	int dutyA = 0,
		dutyB = 0;
	dutyB = Vlocity_init + speed;
	dutyA = Vlocity_init - speed;
	PwmA_Duty_Set(0,0);																
	PwmA_Duty_Set(Duty_Limit(dutyA),1);

	PwmB_Duty_Set(0,0);
	PwmB_Duty_Set(Duty_Limit(dutyB),1);

}

void Motor_Stop(int speed)
{
	PwmA_Duty_Set(Duty_Limit(speed),0);											//PA21 = 0 | PA22 = 1Ϊͣת														
	PwmA_Duty_Set(Duty_Limit(speed),1);				

	PwmB_Duty_Set(Duty_Limit(speed),0);											//PA25 = 0 | PA14 = 1Ϊͣת
	PwmB_Duty_Set(Duty_Limit(speed),1);

}