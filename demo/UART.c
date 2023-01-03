#include <REGX52.H>
#define uchar unsigned char
	
void UART_Init()		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;		//设置定时初始值
	TH1 = 0xFD;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	EA = 1;
	ES = 1;
}

void UART_Sendbyte(uchar byte)
{
	SBUF = byte;
	while(TI == 0);
	TI = 0;
}

/*串口中断函数模板
void UART_Routine() interrupt 4
{
	if(RI==1)
	{
		
		RI=0;
	}
}
*/