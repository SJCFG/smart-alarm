#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer.h"
#include "Buzzer.h"
#include "Delay.h"
#include "UART.h"
#include "I2C.h"
#include "AT24C02.h"
#include "DHT11.h"

sbit HC_SR501 = P2^3; //人体检测模块IO口
 
uchar MODE1, MODE2, Timesetselect, flag, warning, upflag_2;
uchar Tempflag, Alarmflag, upflag, runflag, getupflag, startflag, saveflag;
uchar dataGetBuff[5] = {0};
uchar dataGetBuffCount = 0;
uchar code tempstr[5] = "Temp:";
uchar code humistr[5] = "Humi:";
uchar code welcome[8] = "Current ";
uchar code end[8] = "Wake Up!";
uchar code back[3] = "\r\n";

char alarm_time[] = {00, 00, 00, 00}; //闹钟
char cal_time[] = {00, 00, 00}; //倒计时
void Timeshow(void) //时钟显示功能
{
	LCD_ShowString(1, 1, "    ");
	LCD_ShowString(1, 13, "    ");
	LCD_ShowString(1, 7, "-");
	LCD_ShowString(1, 10, "-");
	LCD_ShowString(2, 1, "    ");
	LCD_ShowString(2, 13, "   ");
	LCD_ShowString(2, 7, ":");
	LCD_ShowString(2, 10, ":");
	LCD_ShowNum(1, 5, DS1302_time[0], 2);
	LCD_ShowNum(1, 8, DS1302_time[1], 2);
	LCD_ShowNum(1, 11, DS1302_time[2], 2);
	LCD_ShowNum(2, 5, DS1302_time[3], 2);
	LCD_ShowNum(2, 8, DS1302_time[4], 2);
	LCD_ShowNum(2, 11, DS1302_time[5], 2);
	if(startflag) LCD_ShowChar(2,16,'*');
	else LCD_ShowChar(2,16,' ');
}

