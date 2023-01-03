#include <REGX52.H>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

#define uchar unsigned char
#define DS1302_second	0x80
#define DS1302_minute	0x82
#define DS1302_hour 	0x84
#define DS1302_date 	0x86
#define DS1302_month	0x88
#define DS1302_day  	0x8a
#define DS1302_year 	0x8c
#define DS1302_protect	0x8e

char DS1302_time[] = {22,11,12,12,59,57,6};
/**
  * @brief  时钟初始化
  * @param  无
  * @retval 无
  */
void DS1302_Init()
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

/**
  * @brief  写入一个字节
  * @param  Command：写入的指令；Data：写入的数据
  * @retval 无
  */
void DS1302_Writebyte(uchar Command,Data)
{
	uchar i;
	DS1302_CE = 1;
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = Command & (0x01<<i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = Data & (0x01<<i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	DS1302_CE = 0;
}

/**
  * @brief  读取一个字节
  * @param  Command：读取的指令
  * @retval Data：读取的数据
  */
uchar DS1302_Readbyte(uchar Command)
{
	uchar i,Data = 0x00;
	Command |= 0x01;
	DS1302_CE = 1;
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = Command & (0x01<<i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	for(i = 0; i < 8; i++)
	{
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if(DS1302_IO) { Data |= (0x01 << i);}
	}
	DS1302_CE = 0;
	DS1302_IO = 0;
	return Data;
}

/**
  * @brief  设置时间
  * @param  无
  * @retval 无
  */
void DS1302_Settime()
{
	DS1302_Writebyte(DS1302_protect,0x00);
	DS1302_Writebyte(DS1302_year,DS1302_time[0]/10*16+DS1302_time[0]%10);
	DS1302_Writebyte(DS1302_month,DS1302_time[1]/10*16+DS1302_time[1]%10);
	DS1302_Writebyte(DS1302_date,DS1302_time[2]/10*16+DS1302_time[2]%10);
	DS1302_Writebyte(DS1302_hour,DS1302_time[3]/10*16+DS1302_time[3]%10);
	DS1302_Writebyte(DS1302_minute,DS1302_time[4]/10*16+DS1302_time[4]%10);
	DS1302_Writebyte(DS1302_second,DS1302_time[5]/10*16+DS1302_time[5]%10);
	DS1302_Writebyte(DS1302_day,DS1302_time[6]/10*16+DS1302_time[6]%10);
	DS1302_Writebyte(DS1302_protect,0x80);
}

/**
  * @brief  读取时间
  * @param  无
  * @retval 无
  */
void DS1302_Readtime()
{
	uchar temp;
	temp = DS1302_Readbyte(DS1302_year);
	DS1302_time[0] = temp/16*10 + temp%16;
	temp = DS1302_Readbyte(DS1302_month);
	DS1302_time[1] = temp/16*10 + temp%16;
	temp = DS1302_Readbyte(DS1302_date);
	DS1302_time[2] = temp/16*10 + temp%16;
	temp = DS1302_Readbyte(DS1302_hour);
	DS1302_time[3] = temp/16*10 + temp%16;
	temp = DS1302_Readbyte(DS1302_minute);
	DS1302_time[4] = temp/16*10 + temp%16;
	temp = DS1302_Readbyte(DS1302_second);
	DS1302_time[5] = temp/16*10 + temp%16;
	temp = DS1302_Readbyte(DS1302_day);
	DS1302_time[6] = temp/16*10 + temp%16;
}