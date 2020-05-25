#include "bsp_gpio.h"
/***************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 bsp_gpio.h
作者	   : 左忠凯
版本	   : V1.0
描述	   : GPIO操作文件。
其他	   : 无
论坛 	   : www.openedv.com
日志	   : 初版V1.0 2019/1/4 左忠凯创建
***************************************************************/

/*
 * @description		: GPIO初始化。
 * @param - config	: GPIO配置结构体。
 * @return 			: 无
 */
void gpio_init(gpio_pin_config_t *config)
{
	if(config->direction == kGPIO_DigitalInput) /* 输入 */
	{
		config->base->GDIR &= ~( 1 << config->pin);
	}
	else										/* 输出 */
	{
		config->base->GDIR |= 1 << config->pin;
		gpio_pinwrite(config, config->outputLogic);/* 设置默认输出电平 */
	}
}

 /*
  * @description	 : 读取指定GPIO的电平值 。
  * @param - config	 : 要读取的GPIO结构体。
  * @return 		 : 无
  */
 int gpio_pinread(gpio_pin_config_t *config)
 {
	 return (((config->base->DR) >> config->pin) & 0x1);
 }

 /*
  * @description	 : 指定GPIO输出高或者低电平 。
  * @param - config	 : 要输出的的GPIO结构体。
  * @param - value	 : 要输出的电平，1 输出高电平， 0 输出低低电平
  * @return 		 : 无
  */
void gpio_pinwrite(gpio_pin_config_t *config, int value)
{
	 if (value == 0U)
	 {
		config->base->DR &= ~(1U << config->pin); /* 输出低电平 */
	 }
	 else
	 {
		 config->base->DR |= (1U << config->pin); /* 输出高电平 */
	 }
}



