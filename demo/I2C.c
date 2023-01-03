#include <REGX52.H>
#include "Delay.h"

#define uchar unsigned char
	
sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
  * @name	I2C_start
  * @brief	I2C起始条件
  * @param	无
  * @retval	无
  */
void I2C_start()
{
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
}

/**
  * @name	I2C_stop
  * @brief	I2C停止条件
  * @param	无
  * @retval	无
  */
void I2C_stop()
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}

/**
  * @name	I2C_sendbyte
  * @brief	I2C发送一个字节
  * @param	byte 要发送的字节
  * @retval	无
  */
void I2C_sendbyte(uchar byte)
{
	uchar i;
	for(i = 0; i < 8; i++)
	{
		I2C_SDA = byte&(0x80>>i);
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}

/**
  * @name	I2C_receivebyte
  * @brief	I2C接收一个字节
  * @param	无
  * @retval	byte接受的字节
  */
uchar I2C_receivebyte()
{
	uchar i,byte=0x00;
	
	I2C_SDA = 1;
	for(i = 0; i < 8; i++)
	{
		I2C_SCL = 1;
		if(I2C_SDA) {byte |= (0x80>>i);}
		I2C_SCL = 0;
	}	
	return byte;
}

/**
  * @name	I2C_sendack
  * @brief	I2C发送应答
  * @param	ackbit 应答位（0：应答；1：非应答）
  * @retval	无
  */
void I2C_sendack(uchar ackbit)
{
	I2C_SDA = ackbit;
	I2C_SCL = 1;
	I2C_SCL = 0;
}

/**
  * @name	I2C_receiveack
  * @brief	I2C接受应答
  * @param	无
  * @retval	ackbit 应答位（0：应答；1：非应答）
  */
uchar I2C_receiveack()
{
	uchar ackbit;
	I2C_SDA = 1;
	I2C_SCL = 1;
	ackbit = I2C_SDA;
	I2C_SCL = 0;
	return ackbit;
}