void Timeset(void) //时钟设置功能
{
	if(KeyNum == 2)
	{
		KeyNum = 0;
		Timesetselect++;
		Timesetselect %= 6; //越界清零
	}
	if(KeyNum == 3)
	{
		KeyNum = 0;
		DS1302_time[Timesetselect]++;
		if(DS1302_time[0]>99) DS1302_time[0] = 0;
		if(DS1302_time[1]>12) DS1302_time[1] = 1;
		if(DS1302_time[1] == 1 || DS1302_time[1] == 3 || DS1302_time[1] == 5 ||
			DS1302_time[1] == 7 || DS1302_time[1] == 8 || DS1302_time[1] == 10 ||
			DS1302_time[1] == 12)
		{
			if(DS1302_time[2]>31) DS1302_time[2] = 1;
		}
		else if(DS1302_time[1] == 4 || DS1302_time[1] == 6 || DS1302_time[1] == 9 ||
			DS1302_time[1] == 11)
		{
			if(DS1302_time[2]>30) DS1302_time[2] = 1;
		}
		else if(DS1302_time[1] == 2)
		{
			if(DS1302_time[0] % 4 == 0)
			{
				if(DS1302_time[2]>29) DS1302_time[2] = 1;
			}
			else 
			{
				if(DS1302_time[2]>28) DS1302_time[2] = 1;
			}
		}
		if(DS1302_time[3]>23) DS1302_time[3] = 0;
		if(DS1302_time[4]>59) DS1302_time[4] = 0;
		if(DS1302_time[5]>59) DS1302_time[5] = 0;
		if(DS1302_time[6]>7) DS1302_time[6] = 1;
	}
	if(KeyNum == 33)
	{
		KeyNum = 0;
		DS1302_time[Timesetselect]--;
		if(DS1302_time[0] == 0) DS1302_time[0] = 99;
		if(DS1302_time[1] == 0) DS1302_time[1] = 12;
		if(DS1302_time[1] == 1 || DS1302_time[1] == 3 || DS1302_time[1] == 5 ||
			DS1302_time[1] == 7 || DS1302_time[1] == 8 || DS1302_time[1] == 10 ||
			DS1302_time[1] == 12)
		{
			if(DS1302_time[2] == 0) DS1302_time[2] = 31;
		}
		else if(DS1302_time[1] == 4 || DS1302_time[1] == 6 || DS1302_time[1] == 9 ||
			DS1302_time[1] == 11)
		{
			if(DS1302_time[2] == 0 || DS1302_time[2] > 30) DS1302_time[2] = 30;
		}
		else if(DS1302_time[1] == 2)
		{
			if(DS1302_time[0] % 4 == 0)
			{
				if(DS1302_time[2] == 0 || DS1302_time[2] > 29) DS1302_time[2] = 29;
				
			}
			else 
			{
				if(DS1302_time[2] == 0 || DS1302_time[2] > 28) DS1302_time[2] = 28;
			}
		}
		if(DS1302_time[3] < 0) DS1302_time[3] = 23;
		if(DS1302_time[4] < 0) DS1302_time[4] = 59;
		if(DS1302_time[5] < 0) DS1302_time[5] = 59;
		if(DS1302_time[6] < 0) DS1302_time[6] = 7;
	}
	if(Timesetselect == 0 && flag == 1) {LCD_ShowString(1, 5, "  ");}
	else {LCD_ShowNum(1, 5, DS1302_time[0], 2);}
	if(Timesetselect == 1 && flag == 1) {LCD_ShowString(1, 8, "  ");}
	else {LCD_ShowNum(1, 8, DS1302_time[1], 2);}
	if(Timesetselect == 2 && flag == 1) {LCD_ShowString(1, 11, "  ");}
	else {LCD_ShowNum(1, 11, DS1302_time[2], 2);}
	if(Timesetselect == 3 && flag == 1) {LCD_ShowString(2, 5, "  ");}
	else {LCD_ShowNum(2, 5, DS1302_time[3], 2);}
	if(Timesetselect == 4 && flag == 1) {LCD_ShowString(2, 8, "  ");}
	else {LCD_ShowNum(2, 8, DS1302_time[4], 2);}
	if(Timesetselect == 5 && flag == 1) {LCD_ShowString(2, 11, "  ");}
	else {LCD_ShowNum(2, 11, DS1302_time[5], 2);}
}

void Alarmshow(void) //闹钟钟显示功能
{
	alarm_time[0] = AT24C02_readbyte(0);
	alarm_time[1] = AT24C02_readbyte(1);
	alarm_time[2] = AT24C02_readbyte(2);
	alarm_time[3] = AT24C02_readbyte(3);
	LCD_ShowString(1, 1, "Alarm Clock:");
	LCD_ShowNum(2, 5, alarm_time[0], 2);
	LCD_ShowNum(2, 8, alarm_time[1], 2);
	LCD_ShowNum(2, 11, alarm_time[2], 2);
	if(alarm_time[3]) {LCD_ShowString(1, 14, "ON ");}
	else {LCD_ShowString(1, 14, "OFF");}
}

void Alarmsave(void) //闹钟存储功能
{
	AT24C02_writebyte(0,alarm_time[0]);
	Delay(5);
	AT24C02_writebyte(1,alarm_time[1]);
	Delay(5);
	AT24C02_writebyte(2,alarm_time[2]);
	Delay(5);
	AT24C02_writebyte(3,alarm_time[3]);
	Delay(5);
}

