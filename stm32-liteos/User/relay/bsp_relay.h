#ifndef __RELAY_H
#define	__RELAY_H


#include "stm32f10x.h"



// 灯1
#define RELAY_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define RELAY_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define RELAY_GPIO_PIN		GPIO_Pin_13			        /* 连接到SCL时钟线的GPIO */


/* 直接操作寄存器的方法控制IO */
#define	R_digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define R_digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define R_digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态


#define RELAY_TOGGLE		 R_digitalToggle(RELAY_GPIO_PORT,RELAY_GPIO_PIN)
#define RELAY_OFF		   R_digitalHi(RELAY_GPIO_PORT,RELAY_GPIO_PIN)
#define RELAY_ON			   R_digitalLo(RELAY_GPIO_PORT,RELAY_GPIO_PIN)

void Relay_Init(void);
#endif /* __LED_H */