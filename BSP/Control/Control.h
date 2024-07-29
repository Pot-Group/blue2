#ifndef __CONTROL_H
#define __CONTROL_H

#include "board.h"


typedef struct PID
{ 
    float P;               
    float I;
    float D;	
	float Now_error;
    float Last_Error;     
    float OutputMax;       
}PID;

extern PID pid;                        

extern void Interrupt_Solution();
int Velocity_Con(int Aim_velocity);

#endif