void Alarmset(void) //闹钟设置功能
{
	if(KeyNum == 2)
	{
		KeyNum = 0;
		Timesetselect++;
		Timesetselect %= 4; //越界清零
	}
	if(KeyNum == 3)
	{
		KeyNum = 0;
		alarm_time[Timesetselect]++;
		if(alarm_time[0] > 23) alarm_time[0] = 0;
		if(alarm_time[1] > 59) alarm_time[1] = 0;
		if(alarm_time[2] > 59) alarm_time[2] = 0;
		if(alarm_time[3] > 1) alarm_time[3] = 0;
	}
	if(KeyNum == 33)
	{
		KeyNum = 0;
		alarm_time[Timesetselect]--;
		if(alarm_time[0] < 0) alarm_time[0] = 23;
		if(alarm_time[1] < 0) alarm_time[1] = 59;
		if(alarm_time[2] < 0) alarm_time[2] = 59;
		if(alarm_time[3] < 0) alarm_time[3] = 1;
	}
	if(Timesetselect == 0 && flag == 1) {LCD_ShowString(2, 5, "  ");}
	else {LCD_ShowNum(2, 5, alarm_time[0], 2);}
	if(Timesetselect == 1 && flag == 1) {LCD_ShowString(2, 8, "  ");}
	else {LCD_ShowNum(2, 8, alarm_time[1], 2);}
	if(Timesetselect == 2 && flag == 1) {LCD_ShowString(2, 11, "  ");}
	else {LCD_ShowNum(2, 11, alarm_time[2], 2);}
	if(Timesetselect == 3 && flag == 1) {LCD_ShowString(1, 14, "   ");}
	else 
	{
		if(alarm_time[3]) {LCD_ShowString(1, 14, "ON ");}
		else {LCD_ShowString(1, 14, "OFF");}
	}
	saveflag = 1;
}

void AlarmCheck(void) //闹钟判断
{
	uchar i;
	if(DS1302_time[3] == alarm_time[0] && DS1302_time[4] == alarm_time[1] && DS1302_time[5] == alarm_time[2])
	{
		Alarmflag = 1;
		for(i=0;i<8;i++)
			UART_Sendbyte(end[i]);
		for(i=0;i<2;i++)
			UART_Sendbyte(back[i]);
	}
}

void Alarmbeep(void) //闹钟响铃
{
	while(KeyNum != 3 && KeyNum != 2)
	{
		Buzzer_time();
	}
	KeyNum = 0;
}

void Getupcheck(void) //起床检测
{
	if(HC_SR501) getupflag = 1;
	else getupflag = 0;
	if(KeyNum == 22)
	{
		KeyNum = 0;
		startflag = !startflag;
	}
}

void smartalarm(void) //智能闹铃功能
{
	if(startflag && warning && getupflag)
	{
		uchar i;
		for(i=0;i<8;i++)
			UART_Sendbyte(end[i]);
		for(i=0;i<2;i++)
			UART_Sendbyte(back[i]);
		Alarmbeep();
	}
}

void Uart_bluetooth(void)//蓝牙串口
{
	uchar i;
	if(dataGetBuff[1] == 0x20)       //设置闹钟
	{
		switch(dataGetBuff[2])
		{
			case 0x00:i = 0;break;
			case 0x01:i = 1;break;
			case 0x02:i = 2;break;
			case 0x03:i = 3;break;
		}
		if(dataGetBuff[3] == 0x00)
		{
			alarm_time[i] += 1;
			if(alarm_time[0] > 23) alarm_time[0] = 0;
			if(alarm_time[1] > 59) alarm_time[1] = 0;
			if(alarm_time[2] > 59) alarm_time[2] = 0;
			if(alarm_time[3] > 1) alarm_time[3] = 0;
		}
		else 
		{
			alarm_time[i] -= 1;
			if(alarm_time[0] < 0) alarm_time[0] = 23;
			if(alarm_time[1] < 0) alarm_time[1] = 59;
			if(alarm_time[2] < 0) alarm_time[2] = 59;
			if(alarm_time[3] < 0) alarm_time[3] = 1;
		}
		for(i=0;i<5;i++)
		{
			UART_Sendbyte(dataGetBuff[i]);
		}
		saveflag = 1;
	}
	else if(dataGetBuff[1] == 0x30)  //获取温湿度
	{
		if(dataGetBuff[2] == 0x00)
		{
			for(i=0;i<8;i++)
			{
				UART_Sendbyte(welcome[i]);
			}
		}
		if(dataGetBuff[3] == 0x00)
		{
			for(i=0;i<5;i++)
			{
				UART_Sendbyte(tempstr[i]);
			}
			UART_Sendbyte(DHT11_DATA[2]/10 + 0x30);
			UART_Sendbyte(DHT11_DATA[2]%10 + 0x30);
			UART_Sendbyte('.');
			UART_Sendbyte(DHT11_DATA[3]%10 + 0x30);
			for(i=0;i<2;i++)
			{
				UART_Sendbyte(back[i]);
			}
		}
		else 
		{
			for(i=0;i<5;i++)
			{
				UART_Sendbyte(humistr[i]);
			}
			UART_Sendbyte(DHT11_DATA[0]/10 + 0x30);
			UART_Sendbyte(DHT11_DATA[0]%10 + 0x30);
			UART_Sendbyte('.');
			UART_Sendbyte(DHT11_DATA[1]%10 + 0x30);
			for(i=0;i<2;i++)
			{
				UART_Sendbyte(back[i]);
			}
		}
	}
}

