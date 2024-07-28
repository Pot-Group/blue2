#ifndef __LINE_FOLLOW_H
#define __LINE_FOLLOW_H

#include "board.h"

#define Line_Left1 X2                                       //X2为黄线，即PB19
#define Line_Left2 X1                                       //X1为黑线，即PB18
#define Line_Right1 X3                                      //X3为绿线，即PB20
#define Line_Right2 X4                                      //X4为蓝线，即PB24

extern void LineWalking(void);								//巡线模式


#endif
