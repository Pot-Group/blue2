#ifndef __ENCODER_H
#define __ENCODER_H

#include "board.h"


extern volatile int32_t Left_Count;
extern volatile int32_t Right_Count;

int Read_Speed(int Encoder_Num);									//¶ÁÈ¡±àÂëÆ÷ËÙ¶È
extern float Encoder_Get();

//void Encoder_datatest();


extern int16_t	 Encoder_left_out,
				 Encoder_right_out;

#endif
