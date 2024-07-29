#include "Control.h"
#include "stdio.h"

float Velocity_D = 0,Velocity_I = 0;					//速度环KP、KI

int Velocity_out,PWM_out;								//速度环的输出
int Moto1,Moto2;												//两个电机的输出量
int Encoder_Left,Encoder_Right,
			Motor_pwm;
extern PID pid; 

void Interrupt_Solution(void){
//	if(Flag_2ms == 1){
//			
//		Flag_2ms = 0;
//				
//	}
//	if(Flag_20ms == 1){
//		
//		
//		Flag_20ms = 0;
//	}
	
	
	Motor_pwm = Velocity_Con(1000);
	
	printf("Motor_pwm %d\n", Motor_pwm);
	Motor_straight(Motor_pwm);
	
}
//void EXTI9_5_IRQHandler(void)								//中断服务程序
//{
//	if(EXTI_GetITStatus(EXTI_Line5) != 0)				//若IT标志位不为0即表示触发中断
//	{
//		if(PBin(5) == 0)										//中断为下降沿触发，触发后会变为低电平，由此再次判断
//		{
//			EXTI_ClearITPendingBit(EXTI_Line5);		
//			
//			//1.采集编码器的数值
//			Encoder_Left = -Read_Speed(2);				//两个电机相对安装，编码器方向旋转180°，采值相反，为了让编码器输出极性一致，需要取反
//			Encoder_Right = Read_Speed(4);
//			
//			//2.把采集到的数据压入速度闭环控制中、计算输出控制量
//			Velocity_out = Velocity_Con(Encoder_Left,Encoder_Right);
//			
//			PWM_out = Vertical_out + Vertical_P * Velocity_out;			//最终输出
//			//3.把输出量加载到电机上完成控制
//			Moto1 = PWM_out - Turn_out;							//左电机
//			Moto2 = PWM_out + Turn_out;							//右电机
//			M1 = Moto1;
//			M2 = Moto2;
//			Limit(&Moto1,&Moto2);
//			Load(Moto1,Moto2);
//		}
//	}	
//}

/*************
*巡线位置式PID
*公式为：
*入口参数：opencv输出
*返回参数：电机差速打角
*************/




/*************
*速度环控制
*公式为：Velocity_out =Kp2*(Encoder_ real- Encoder_ expect)+Ki*S(Encoder_ real- Encoder_ expect)
*入口参数：左右编码器的速度
*返回参数：速度环pid输出
*************/
//int Velocity_Con(int Encoder_Left,int Encoder_Right)
//{
//	static int PWM_out,Enc_ERR,Enc_ERR_Lowout,Enc_ERR_Lowout_Last,Enc_ERR_S;
//	float a = 0.7;																		//这个系数是作用在低通滤波器上的，要突出其中一部分的信号，一般大于0.5即可
//	//1.计算速度误差
//	Enc_ERR = (Encoder_Left + Encoder_Right) - 0;							//这里的0是预期值，即速度为零静止，不求均值是为了防止舍入误差			
//	//2.速度环的输入会让直立不稳定，添加一个低通滤波器防止高频干扰
//	//LPF公式：滤波结果=a*上一次采样值+(1-a)本次滤波的结果
//	Enc_ERR_Lowout = (1 - a) * Enc_ERR + a * Enc_ERR_Lowout_Last;
//	Enc_ERR_Lowout_Last = Enc_ERR_Lowout;
//	//3.对速度进行积分，得出位移
//	Enc_ERR_S += Enc_ERR_Lowout;													//误差积分
//	//4.对积分进行限幅
//	Enc_ERR_S = Enc_ERR_S > 10000 ? 10000 : (Enc_ERR_S < (-10000) ? (-10000) : Enc_ERR_S);
//	//5.速度环控制输出计算
//	PWM_out = Velocity_D * Enc_ERR_Lowout + Velocity_I * Enc_ERR_S;
//	
//	return PWM_out;
//}


int Velocity_Con(int Aim_velocity)
{
	static int Now_velocity , Now_error,Last_error , Pwm_out,
			   Velocity_P = 1, Velocity_I,Velocity_D;
	
	static float proportion = 10.1,
				 a = 0.7;	
						
	//这个系数是作用在低通滤波器上的，要突出其中一部分的信号，一般大于0.5即可
	//1.计算速度误差
	Encoder_Get();
			
	Now_velocity = (Encoder_left_out + Encoder_right_out) * proportion / 2 ;							//这里的0是预期值，即速度为零静止，不求均值是为了防止舍入误差			
	
	//printf("Now_velocity: %d\n",Now_velocity);
	
	Now_error = Aim_velocity - Now_velocity ;
	
	Pwm_out = Velocity_P *Now_error + Velocity_D * (Now_error - Last_error);
	
	Last_error = Now_error;
	
	//printf("Pwm_out: %d\n",Pwm_out); 
	
	return Pwm_out;
}

