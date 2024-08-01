#ifndef __CONTROL_H
#define __CONTROL_H

#include "board.h"
extern float ind;

typedef struct
{
	float yaw;
	float Last_yaw;
	float Yaw_error;

}Mpu_typedef;

extern Mpu_typedef Mpu_data;

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
	unsigned char One;
	unsigned char Two;
	unsigned char Three;
	unsigned char Four;
	unsigned char Five;
	uint16_t count ;


}typedef_flag;

extern typedef_flag Flag;

void Turn_Funtion(float Aim_angle,float Now_angle);

void PID_init();     

void One_question();



extern void Interrupt_Solution();
int Velocity_Con(int Aim_velocity);

float Mpu6050_Getdata( Mpu_typedef * Mpu_yaw);

int Angle_Position_PID(PIDtypedef *PID,float Target_value,float Now_value);
int Angle_Ring(float Aim_angle,float Now_anlge);
void PID_set(PIDtypedef *PID,float P,float I,float D);
void PID_init();

#endif
