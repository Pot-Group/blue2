#ifndef __ENCODER_H
#define __ENCODER_H

#include "board.h"


extern volatile int32_t Left_Count;
extern volatile int32_t Right_Count;

int Read_Speed(int Encoder_Num);										//¶ÁÈ¡±àÂëÆ÷ËÙ¶È
extern void Encoder_Get(void);

extern unsigned char Flag_2ms;
extern unsigned char Flag_6ms;
extern unsigned char Flag_20ms;  
extern unsigned char Flag_50ms; 

extern int16_t	 Encoder_left_out,
							 Encoder_right_out;

#endif
