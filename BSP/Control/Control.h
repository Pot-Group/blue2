#ifndef __CONTROL_H
#define __CONTROL_H

#include "board.h"
extern float ind;

typedef struct
{
	float yaw;
	float Last_yaw;


}Mpu_typedef;

//extern Mpu_typedef Mpu_init;

typedef struct
{ 
    float P;               
    float I;
    float D;	
	float Now_error;
    float Last_Error; 
	float Output;
	float Last_output;
    float OutputMax;       
}PIDtypedef;

extern PIDtypedef Angle_PID; 

//extern float yaw_error;

typedef struct 
{
	
	 unsigned char T_2ms;
	 unsigned char T_6ms;
	 unsigned char T_20ms;  
	 unsigned char T_50ms; 

}Time0;

extern Time0 Flag;

void PID_init();     

int One_question();



extern void Interrupt_Solution();
int Velocity_Con(int Aim_velocity);

float Mpu6050_Getdata( Mpu_typedef * Mpu_yaw);

int Angle_Position_PID(PIDtypedef *PID,float Target_value,float Now_value);
int Angle_Ring(float Aim_angle,float Now_anlge);
void PID_set(PIDtypedef *PID,float P,float I,float D);
void PID_init();

#endif
