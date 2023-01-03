#ifndef __I2C_H__
#define __I2C_H__

#define uchar unsigned char
	
uchar I2C_receivebyte();
void I2C_sendack(uchar ackbit);
uchar I2C_receiveack();
void I2C_sendbyte(uchar byte);
void I2C_stop();
void I2C_start();

#endif