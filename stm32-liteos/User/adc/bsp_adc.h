#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

typedef struct
{
	float  soil;		//土壤湿度
	float  light;	 	//光强
} ADC_Data_TypeDef;

/********************ADC1输入通道（引脚）配置**************************/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOA

// 转换通道个数
#define    NOFCHANEL										 2

#define    ADC_PIN1                      GPIO_Pin_2
#define    ADC_CHANNEL1                  ADC_Channel_2

#define    ADC_PIN2                      GPIO_Pin_5
#define    ADC_CHANNEL2                  ADC_Channel_5


// ADC1 对应 DMA1通道1，ADC3对应DMA2通道5
#define    ADC_x                         ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1


/**************************函数声明********************************/
void               ADCx_Init                               (void);


#endif /* __ADC_H */

