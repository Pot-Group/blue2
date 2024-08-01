#include "Control.h"
#include "stdio.h"

float Velocity_D = 0,Velocity_I = 0;					

int Velocity_out,PWM_out;								
int Moto1,Moto2;												//��������������
int Encoder_Left,Encoder_Right;
//PID pid; 

int16_t count = 0;
uint8_t count_flag = 0,
		Stop_flag = 0,
		Identify_count = 0;

float Aim_angle = 0;

typedef_flag Flag = {0,0,0,0,0,0};
Mpu_typedef Mpu_data;

PIDtypedef Angle_PID; 
PIDtypedef Velocity_PID; 

void Interrupt_Solution(typedef_flag * Flag){
	int Time_count;
	float Aim_angle = 0 ,Now_angle = 0;
	int Turn_out ,Motor_pwm = 0;
	delay_ms(5);	
	Now_angle = Mpu6050_Getdata(&Mpu_data);
	
	if(count_flag == 1){
	if(Flag->One == 0){
		
		Turn_Funtion(Aim_angle,Now_angle);
	
		if(LineWalking(0) == 1){
			Flag->One = 1;
			Motor_pwm = Velocity_Con(4000);
			Motor_straight(Motor_pwm);
			delay_1ms(50);
			DL_GPIO_clearPins(GPIO_Beep_PORT,GPIO_Beep_PIN_Beep_PIN);
			delay_1ms(10);
			DL_GPIO_setPins(GPIO_Beep_PORT,GPIO_Beep_PIN_Beep_PIN);
			delay_1ms(10);
			DL_GPIO_setPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);
			delay_1ms(10);
			DL_GPIO_clearPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);
			delay_1ms(10);
			Motor_Stop(0);
		}				
	}	
	else if(Flag->One == 1 && Flag->Two == 0  && Flag->Three == 0) {
			
			LineWalking(1);
			if(fabsf(Now_angle) > 160  && LineWalking(0) == 0) {
//				Flag->count ++;
//				if(Flag->count > 3){
				Flag->Three = 1;
				Flag->count = 0;
				Motor_pwm = Velocity_Con(4000);
				Motor_straight(Motor_pwm);
				delay_1ms(10);
				DL_GPIO_clearPins(GPIO_Beep_PORT,GPIO_Beep_PIN_Beep_PIN);
				delay_1ms(10);
				DL_GPIO_setPins(GPIO_Beep_PORT,GPIO_Beep_PIN_Beep_PIN);
//				}
			}
		}
	
	else if( Flag->Three == 1 && Flag->Four == 0){
		
		Turn_Funtion(-170,Now_angle);		
		if(LineWalking(0) == 1){								
							
				Flag->Four = 1;				
				Motor_pwm = Velocity_Con(4000);
				Motor_straight(Motor_pwm);
				delay_1ms(40);
				DL_GPIO_clearPins(GPIO_Beep_PORT,GPIO_Beep_PIN_Beep_PIN);
				delay_1ms(40);
				DL_GPIO_setPins(GPIO_Beep_PORT,GPIO_Beep_PIN_Beep_PIN);
			}
		
		
	}
	else if(Flag->Four == 1  && Flag->Five == 0){
			LineWalking(1);
		//if(LineWalking(0) == 1  && fabsf(Now_angle) < 15) Flag->Five = 1;
			
	} 
	
//	else if( Flag->Five == 1 && fabsf(Now_angle) < 6 && LineWalking(0) == 0){
//				//Flag->Five = 1;
//				Motor_pwm = Velocity_Con(4000);
//				Motor_straight(Motor_pwm);
//				delay_1ms(50);
//				DL_GPIO_clearPins(GPIO_Beep_PORT,GPIO_Beep_PIN_Beep_PIN);
//				delay_1ms(10);
//				DL_GPIO_setPins(GPIO_Beep_PORT,GPIO_Beep_PIN_Beep_PIN);
//			
//			}
//printf("%d ,%d,%d\n", Flag->One,Flag->Two,Flag->Three);

//}



//void One_question(Mpu_typedef *Mpudata){
//	int Time_count;
//	float Aim_angle = 0 ,Now_angle = 0;
//	int Turn_out = 0,Motor_pwm = 0;
//	delay_ms(20);	
//	Now_angle = Mpu6050_Getdata(&Mpu_data);
//	Turn_out = Angle_Position_PID(&Angle_PID,0,Now_angle);
//	
//	if(count_flag == 1 && Stop_flag ==0){
//		if(Turn_out == 0) Motor_straight(Vlocity_init);
//		else if(Turn_out > 0){
//			Motor_Turnleft(Turn_out);
//			
//		}
//			else if(Turn_out < 0){
//			Turn_out = -Turn_out;
//			Motor_TurnRight(Turn_out);
//			
//		}
//			
////		if(LineWalking() == 1){
////			Stop_flag = 1;
////			Motor_pwm = Velocity_Con(4000);
////			Motor_straight(Motor_pwm);
////			DL_GPIO_clearPins(GPIO_Beep_PORT,GPIO_Beep_PIN_Beep_PIN);
////			delay_1ms(10);
////			DL_GPIO_setPins(GPIO_Beep_PORT,GPIO_Beep_PIN_Beep_PIN);
////			DL_GPIO_clearPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);
////			delay_1ms(50);
////			DL_GPIO_setPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);
////		}
////		
//		
//	}
}
		//printf("Aim_angle:%f,Now_angle:%f,Turn_out:%d\n",Aim_angle,Now_angle,Turn_out);

}

void Turn_Funtion(float Aim_angle,float Now_angle){
	int Turn_out;
	Turn_out = Angle_Position_PID(&Angle_PID,Aim_angle,Now_angle);
		if(Turn_out == 0) Motor_straight(Vlocity_init);
		else if(Turn_out > 0){
			Motor_Turnleft(Turn_out);
			
		}
			else if(Turn_out < 0){
			Turn_out = -Turn_out;
			Motor_TurnRight(Turn_out);
			
		}
	}			

float Mpu6050_Getdata(Mpu_typedef * Mpu_yaw){
	
	float pitch=0,roll=0,yaw = 0 ;  
	static float a = 0.7;	
	
	if( mpu_dmp_get_data(&pitch,&roll,&yaw) == 0 )
		{
			if(count_flag == 0)count ++;			
			
			else {
				yaw =  yaw - Mpu_yaw->Yaw_error;
				yaw =  yaw * (1 - a) + Mpu_yaw->Last_yaw * a;
				Mpu_yaw->Last_yaw = yaw;
			}
						
		}
	if(count == 2000 && count_flag == 0 && yaw != 0) {			
		Mpu_yaw->Yaw_error = yaw;
		count_flag = 1;
        DL_GPIO_setPins(GPIO_LED_PORT,GPIO_LED_PIN_0_PIN);  //����ߵ�ƽ
        
	}
	
//	printf("yaw1 = %f ,%d\r\n",yaw,count);
		
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

	PID->Output =  (PID->P * PID->Now_error + PID->D *  (PID->Now_error - PID->Last_Error));
	
	PID->Output = (int)(100 * PID->Output);
	
	PID->Last_Error = PID->Now_error ;
	
	//printf("PID->Output %f\n",PID->Output);
	
	return PID->Output ;
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
	
		PID_set(&Angle_PID,0.45,0.0,0.6);
	
	
		//PID_set(&Velocity_PID,13.5,0,0);


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

