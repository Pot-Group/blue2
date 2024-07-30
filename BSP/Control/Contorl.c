#include "Control.h"
#include "stdio.h"

float Velocity_D = 0,Velocity_I = 0;					//�ٶȻ�KP��KI

int Velocity_out,PWM_out;								//�ٶȻ������
int Moto1,Moto2;												//��������������
int Encoder_Left,Encoder_Right,
			Motor_pwm;
//PID pid; 

int16_t count = 0;
uint8_t count_flag = 0;

Time0 Flag;
Mpu_typedef Mpu_init;
PIDtypedef Angle_PID; 


void Interrupt_Solution(void){
	int Time_count;
	float Aim_angle = 0 ,Now_angle;
	int Turn_out;
	delay_ms(20);	
	Now_angle = Mpu6050_Getdata(&Mpu_init);
	Turn_out = Position_PID(&Angle_PID,Aim_angle,Now_angle);
	
	if(count_flag == 1){	
		if(Turn_out > 0)Motor_TurnRight(Turn_out);
		else if(Turn_out < 0){
			Turn_out = -Turn_out;
			Motor_Turnleft(Turn_out);
		}
		
	}
	
	
//	printf("Turn_out %d\n", Turn_out);

	
	//Time_count ++;
	
	


	
//	Motor_pwm = Velocity_Con(0);
//	
//	//printf("%d ,%d\n", Vlocity_init,Motor_pwm);
//	Motor_straight(Motor_pwm);
	
}



float Mpu6050_Getdata(Mpu_typedef * Mpu_yaw){
	
	float pitch=0,roll=0,yaw = 0 ;  
	static float a = 0.7;	
	
	if( mpu_dmp_get_data(&pitch,&roll,&yaw) == 0 )
		{
			if(count_flag == 0)count ++;			
			
			else {
				yaw =  yaw - Mpu_yaw->yaw;
						
			}
						
		}
	if(count == 700 && count_flag == 0 && yaw != 0) {
		Mpu_yaw->yaw = yaw;		
		count_flag = 1;
        DL_GPIO_setPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);  //����ߵ�ƽ
        
	}
	
	printf("yaw1 = %f %f %d\r\n", Mpu_yaw->yaw,yaw,count);
		
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


int Position_PID(PIDtypedef *PID,float Target_value,float Now_value){
	
	PID->Now_error = Target_value - Now_value;

	PID->Output = PID->P * PID->Now_error + PID->D *  (PID->Now_error - PID->Last_Error);
	
	PID->Last_Error = PID->Now_error ;
	
	return PID->Output;
}

void PID_set(PIDtypedef *PID,float P,float I,float D){

	
		PID->P = P;
		PID->D = D;
		PID->I = I;
		PID->Now_error = 0;
		PID->Last_Error = 0;
		
	
}

void PID_init(){
	
		PID_set(&Angle_PID,7.0,0,0);



}



int Velocity_Con(int Aim_velocity)
{
	static float Now_velocity ,Last_velocity, Now_error,Last_error , Pwm_out,Last_pwm_out,
			   Velocity_P = 4.8 , Velocity_I,Velocity_D = 0;
	
	float left_v,right_v;
	
	static float proportion = 100.32,
				 a = 0.7;	
						
	
	left_v = Encoder_Get(1);
	right_v = Encoder_Get(2);
//			printf("left_v: %f\n",left_v); 
//			printf("right_v: %f\n",right_v);
			
	Now_velocity = (left_v + right_v) * proportion / 2 ;							//�����0��Ԥ��ֵ�����ٶ�Ϊ�㾲ֹ�������ֵ��Ϊ�˷�ֹ�������			
	
	//Now_velocity = Last_velocity * a + Now_velocity *(1 - a);
	
	Last_velocity = Now_velocity;
	
	//printf("Now_velocity: %f\n",Now_velocity);
	
	Now_error = Aim_velocity - Now_velocity ;
	
	Pwm_out = Velocity_P * Now_error + Velocity_D * (Now_error - Last_error);
			
		Last_error = Now_error;
			
		Pwm_out = Last_pwm_out * a + Pwm_out *(1 - a);
	
		Last_pwm_out = Pwm_out;
		
	
	
	//printf("Pwm_out: %f\n",Pwm_out); 
	
	return Pwm_out;
}

