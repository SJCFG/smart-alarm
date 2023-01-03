#include <REGX52.H>
#include <INTRINS.H>

//开发板为1^7
sbit Data = P3^7;

#define uchar unsigned char
#define uint unsigned int

uchar DHT11_DATA[4];

void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 36;
	j = 217;
	do
	{
		while (--j);
	} while (--i);
}

void Delay30us()		//@11.0592MHz
{
	unsigned char i;

	i = 11;
	while (--i);
}

void Delay40us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 15;
	while (--i);
}

void DHT11_Rst(void)
{
	Data = 1;
	_nop_();
	Data = 0;
	Delay20ms();
	Data = 1;
	Delay40us();
}

char DHT11_Check(void)
{
	uint t = 0;
	while(Data) //等待低电平
	{
		t++;
		_nop_();
		if(t > 1000)
			return -1;
	}
	t = 0;
	while(!Data) // 判断低电平的合法性
	{
		t++;
		_nop_();
		if(t > 100)
			return -2;
	}
	t = 0;
	while(Data)
	{
		t++;
		_nop_();
		if(t > 100)
			return -3;
	}
	return 0; //如果DHT11正常返回0
}


uchar DHT11_Readbyte(void)
{
	uint t;
	uchar i,byte;
	for(i = 0; i < 8; i++) //高位先出，低位后出
	{
		while(!Data)
		{
			t++;
			_nop_();
			if(t > 100)
				return 0;
		}
		Delay40us();
		byte <<= 1;
		if(Data == 1)
		{
			byte |= 1;
			t = 0;
			while(Data)
			{
				t++;
				_nop_();
				if(t > 100)
					return 0;
			}	
		}
	}
	return byte;
}

char DHT11_Readdata()
{
	uchar buff[5];
	DHT11_Rst();
	if(DHT11_Check() == 0)
	{
		buff[0] = DHT11_Readbyte(); //湿度high 8
		buff[1] = DHT11_Readbyte();//湿度low 8
		buff[2] = DHT11_Readbyte();//温度high 8
		buff[3] = DHT11_Readbyte();//温度low 8
		buff[4] = DHT11_Readbyte();//校验位
		Delay40us();
		if((buff[0]+buff[1]+buff[2]+buff[3]) == buff[4])
		{
			DHT11_DATA[0] = buff[0];
			DHT11_DATA[1] = buff[1];
			DHT11_DATA[2] = buff[2];
			DHT11_DATA[3] = buff[3];
		}
		else
			return -1;
	}
	else
		return -2;
	return 0;
}