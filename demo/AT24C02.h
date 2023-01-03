#ifndef __AT24C02_H__
#define __AT24C02_H__

#define uchar unsigned char
	
void AT24C02_writebyte(uchar Wordaddress, Data);
uchar AT24C02_readbyte(uchar Wordaddress);


#endif