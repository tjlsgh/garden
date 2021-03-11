#ifndef __LAMP_H
#define	__LAMP_H


#include "stm32f10x.h"



// 灯1
#define LAMP_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define LAMP_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LAMP_GPIO_PIN		GPIO_Pin_12			        /* 连接到SCL时钟线的GPIO */


/* 直接操作寄存器的方法控制IO */
#define	L_digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define L_digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define L_digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态


#define LAMP_TOGGLE		 L_digitalToggle(LAMP_GPIO_PORT,LAMP_GPIO_PIN)
#define LAMP_ON		   L_digitalHi(LAMP_GPIO_PORT,LAMP_GPIO_PIN)
#define LAMP_OFF			   L_digitalLo(LAMP_GPIO_PORT,LAMP_GPIO_PIN)

void Lamp_Init(void);
#endif /* __LED_H */
