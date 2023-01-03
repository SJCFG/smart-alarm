#include <REGX52.H>
#include <INTRINS.H>
#define uint unsigned int
#define uchar unsigned char

void Delay(uint ms)		//@11.0592MHz
{
	while(ms--)
	{
		unsigned char i, j;

		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}

}