void Timebeep(void) // 整点报时
{
	if(DS1302_time[4] == 0 && DS1302_time[5] == 0)
	{
		Buzzer_time();
	}
}

void Tempget(void) //定期刷新温湿度，周期1s
{
	if(Tempflag)
	{
		TR0 = 0;
		DHT11_Readdata();
		TR0 = 1;
	}
}

void Tempshow()  // 温湿度显示
{
	LCD_ShowString(1, 1, "Temp: ");
	LCD_ShowString(2, 1, "Humi: ");
	
	LCD_ShowNum(1,7,DHT11_DATA[2],2);
	LCD_ShowChar(1,9,'.');
	LCD_ShowNum(1,10,DHT11_DATA[3],1);
	LCD_ShowString(1,11," C    ");
		
	LCD_ShowNum(2,7,DHT11_DATA[0],2);
	LCD_ShowChar(2,9,'.');
	LCD_ShowNum(2,10,DHT11_DATA[1],1);
	LCD_ShowString(2,11," %    ");
	
}
void timingshow(void) //倒计时显示
{
	LCD_ShowString(1, 1, "   --Timer--   ");
	LCD_ShowString(2,1,"    ");
	LCD_ShowString(2,13,"    ");
	LCD_ShowChar(2,7,':');
	LCD_ShowChar(2,10,':');
	LCD_ShowNum(2, 5, cal_time[0], 2);
	LCD_ShowNum(2, 8, cal_time[1], 2);
	LCD_ShowNum(2, 11, cal_time[2], 2);
}

void timing(void) //倒计时功能
{
	uchar i = 10;
	if(upflag && (cal_time[0] != 0 || cal_time[1] != 0 || cal_time[2] != 0))
	{
		upflag = 0;
		upflag_2 = 1;
		if(cal_time[2] == 0 && (cal_time[0] != 0 || cal_time[1] != 0))
		{
			cal_time[2] = 59;
			cal_time[1]--;
			if(cal_time[1] < 0 && cal_time[0] != 0)
			{
				cal_time[0]--;
				cal_time[1] = 59;
			}
		}
		cal_time[2]--;
	}
	while(cal_time[0]==0 && cal_time[1]==0 && cal_time[2]==0 && upflag_2)
	{	
		while(i--)
		{
			Buzzer_time();//蜂鸣器长响
		}
		upflag_2=0;
	}
}

