#ifndef __DHT11_H__
#define __DHT11_H__

#define uchar unsigned char

extern uchar DHT11_DATA[4];
void Delay30us();
void Delay40us();
void Delay20ms();

void DHT11_Rst();
uchar DHT11_Readbyte(void);
uchar DHT11_ReadBit();
char DHT11_Check(void);
char DHT11_Readdata();
#endif