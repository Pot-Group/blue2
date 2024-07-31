#ifndef __LINE_FOLLOW_H
#define __LINE_FOLLOW_H

#include "board.h"

#define Line_Left1     L2                                       //L1为黄线，即PB19
#define Line_Left2     L3                                       //L2为橙线，即PB18
#define Line_Right1 	R2                                      //R1为紫线，即PB20
#define Line_Right2 	R3                                      //R2为灰线，即PB24


//#define Line_Mid1   	M1                                      //M1为黑线，即PA12
//#define Line_Mid1   	M2                                      //M2为黄线，即PA13


//X1为Mid1   X2为Mid2
extern int LineWalking(void);								//巡线模式


#endif
