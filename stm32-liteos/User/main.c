/* LiteOS ͷ�ļ� */
#include "los_sys.h"
#include "los_task.h"
#include "los_tick.h"
/* �弶����ͷ�ļ� */
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_key.h" 
#include "bsp_esp8266.h"
#include "wifi.h"
#include "mqtt.h"
#include "bsp_dht11.h"
#include "bsp_adc.h"

/********************************** ������ *************************************/
/* ���������� */
UINT32 Read_Publish_Task_Handle;
UINT32 Connect_Init_Task_Handle;
UINT32 Key_Task_Handle;
UINT32 Mqtt_SendHeatbeat_Handle;

/********************************** �������� *************************************/
static UINT32 AppTaskCreate(void);
static UINT32 Creat_Connect_Init_Task(void);
static UINT32 Creat_Key_Task(void);
static UINT32 Creat_Read_Publish_Task(void);
static UINT32 Creat_Mqtt_SendHeatbeat_Task(void);

static void Connect_Init_Task(void);
static void Read_Publish_Task(void);
static void Key_Task(void);
static void BSP_Init(void);
static void Mqtt_SendHeatbeat_Task(void);

/***************************************************************
  * @brief  ������
  * @param  ��
  * @retval ��
  * @note   ��һ����������Ӳ����ʼ�� 
			�ڶ���������APPӦ������
			������������LiteOS����ʼ��������ȣ�����ʧ�������������Ϣ
  **************************************************************/
int main(void)
{	
	UINT32 uwRet = LOS_OK;  //����һ�����񴴽��ķ���ֵ��Ĭ��Ϊ�����ɹ�
	
	/* ������س�ʼ�� */
  BSP_Init();
	printf("\n ��ʼ���ɹ���\n");

	/* LiteOS �ں˳�ʼ�� */
	uwRet = LOS_KernelInit();
	
  if (uwRet != LOS_OK)
  {
		printf("LiteOS ���ĳ�ʼ��ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
		return LOS_NOK;
  }
	
	uwRet = AppTaskCreate();
	if (uwRet != LOS_OK)
  {
		printf("AppTaskCreate��������ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
		return LOS_NOK;
  }

  /* ����LiteOS������� */
  LOS_Start();
	
	//��������²���ִ�е�����
	while(1);
}


/*********************************************************************

							        ���������������������

  *******************************************************************/
static UINT32 AppTaskCreate(void)
{
	/* ����һ���������ͱ�������ʼ��ΪLOS_OK */
	UINT32 uwRet = LOS_OK;
	
	uwRet = Creat_Key_Task();
  if (uwRet != LOS_OK)
  {
		printf("Key_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
		return uwRet;
  }
	
	uwRet = Creat_Connect_Init_Task();
  if (uwRet != LOS_OK)
  {
		printf("Connect_Init���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
		return uwRet;
  }
	
	return LOS_OK;
}


/******************************************************************

														��������

  ******************************************************************/
static UINT32 Creat_Connect_Init_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;			
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;	

	task_init_param.usTaskPrio = 1;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
	task_init_param.pcName = "Connect_Init_Task";/* ������ */
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Connect_Init_Task;/* ��������� */
	task_init_param.uwStackSize = 1024;		/* ��ջ��С */

	uwRet = LOS_TaskCreate(&Connect_Init_Task_Handle, &task_init_param);/* �������� */
	return uwRet;
}

static UINT32 Creat_Key_Task()
{
	// ����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;				
	TSK_INIT_PARAM_S task_init_param;

	task_init_param.usTaskPrio = 4;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
	task_init_param.pcName = "Key_Task";	/* ������*/
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Key_Task;/* ��������� */
	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
	
	uwRet = LOS_TaskCreate(&Key_Task_Handle, &task_init_param);/* �������� */

	return uwRet;
}

static UINT32 Creat_Read_Publish_Task()
{
	// ����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;				
	TSK_INIT_PARAM_S task_init_param;

	task_init_param.usTaskPrio = 2;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
	task_init_param.pcName = "Key_Task";	/* ������*/
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Read_Publish_Task;/* ��������� */
	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
	
	uwRet = LOS_TaskCreate(&Read_Publish_Task_Handle, &task_init_param);/* �������� */

	return uwRet;
}

static UINT32 Creat_Mqtt_SendHeatbeat_Task()
{
	// ����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;				
	TSK_INIT_PARAM_S task_init_param;

	task_init_param.usTaskPrio = 5;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
	task_init_param.pcName = "Mqtt_SendHeatbeat_Task";	/* ������*/
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Mqtt_SendHeatbeat_Task;/* ��������� */
	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
	
	uwRet = LOS_TaskCreate(&Mqtt_SendHeatbeat_Handle, &task_init_param);/* �������� */

	return uwRet;
}

/******************************************************************
  
														����ʵ��

  *****************************************************************/
static void Connect_Init_Task(void)
{
	UINT32 uwRet = LOS_OK;
  /* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		Wifi_Config();			//����wifi
		Server_Connect(); 		//���ӷ�����
		LOS_TaskDelay(1000);		
		Mqtt_Connect();
		LOS_TaskDelay(1000);
		
		// ������������������
		uwRet = Creat_Mqtt_SendHeatbeat_Task(); 
		if (uwRet != LOS_OK)
		{
			printf("Mqtt_SendHeatbeat���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
		}else {
			printf("������������ɹ���\n");
		}
		
		// ������ȡ���ݲ����͵��ƶ�����
		uwRet = Creat_Read_Publish_Task();
		if (uwRet != LOS_OK)
		{
			printf("Key_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
		}else {
			printf("������ȡdht11����������ɹ���\n");
		}
		
		LOS_TaskDelete(Connect_Init_Task_Handle);			//ɾ������
	}
}

static void Mqtt_SendHeatbeat_Task(void)
{
  /* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		Mqtt_SendHeatbeat();
		printf("\n���������ɹ�\n");
		LOS_TaskDelay(30000);	
	}
}

static void Key_Task(void)
{
	UINT32 uwRet = LOS_OK;				
	
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		/* K1 ������ */
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )
		{
			printf("����LED����\n");
			uwRet = LOS_TaskSuspend(Connect_Init_Task_Handle);/* ����LED1���� */
			if(LOS_OK == uwRet)
			{
				printf("����LED����ɹ���\n");
			}
		}
		/* K2 ������ */
		else if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON ) 
		{
			printf("�ָ�LED����\n");
			uwRet = LOS_TaskResume(Connect_Init_Task_Handle); /* �ָ�LED1���� */
			if(LOS_OK == uwRet)
			{
				printf("�ָ�LED����ɹ���\n");
			}
			
		}
		LOS_TaskDelay(20);   /* 20msɨ��һ�� */
	}
}