void timerset(void) //倒计时设置
{
	if(KeyNum == 2)
	{
		KeyNum = 0;
		Timesetselect++;
		Timesetselect %= 3; //越界清零
	}
	if(KeyNum == 3)
	{
		KeyNum = 0;
		cal_time[Timesetselect]++;
		if(cal_time[0] > 23) cal_time[0] = 0;
		if(cal_time[1] > 59) cal_time[1] = 0;
		if(cal_time[2] > 59) cal_time[2] = 0;
	}
	if(KeyNum == 33)
	{
		KeyNum = 0;
		cal_time[Timesetselect]--;
		if(cal_time[0] < 0) cal_time[0] = 23;
		if(cal_time[1] < 0) cal_time[1] = 59;
		if(cal_time[2] < 0) cal_time[2] = 59;
	}
	if(Timesetselect == 0 && flag == 1) {LCD_ShowString(2, 5, "  ");}
	else {LCD_ShowNum(2, 5, cal_time[0], 2);}
	if(Timesetselect == 1 && flag == 1) {LCD_ShowString(2, 8, "  ");}
	else {LCD_ShowNum(2, 8, cal_time[1], 2);}
	if(Timesetselect == 2 && flag == 1) {LCD_ShowString(2, 11, "  ");}
	else {LCD_ShowNum(2, 11, cal_time[2], 2);}
//	if(cal_time[0] > 0 || cal_time[1] > 0 || cal_time[2] > 0)
//	{
//		runflag = 0;
//	}
}

void main()
{
	LCD_Init();
	//DS1302_Init();
	Buzzer_Init();
	T0_mod1_init();
	UART_Init();
	DS1302_Settime();
	LCD_ShowString(1, 1, "  Alarm Clock  ");
	LCD_ShowString(2, 1, "  ---Loding--  ");
	Delay(1500);
	LCD_ShowString(1, 1, "               ");
	LCD_ShowString(2, 1, "               ");
	while(1)
	{
		Key_Scan();
		Tempget();
		DS1302_Readtime();
		Timebeep();
		AlarmCheck();
		Getupcheck();
		smartalarm();
		if(saveflag)
		{
			Alarmsave();
			saveflag = 0;
		}
		if(alarm_time[3]&&Alarmflag) 
		{
			Alarmbeep();
			Alarmflag = 0;
			warning = 1;
		}
		if(KeyNum == 1)  //模式选择
		{
			KeyNum = 0;
			MODE1++;
			MODE1 %= 4;
			if(MODE1 == 0) {MODE2 = 0;Buzzer_time();Timesetselect = 0;}
			else if(MODE1 == 1) {MODE2 = 0;Buzzer_time();Timesetselect = 0;}
			else if(MODE1 == 2) {MODE2 = 0;Buzzer_time();}
			else if(MODE1 == 3) {MODE2 = 0;Buzzer_time();}
		}
		if(KeyNum == 4)  //修改 or 确认
		{
			KeyNum = 0;
			if(MODE2 == 0) MODE2 = 1;
			else MODE2 = 0;
		} 
		switch(MODE1)
		{
			case 0:
				if(MODE2) 
				{
					Timeset();
					DS1302_Settime();
				}
				else Timeshow();
				break;
			case 1:
				if(MODE2) Alarmset();
				else Alarmshow();
				break;
			case 2:
				Tempshow();
				break;
			case 3:
				if(MODE2) timerset();
				else
				{	
					timing();
					timingshow();					
				}
				break;
		}
	}
}

void T0_rupt() interrupt 1  //1毫秒@11.0592MHz
{
	static unsigned int T0Count0, T0Count1, T0Count2;
	TL0 = 0x66;	 	//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count0++;
	Key_Scan();
	if(T0Count0 >= 400)
	{
		T0Count0 = 0;
		flag = !flag;
	}
	T0Count1++;
	if(T0Count1 >= 1000)
	{
		T0Count1 = 0;
		Tempflag = !Tempflag;
	}
	T0Count2++;
	if(T0Count2 >= 1000)
	{
		T0Count2 = 0;
		upflag = 1;
	}
}

void UartRoutine(void) interrupt 4
{
	uchar res;	
	if(RI)
	{
		res = SBUF;
		if(dataGetBuffCount == 0 && res == 0xAA)
		{
			dataGetBuff[dataGetBuffCount] = res;
			dataGetBuffCount++;
		}else if(dataGetBuffCount!=0)
		{
			dataGetBuff[dataGetBuffCount] = res;
			dataGetBuffCount++;
			if(dataGetBuffCount == 5 && res == 0xDD)
			{
				dataGetBuffCount = 0;
				Uart_bluetooth();
			}
		}
		RI = 0;
	}	
}