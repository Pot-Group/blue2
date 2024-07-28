/*
 * ������������Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ
 * �����������www.lckfb.com
 * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ
 * ������̳��https://oshwhub.com/forum
 * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
 * ��������׬Ǯ���������й�����ʦΪ����
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-26     LCKFB     first version
 */
#include "board.h"
#include "stdio.h"

#define RE_0_BUFF_LEN_MAX	128

volatile uint8_t  recv0_buff[RE_0_BUFF_LEN_MAX] = {0};
volatile uint16_t recv0_length = 0;
volatile uint8_t  recv0_flag = 0;

void board_init(void)
{
	// SYSCFG��ʼ��
//	SYSCFG_DL_init();
	//��������жϱ�־
	NVIC_ClearPendingIRQ(USB_TLL_INST_INT_IRQN);
	//ʹ�ܴ����ж�
	NVIC_EnableIRQ(USB_TLL_INST_INT_IRQN);
	
	printf("Board Init [[ ** LCKFB ** ]]\r\n");
}

//����δ�ʱ��ʵ�ֵľ�ȷus��ʱ
void delay_us(unsigned long __us) 
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 38;

    // ������Ҫ��ʱ���� = �ӳ�΢���� * ÿ΢���ʱ����
    ticks = __us * (32000000 / 1000000);

    // ��ȡ��ǰ��SysTickֵ
    told = SysTick->VAL;

    while (1)
    {
        // �ظ�ˢ�»�ȡ��ǰ��SysTickֵ
        tnow = SysTick->VAL;

        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += SysTick->LOAD - tnow + told;

            told = tnow;

            // ����ﵽ����Ҫ��ʱ���������˳�ѭ��
            if (tcnt >= ticks)
                break;
        }
    }
}
//����δ�ʱ��ʵ�ֵľ�ȷms��ʱ
void delay_ms(unsigned long ms) 
{
	delay_us( ms * 1000 );
}

void delay_1us(unsigned long __us){ delay_us(__us); }
void delay_1ms(unsigned long ms){ delay_ms(ms); }

//���ڷ��͵����ַ�
void uart0_send_char(char ch)
{
	//������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
	while( DL_UART_isBusy(USB_TLL_INST) == true );
	//���͵����ַ�
	DL_UART_Main_transmitData(USB_TLL_INST, ch);

}
//���ڷ����ַ���
void uart0_send_string(char* str)
{
	//��ǰ�ַ�����ַ���ڽ�β ���� �ַ����׵�ַ��Ϊ��
	while(*str!=0&&str!=0)
	{
		//�����ַ����׵�ַ�е��ַ��������ڷ������֮���׵�ַ����
		uart0_send_char(*str++);
	}
}

void uart1_send_char(char ch)
{
	//������1æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
	while( DL_UART_isBusy(UART_Trans_INST) == true );
	//���͵����ַ�
	DL_UART_Main_transmitData(UART_Trans_INST, ch);

}

void uart1_send_string(char* str)
{
	//��ǰ�ַ�����ַ���ڽ�β ���� �ַ����׵�ַ��Ϊ��
	while(*str!=0&&str!=0)
	{
		//�����ַ����׵�ַ�е��ַ��������ڷ������֮���׵�ַ����
		uart1_send_char(*str++);
	}
}


#if !defined(__MICROLIB)
//��ʹ��΢��Ļ�����Ҫ�������ĺ���
#if (__ARMCLIB_VERSION <= 6000000)
//�����������AC5  �Ͷ�����������ṹ��
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
	x = x;
}
#endif


//printf�����ض���
int fputc(int ch, FILE *stream)
{
	//������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
	while( DL_UART_isBusy(USB_TLL_INST) == true );
	
	DL_UART_Main_transmitData(USB_TLL_INST, ch);
	
	return ch;
}

//���ڵ��жϷ�����
//void USB_TLL_INST_IRQHandler(void)
//{
//	uint8_t receivedData = 0;
//	
//	//��������˴����ж�
//	switch( DL_UART_getPendingInterrupt(USB_TLL_INST) )
//	{
//		case DL_UART_IIDX_RX://����ǽ����ж�
//			
//			// ���շ��͹��������ݱ���
//			receivedData = DL_UART_Main_receiveData(USB_TLL_INST);

//			// ��黺�����Ƿ�����
//			if (recv0_length < RE_0_BUFF_LEN_MAX - 1)
//			{
//				recv0_buff[recv0_length++] = receivedData;

//				// ������������ٷ��ͳ�ȥ������ش�����ע�͵�
//				uart0_send_char(receivedData);
//			}
//			else
//			{
//				recv0_length = 0;
//			}

//			// ��ǽ��ձ�־
//			recv0_flag = 1;
//		
//			break;
//		
//		default://�����Ĵ����ж�
//			break;
//	}
//}
