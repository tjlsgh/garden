#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

typedef struct
{
	float  soil;		//����ʪ��
	float  light;	 	//��ǿ
} ADC_Data_TypeDef;

/********************ADC1����ͨ�������ţ�����**************************/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOA

// ת��ͨ������
#define    NOFCHANEL										 2

#define    ADC_PIN1                      GPIO_Pin_2
#define    ADC_CHANNEL1                  ADC_Channel_2

#define    ADC_PIN2                      GPIO_Pin_5
#define    ADC_CHANNEL2                  ADC_Channel_5


// ADC1 ��Ӧ DMA1ͨ��1��ADC3��ӦDMA2ͨ��5
#define    ADC_x                         ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1


/**************************��������********************************/
void               ADCx_Init                               (void);


#endif /* __ADC_H */

