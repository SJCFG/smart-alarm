#include <REGX52.H>

#define uchar unsigned char


void T0_mod1_init(void)  //1毫秒@11.0592MHz
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TH0 = 0xFC;
	TL0 = 0x66;	
	TF0 = 0;
	TR0 = 1;
	EA = 1;
	ET0 = 1;
}

void T0_mod2_init(uchar num)
{
	TMOD &= 0xF0;
	TMOD |= 0x02;
	TH0 = (256 - num) / 256;
	TL0 = (256 - num) / 256;
	TF0 = 0;
	TR0 = 1;
	EA = 1;
	ET0 = 1;
}
void T1_mod1_init(void)  //1毫秒@11.0592MHz
{
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TH1 = 0xFC;
	TL1 = 0x66;
	TF1 = 0;
	TR1 = 1;
	EA = 1;
	ET1 = 1;
}

void T1_mod2_init(uchar num)
{
	TMOD &= 0x0F;
	TMOD |= 0x20;
	TH1 = (256 - num) / 256;
	TL1 = (256 - num) / 256;
	TF1 = 0;
	TR1 = 1;
	EA = 1;
	ET1 = 1;
}

/*定时器中断函数模板
void T0_rupt() interrupt 1  //1毫秒@11.0592MHz
{
	static unsigned int T0Count;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		
	}
}
*/