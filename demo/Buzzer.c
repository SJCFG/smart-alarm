#include <REGX52.H>
#include <INTRINS.H>
#include "Delay.h"
#define uint unsigned int
	
//开发板为2^5
sbit Buzzer = P2^4;

/**
  * @brief  初始化蜂鸣器
  * @param  无
  * @retval 无
  */
void Buzzer_Init(void)
{
	Buzzer = 0;
}

/**
  * @brief  有源蜂鸣器鸣叫
  * @param  无
  * @retval 无
  */
void Buzzer_time(void)
{
	Buzzer = 1;
	Delay(25);	
	Buzzer = 0;
}