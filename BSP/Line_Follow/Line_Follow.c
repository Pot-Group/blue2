#include "Line_Follow.h"
#include "ti_msp_dl_config.h"
#include <string.h>
#include "stdio.h"

#define SENSOR_COUNT 6
#define CENTER_SENSOR 3 // 假设中间传感器是第3个

float pidOutput; // PID控制器的输出

PIDtypedef Line_PID = { 15, 0, 0 ,0 , 0 , 0 ,0};
/**
* Function       GetLineWalking
* @brief         获取巡线状态
* @param[in]     int sensors[]  传感器数组
* @param[out]    void
* @retval        void
* @par History   无
*/
void GetLineWalking(int sensors[SENSOR_COUNT])
{
    sensors[0] = DL_GPIO_readPins(GPIO_LineGet_PORT, GPIO_LineGet_PIN_Line_Left1_PIN); // L1
    sensors[1] = DL_GPIO_readPins(GPIO_LineGet_PORT, GPIO_LineGet_PIN_Line_Left2_PIN); //L2
    sensors[2] = DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_12); // 假设LMid为GPIOA的DL_GPIO_PIN_12 M1
    sensors[3] = DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_13); // 假设RMid为GPIOA的DL_GPIO_PIN_13 M2
    sensors[4] = DL_GPIO_readPins(GPIO_LineGet_PORT, GPIO_LineGet_PIN_Line_Right1_PIN);  //R1
    sensors[5] = DL_GPIO_readPins(GPIO_LineGet_PORT, GPIO_LineGet_PIN_Line_Right2_PIN);  //R1
}

/**
* Function       CalculateError
* @brief         计算传感器输出与期望位置之间的误差
* @param[in]     int sensors[]  传感器数组
* @param[out]    float *error   误差值
* @retval        void
*/
void CalculateError(int sensors[SENSOR_COUNT], float *error)
{
    int detectedLineCount = 0;
    float detectedLinePosition = 0.0;

    for (int i = 0; i < SENSOR_COUNT; i++)
    {
        if (sensors[i] == LOW) // 如果检测到黑线
        {
            detectedLinePosition += (i - CENTER_SENSOR + 0.5f);  //中心值为2.5 
            detectedLineCount++;
        }
    }

    if (detectedLineCount > 0)
    {
        *error = detectedLinePosition / detectedLineCount;
    }
    else
    {
        *error = 0.0; // 如果没有检测到黑线，则误差为0
    }
}


/**
* Function       PIDController
* @brief         PID控制器
* @param[in]     float error     误差值
* @param[out]    void
* @retval        void
*/
int PIDController( PIDtypedef * Line_PID,float error)
{
    // 在这里实现你的PID算法
    // ...
    // 更新pidOutput变量
	Line_PID->Now_error = error;
	
	Line_PID->Output = Line_PID->P * Line_PID->Now_error + Line_PID->D *  (Line_PID->Now_error - Line_PID->Last_Error);
	
	Line_PID->Last_Error = Line_PID->Now_error ;
	
	return (Line_PID->Output * 50);
	
}



/**
* Function       LineWalking  
* @brief         巡线模式运动
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   无
*/
int LineWalking(void)
{
    int lineSensors[SENSOR_COUNT] = {1,1,1,1,1,1},
						pidOutput = 0;
    float error = 0;

    GetLineWalking(lineSensors);
    CalculateError(lineSensors, &error);
    pidOutput = PIDController(&Line_PID,error);
	
	// 根据pidOutput调整电机速度
	if(pidOutput == 0) Motor_straight(Vlocity_init);
		else if(pidOutput > 0){
			Motor_Turnleft(pidOutput);
			
		}
			else if(pidOutput < 0){
			pidOutput = -pidOutput;
			Motor_TurnRight(pidOutput);
			
		}   		
		
    // 返回值可以根据需要进行修改
    if(lineSensors[0] == LOW || lineSensors[1] == LOW || lineSensors[4] == LOW || lineSensors[5] == LOW) return 1;

    return 0;
}