#ifndef __BLUEBOOTH_H
#define __BLUEBOOTH_H

#include "string.h"
#include "board.h"

//是否开启串口0调试     1开始  0关闭
#define     DEBUG   1


#define  BLERX_LEN_MAX  200


#define BLUETOOTH_LINK      ( ( DL_GPIO_readPins( HC05_PORT, HC05_STATE_PIN ) & HC05_STATE_PIN ) ? 1 : 0 )

#define CONNECT             1       //蓝牙连接成功
#define DISCONNECT          0       //蓝牙连接断开

extern unsigned char BLERX_BUFF[BLERX_LEN_MAX];
extern unsigned char BLERX_FLAG;
extern unsigned char BLERX_LEN;


void Bluetooth_Init(void);
unsigned char Get_Bluetooth_ConnectFlag(void);
void Bluetooth_Mode(void);
void Receive_Bluetooth_Data(void);
void BLE_send_String(unsigned char *str);
extern void BLE_Send_Bit(unsigned char ch);
void Send_Bluetooth_Data(char *dat);

#endif
