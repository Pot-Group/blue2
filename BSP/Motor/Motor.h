#ifndef __MOTOR_H
#define __MOTOR_H

#include "board.h"

extern void Motor_straight(float speed);										//电机直行
extern void Motor_Turnleft(float speed);										//电机左转，左电机反转，右电机正转
extern void Motor_TurnRight(float speed);										//电机右转，左电机正转，右电机反转
extern void Motor_Stop(float speed);

extern uint16_t Vlocity_init ;

#endif
