#ifndef __LAMP_H
#define	__LAMP_H


#include "stm32f10x.h"



// ��1
#define LAMP_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define LAMP_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LAMP_GPIO_PIN		GPIO_Pin_12			        /* ���ӵ�SCLʱ���ߵ�GPIO */


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	L_digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define L_digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define L_digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬


#define LAMP_TOGGLE		 L_digitalToggle(LAMP_GPIO_PORT,LAMP_GPIO_PIN)
#define LAMP_ON		   L_digitalHi(LAMP_GPIO_PORT,LAMP_GPIO_PIN)
#define LAMP_OFF			   L_digitalLo(LAMP_GPIO_PORT,LAMP_GPIO_PIN)

void Lamp_Init(void);
#endif /* __LED_H */
