#include "bsp_lamp.h"

void Lamp_Init(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( LAMP_GPIO_CLK, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LAMP_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LAMP_GPIO_PORT, &GPIO_InitStructure);	
		
		/* �ر�����led��	*/
		GPIO_ResetBits(LAMP_GPIO_PORT, LAMP_GPIO_PIN);
}
