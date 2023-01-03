#ifndef __DS1302_H__
#define __DS1302_H__

#define uchar unsigned char
	
extern char DS1302_time[];

void DS1302_Init();
void DS1302_Writebyte(uchar Command,Data);
uchar DS1302_Readbyte(uchar Command);
void DS1302_Readtime();
void DS1302_Settime();

#endif