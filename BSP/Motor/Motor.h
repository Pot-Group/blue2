#ifndef __MOTOR_H
#define __MOTOR_H

#include "board.h"

extern void Motor_straight(int speed);										//���ֱ��
extern void Motor_Turnleft(int speed);										//�����ת��������ת���ҵ����ת
extern void Motor_TurnRight(int speed);										//�����ת��������ת���ҵ����ת
extern void Motor_Stop(int speed);

extern uint16_t Vlocity_init ;

#endif
