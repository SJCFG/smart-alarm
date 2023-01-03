#include <REGX52.H>

#define uchar unsigned char
#define uint unsigned int
		
#define KEY_DELAY_TIME 	10
#define KEY_LONG_TIME 	250 //长按标志时长
#define KEY_TIME 		500
#define KEY_DOUBLE_TIME 200

//开发板的要换回来key1 和 key2
sbit KEY1 = P3^0;
sbit KEY2 = P3^1;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

uchar key1_lock_flag;
uint key1_cnt;

uchar key2_lock_flag;
uchar key2_cnt;
uint key2_cnt2;
uint key2_cnt3;
uchar key2_times;

uchar key3_lock_flag;
uchar key3_cnt;
uint key3_cnt2;
uint key3_cnt3;
uchar key3_times;

uchar key4_lock_flag;
uchar key4_cnt;

uchar KeyNum = 0;
void Key_Scan(void)
{
	/*--------------------------------------------*/	
	if(KEY1) //如果按键没有按下
	{
		key1_lock_flag = 0; //清零自锁标志
		key1_cnt = 0; //清零计数标志
	}
	else if(!key1_lock_flag)
	{
		key1_cnt++; // 累计按键消抖延时次数
		if(key1_cnt > KEY_DELAY_TIME)
		{
			key1_cnt = 0; //清零计数变量
			key1_lock_flag = 1; // 自锁标志，防止按键多次触发
			KeyNum = 1; //赋键值编码
		}
	}
	/*--------------------------------------------*/	
	if(KEY2) //如果按键没有按下
	{
		key2_lock_flag = 0; //清零自锁标志
		key2_cnt = 0; //清零计数标志
		if(key2_times > 0)
		{
			key2_cnt3++;
			if(key2_cnt3 > KEY_DOUBLE_TIME)
			{
				if(key2_times == 1)
				{	
					KeyNum = 2; //按键单击
				}
				key2_cnt3 = 0; //清楚双击时间间隔
				key2_times = 0; //清楚按键次数
			}
		}
	}
	else if(!key2_lock_flag)
	{
		key2_cnt++; // 累计按键消抖延时次数
		if(key2_cnt > KEY_DELAY_TIME)
		{
			key2_cnt = 0;
			key2_cnt3 = 0;
			key2_times++; //统计按键按下次数 
			key2_lock_flag = 1;
			if(key2_times == 2)
			{
				KeyNum = 22; //按键双击
			}
		}
	}
	else if(key2_cnt < KEY_LONG_TIME)
	{
		key2_cnt++;
	}
	else
	{
		key2_cnt2++;
		if(key2_cnt2 > KEY_TIME)
		{
			key2_cnt2 = 0;
			KeyNum = 222;
		}
	}
	/*--------------------------------------------*/	
	if(KEY3) //如果按键没有按下
	{
		key3_lock_flag = 0; //清零自锁标志
		key3_cnt = 0; //清零计数标志
		if(key3_times > 0)
		{
			key3_cnt3++;
			if(key3_cnt3 > KEY_DOUBLE_TIME)
			{
				if(key3_times == 1)
				{	
					KeyNum = 3; //按键单击
				}
				key3_cnt3 = 0; //清楚双击时间间隔
				key3_times = 0; //清楚按键次数
			}
		}
	}
	else if(!key3_lock_flag)
	{
		key3_cnt++; // 累计按键消抖延时次数
		if(key3_cnt > KEY_DELAY_TIME)
		{
			key3_cnt = 0;
			key3_cnt3 = 0;
			key3_times++; //统计按键按下次数 
			key3_lock_flag = 1;
			if(key3_times == 2)
			{
				KeyNum = 33; //按键双击
			}
		}
	}
	else if(key3_cnt < KEY_LONG_TIME)
	{
		key3_cnt++;
	}
	else
	{
		key3_cnt2++;
		if(key3_cnt2 > KEY_TIME)
		{
			key3_cnt2 = 0;
			KeyNum = 3;
		}
	}
	/*--------------------------------------------*/
	if(KEY4) //如果按键没有按下
	{
		key4_lock_flag = 0; //清零自锁标志
		key4_cnt = 0; //清零计数标志
	}
	else if(!key4_lock_flag)
	{
		key4_cnt++; // 累计按键消抖延时次数
		if(key4_cnt > KEY_DELAY_TIME)
		{
			key4_cnt = 0; //清零计数变量
			key4_lock_flag = 1; // 自锁标志，防止按键多次触发
			KeyNum = 4; //赋键值编码
		}
	}
}