static void Read_Publish_Task(void)
{	
	DHT11_Data_TypeDef DHT11_Data;
	extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
	ADC_Data_TypeDef ADC_Data;
	
	char mqtt_message[200];
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		LED1_TOGGLE;			//LED��ת
		if( DHT11_Read_TempAndHumidity ( &DHT11_Data ) == SUCCESS)
		{
			printf("\r\n ����ʪ��Ϊ%d.%d ��RH �������¶�Ϊ %d.%d�� \r\n",\
			DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		}			
		else
		{
				printf("Read DHT11 ERROR!\r\n");
		}
		ADC_Data.light = (-((float)ADC_ConvertedValue[0] /100) + 45)*3;
		ADC_Data.soil = (-((float)ADC_ConvertedValue[1] /100) + 45)*3;	
		Mqtt_Publish(&DHT11_Data, ADC_Data.light, ADC_Data.soil);
		printf("\r\n ��ǿΪ%.2f LUX������ʪ��Ϊ %.2f \r\n",\
		ADC_Data.light, ADC_Data.soil);
		LOS_TaskDelay(5000); // ÿ���ȡһ��
	}
}

/*******************************************************************

                    �弶�����ʼ��

  ******************************************************************/
static void BSP_Init(void)
{
	/*
	 * STM32�ж����ȼ�����Ϊ4����4bit��������ʾ��ռ���ȼ�����ΧΪ��0~15
	 */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	
	/* LED ��ʼ�� */
	LED_GPIO_Config();

	/* ���ڳ�ʼ��	*/
	USART_Config();

  /* ������ʼ�� */
	Key_GPIO_Config();
  /* ������ʼ�� */
	DHT11_Init ();
  /* esp8266��ʼ�� */	
	ESP8266_Init();
  /* ��ȡ����ʪ�ȴ������͹��������� */	
	ADCx_Init();
}


/*********************************************END OF FILE**********************/

