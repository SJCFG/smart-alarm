#include <REGX52.H>
#include "I2C.h"

#define uchar unsigned char
#define AT24C02_ADDRESS 0xA0

/**
  * @name	AT24C02_writebyte
  * @brief	AT24C02写入一个字节
  * @param	Wordaddress ：要写入字节的地址
  * @param	Data ：要写入的数据
  * @retval	无
  */
void AT24C02_writebyte(uchar Wordaddress, Data)
{
	I2C_start();
	I2C_sendbyte(AT24C02_ADDRESS);
	I2C_receiveack();
	I2C_sendbyte(Wordaddress);
	I2C_receiveack();
	I2C_sendbyte(Data);
	I2C_receiveack();
	I2C_stop();
}

/**
  * @name	AT24C02_readbyte
  * @brief	AT24C02读取一个字节
  * @param	Wordaddress ：要读取字节的地址
  * @retval	 Data：要读取的数据
  */
uchar AT24C02_readbyte(uchar Wordaddress)
{
	uchar Data;
	I2C_start();
	I2C_sendbyte(AT24C02_ADDRESS);
	I2C_receiveack();
	I2C_sendbyte(Wordaddress);
	I2C_receiveack();
	I2C_start();
	I2C_sendbyte(AT24C02_ADDRESS|0x01);
	I2C_receiveack();
	Data =  I2C_receivebyte();
	I2C_sendack(1);
	I2C_stop();
	return Data;
}