/**************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 mian.c
作者	   : 左忠凯
版本	   : V1.0
描述	   : I.MX6U开发板裸机实验7 按键输入实验
其他	   : 本实验主要学习如何配置I.MX6U的GPIO作为输入来使用，通过
	     开发板上的按键控制蜂鸣器的开关。
论坛 	   : www.openedv.com
在线教育	: www.yuanzige.coom
日志	   : 初版V1.0 2019/1/4 左忠凯创建
**************************************************************/
#include "bsp.h"

/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	unsigned char led_state = OFF;
	
	int_init(); 		/* 初始化中断(一定要最先调用！) */
	clk_enable();		/* 使能所有的时钟 			*/
	imx6u_clkinit();	/* 配置时钟频率 			*/
	led_init();			/* 初始化led 			*/
	beep_init();		/* 初始化beep	 		*/
	key_init();			/* 初始化key 			*/
	exit_init();		/* 初始化按键中断			*/

	while(1)			
	{	
		delay(500);
		led_state = !led_state;
		led_switch(LED0, led_state);
	}

	return 0;
}