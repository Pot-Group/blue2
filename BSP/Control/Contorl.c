#include "Control.h"
#include "stdio.h"

float Velocity_D = 0,Velocity_I = 0;					//�ٶȻ�KP��KI

int Velocity_out,PWM_out;								//�ٶȻ������
int Moto1,Moto2;												//��������������
int Encoder_Left,Encoder_Right;
//PID pid; 

int16_t count = 0;
uint8_t count_flag = 0;

Time0 Flag;
Mpu_typedef Mpu_init;

PIDtypedef Angle_PID; 
PIDtypedef Velocity_PID; 

void Interrupt_Solution(void){
	int Time_count;
	float Aim_angle = 0 ,Now_angle;
	int Turn_out ,Motor_pwm = 0;
	delay_ms(20);	
	Now_angle = Mpu6050_Getdata(&Mpu_init);
	Turn_out = Angle_Position_PID(&Angle_PID,Aim_angle,Now_angle);
	
	if(count_flag == 1){
		if(Turn_out == 0) Motor_straight(Vlocity_init);
		else if(Turn_out > 0){
			Motor_Turnleft(Turn_out);
			DL_GPIO_clearPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);
		}
			else if(Turn_out < 0){
			Turn_out = -Turn_out;
			Motor_TurnRight(Turn_out);
			DL_GPIO_setPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);
		}
			
		if(LineWalking() == 1){
			Motor_pwm = Velocity_Con(4000);
			Motor_straight(Motor_pwm);
			DL_GPIO_clearPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);
			delay_1ms(20);
			DL_GPIO_setPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);
		}
//		else {
//			
//			Motor_Stop(0);
//		
//		}
		
	}
//	Velocity_Con(4000);

//	printf("Turn_out %d\n", Turn_out);	
	//Time_count ++;		
//	Motor_pwm = Velocity_Con(4000);
//	
//	//printf("%d ,%d\n", Vlocity_init,Motor_pwm);
//	Motor_straight(Motor_pwm);
	
}

int One_question(){
	int Turn_out =0;
	if(count_flag == 1){
		if(Turn_out == 0) Motor_straight(Vlocity_init);
		else if(Turn_out > 0){
			Motor_TurnRight(Turn_out);
			
		}
			else if(Turn_out < 0){
			Turn_out = -Turn_out;
			Motor_Turnleft(Turn_out);
			
		}
		
	}
//	if(LineWalking()){
//		Velocity_Con(4000); 
//		DL_GPIO_clearPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);
//		delay_1ms(20);
//		DL_GPIO_setPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);
//	}
	
	return 1;
}


float Mpu6050_Getdata(Mpu_typedef * Mpu_yaw){
	
	float pitch=0,roll=0,yaw = 0 ;  
	static float a = 0.7;	
	
	if( mpu_dmp_get_data(&pitch,&roll,&yaw) == 0 )
		{
			if(count_flag == 0)count ++;			
			
			else {
				yaw =  yaw - Mpu_yaw->yaw;
				yaw =  yaw * (1 - a) + Mpu_yaw->Last_yaw * a;
				Mpu_yaw->Last_yaw = yaw;
			}
						
		}
	if(count == 600 && count_flag == 0 && yaw != 0) {
		Mpu_yaw->yaw = yaw;		
		count_flag = 1;
        DL_GPIO_setPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);  //����ߵ�ƽ
        
	}
	
//	printf("yaw1 = %f %f %d\r\n", Mpu_yaw->yaw,yaw,count);
		
		return yaw;
}	

int Angle_Ring(float Aim_angle,float Now_anlge)
{
	
//	int Pwm_out = 0,Last_pwm_out;
//	
//	Angle_now_error = Aim_angle - Now_anlge;
//	
//	//printf("\r\n Angle_now_error =%f\r\n", Angle_now_error);
//	
//	Pwm_out = (int)(Angle_P * Angle_now_error + Angle_D * (Angle_now_error - Angle_last_error));

//	Angle_last_error = Angle_now_error;
//	
//	return Pwm_out;
	
}


int Angle_Position_PID(PIDtypedef *PID,float Target_value,float Now_value){
	
	PID->Now_error = Target_value - Now_value;

	PID->Output = PID->P * PID->Now_error + PID->D *  (PID->Now_error - PID->Last_Error);
	
	PID->Last_Error = PID->Now_error ;
	
	return (PID->Output * 100);
}

//int Velocity_Position_PID(PIDtypedef *PID,float Target_value,float Now_value){
//	
//	static float Low_pass = 0.7;
//	
//	PID->Now_error = Target_value - Now_value;

//	PID->Output = PID->P * PID->Now_error + PID->D *  (PID->Now_error - PID->Last_Error);
//	
//	PID->Last_Error = PID->Now_error ;
//	
//	PID->Output = Low_pass * PID->Last_output + (1 - Low_pass) * PID->Output;
//	
//	PID->Last_output = PID->Output;
//	
//	return PID->Output;
//}


void PID_set(PIDtypedef *PID,float P,float I,float D){

	
		PID->P = P;
		PID->D = D;
		PID->I = I;
		PID->Now_error = 0;
		PID->Last_Error = 0;
		
	
}

void PID_init(){
	
		PID_set(&Angle_PID,0.3,0,1.2);
		PID_set(&Velocity_PID,4.8,0,1.2);


}



int Velocity_Con(int Aim_velocity)
{
		static float Now_velocity ,Last_velocity, Now_error,Last_error , Pwm_out,Last_pwm_out,
				   Velocity_P = 4.8 , Velocity_I,Velocity_D = 0;
		
		float left_v,right_v;
		
		static float proportion = 10.1,
					 a = 0.7;	
						
	
		left_v = Encoder_Get(1);
		right_v = Encoder_Get(2);

			
		Now_velocity = (left_v + right_v) * proportion / 2 ;							//�����0��Ԥ��ֵ�����ٶ�Ϊ�㾲ֹ�������ֵ��Ϊ�˷�ֹ�������			
			
		Last_velocity = Now_velocity;
			
		Now_error = Aim_velocity - Now_velocity ;
		
		Pwm_out = Velocity_P * Now_error + Velocity_D * (Now_error - Last_error);
			
		Last_error = Now_error;
			
		Pwm_out = Last_pwm_out * a + Pwm_out *(1 - a);
	
		Last_pwm_out = Pwm_out;
				
	
	return Pwm_out;
}

