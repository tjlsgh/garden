#ifndef __RELAY_H
#define	__RELAY_H


#include "stm32f10x.h"



// ��1
#define RELAY_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define RELAY_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define RELAY_GPIO_PIN		GPIO_Pin_13			        /* ���ӵ�SCLʱ���ߵ�GPIO */


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	R_digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define R_digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define R_digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬


#define RELAY_TOGGLE		 R_digitalToggle(RELAY_GPIO_PORT,RELAY_GPIO_PIN)
#define RELAY_OFF		   R_digitalHi(RELAY_GPIO_PORT,RELAY_GPIO_PIN)
#define RELAY_ON			   R_digitalLo(RELAY_GPIO_PORT,RELAY_GPIO_PIN)

void Relay_Init(void);
#endif /* __LED_H */