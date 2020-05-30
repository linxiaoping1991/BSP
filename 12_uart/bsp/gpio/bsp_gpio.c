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

	config->base->IMR &= ~(1U << config->pin);

	if(config->direction == kGPIO_DigitalInput) /* 输入 */
	{
		config->base->GDIR &= ~( 1 << config->pin);
	}
	else										/* 输出 */
	{
		config->base->GDIR |= 1 << config->pin;
		gpio_pinwrite(config, config->outputLogic);/* 设置默认输出电平 */
	}

	gpio_intconfig(config->base, config->pin, config->interruptMode);	/* 中断功能配置 */
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

/*
 * @description  			: 设置GPIO的中断配置功能
 * @param - base 			: 要配置的IO所在的GPIO组。
 * @param - pin  			: 要配置的GPIO脚号。
 * @param - pinInterruptMode: 中断模式，参考枚举类型gpio_interrupt_mode_t
 * @return		 			: 无
 */
void gpio_intconfig(GPIO_Type* base, unsigned int pin, gpio_interrupt_mode_t pin_int_mode)
{
	volatile uint32_t *icr;
	uint32_t icrShift;

	icrShift = pin;
	
	base->EDGE_SEL &= ~(1U << pin);

	if(pin < 16) 	/* 低16位 */
	{
		icr = &(base->ICR1);
	}
	else			/* 高16位 */
	{
		icr = &(base->ICR2);
		icrShift -= 16;
	}
	switch(pin_int_mode)
	{
		case(kGPIO_IntLowLevel):
			*icr &= ~(3U << (2 * icrShift));
			break;
		case(kGPIO_IntHighLevel):
			*icr = (*icr & (~(3U << (2 * icrShift)))) | (1U << (2 * icrShift));
			break;
		case(kGPIO_IntRisingEdge):
			*icr = (*icr & (~(3U << (2 * icrShift)))) | (2U << (2 * icrShift));
			break;
		case(kGPIO_IntFallingEdge):
			*icr |= (3U << (2 * icrShift));
			break;
		case(kGPIO_IntRisingOrFallingEdge):
			base->EDGE_SEL |= (1U << pin);
			break;
		default:
			break;
	}
}


/*
 * @description  			: 使能GPIO的中断功能
 * @param - base 			: 要使能的IO所在的GPIO组。
 * @param - pin  			: 要使能的GPIO在组内的编号。
 * @return		 			: 无
 */
void gpio_enableint(GPIO_Type* base, unsigned int pin)
{ 
    base->IMR |= (1 << pin);
}

/*
 * @description  			: 禁止GPIO的中断功能
 * @param - base 			: 要禁止的IO所在的GPIO组。
 * @param - pin  			: 要禁止的GPIO在组内的编号。
 * @return		 			: 无
 */
void gpio_disableint(GPIO_Type* base, unsigned int pin)
{ 
    base->IMR &= ~(1 << pin);
}

/*
 * @description  			: 清除中断标志位(写1清除)
 * @param - base 			: 要清除的IO所在的GPIO组。
 * @param - pin  			: 要清除的GPIO掩码。
 * @return		 			: 无
 */
void gpio_clearintflags(GPIO_Type* base, unsigned int pin)
{
    base->ISR |= (1 << pin);
}

