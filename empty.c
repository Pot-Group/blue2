/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "board.h" 
#include "ti_msp_dl_config.h"
#include <string.h>
#include "stdio.h"
#include "mpu6050.h"
#include "inv_mpu.h"

int main(void)
{
	 SYSCFG_DL_init();
	 board_init();
     Bluetooth_Init();
	 NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);				//定时器0中断清零标志位
	 DL_TimerG_startCounter(TIMER_0_INST); 
	 NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);						//定时器0中断使能
	 MPU6050_Init();
	 NVIC_EnableIRQ(GPIO_Encoder_INT_IRQN);						//编码器中断使能	
	
	
	 uint8_t ret = 1;
	 uint8_t point = 0;
     float pitch=0,roll=0,yaw=0;   //欧拉角读取
	 printf("start\r\n");
		//DMP初始化
      while( mpu_dmp_init() )
      {
            printf("dmp error\r\n");
            delay_ms(200);
      }
	  printf("Initialization Data Succeed \r\n");
	  
	  
    while (1)
    {
			//接收蓝牙数据
            Receive_Bluetooth_Data();
            //蓝牙发送数据
            BLE_send_String((uint8_t *)"LC-MSPM0G3507\n");
//		pitch = (char)pitch;
//			Send_Bluetooth_Data(&pitch);
//            delay_ms(1000);
			//获取欧拉角
//            if( mpu_dmp_get_data(&pitch,&roll,&yaw) == 0 )
//            {
//				 //printf("%d, %d, %d \r\n", (int)pitch,(int)roll,(int)yaw);
////                printf("\r\nroll =%d\r\n", (int)roll);
////                printf("\r\nyaw =%d\r\n", (int)yaw);
//            }
//            delay_ms(20);//根据设置的采样率，不可设置延时过大
			Interrupt_Solution();
//		Motor_Stop(0);
//		Encoder_Get();
	
	}
}

void TIMER_0_INST_IRQHandler(void)
{
		unsigned int T_2ms;
		unsigned int T_6ms;
		unsigned int T_20ms;
		unsigned int T_50ms;
	
    //Èç¹û²úÉúÁË¶¨Ê±Æ÷ÖÐ¶Ï
    switch( DL_TimerG_getPendingInterrupt(TIMER_0_INST) ){
			case DL_TIMER_IIDX_ZERO:
					T_2ms +=1;
					T_6ms +=1;
					T_20ms +=1;	
					T_50ms +=1;
//			printf("T_2ms %d\n",T_50ms);
			break;            
			default:								
            break;
			} 
		if(T_2ms == 2) { 
			Flag_2ms = 1;
		  T_2ms = 0;   
		}
		if(T_6ms == 6) {
			Flag_6ms = 1;
			T_6ms = 0;
		}
		if(T_20ms == 20) {
			Flag_20ms = 1;
			T_20ms = 0;
		}
		if(T_50ms == 50) {
			Flag_50ms = 1;
			T_50ms = 0;
		}
	
}

