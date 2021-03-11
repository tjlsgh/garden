
///* LiteOS ͷ�ļ� */
//#include "los_sys.h"
//#include "los_task.h"
//#include "los_tick.h"
//#include "los_queue.h"
///* �弶����ͷ�ļ� */
//#include "bsp_usart.h"
//#include "bsp_led.h"
//#include "bsp_key.h" 
//#include "bsp_esp8266.h"
//#include "wifi.h"
//#include "mqtt.h"
//#include "bsp_dht11.h"
//#include "bsp_adc.h"

///********************************** ������ *************************************/
///* ���������� */
//UINT32 Key_Task_Handle;
//UINT32 Connect_Init_Task_Handle;
//UINT32 Read_Publish_Task_Handle;
//UINT32 Mqtt_SendHeatbeat_Task_Handle;
//UINT32 Subscribe_React_Task_Handle;
//UINT32 Execute_FillLight_Handle;
//UINT32 Execute_Sprink_Handle;

///********************************** �������� *************************************/
//static UINT32 AppTaskCreate(void);
//static UINT32 Create_Key_Task(void);
//static UINT32 Create_Connect_Init_Task(void);
//static UINT32 Create_Read_Publish_Task(void);
//static UINT32 Create_Mqtt_SendHeatbeat_Task(void);
//static UINT32 Create_Subscribe_React_Task(void);
//static UINT32 Create_Execute_FillLight_Task(void);
//static UINT32 Create_Execute_Sprink_Task(void);

//static void BSP_Init(void);
//static void Key_Task(void);
//static void Connect_Init_Task(void);
//static void Read_Publish_Task(void);
//static void Mqtt_SendHeatbeat_Task(void);
//static void Subscribe_React_Task(void);
//static void Execute_FillLight_Task(void);
//static void Execute_Sprink_Task(void);
//static void Call_Service(UINT8 type, UINT8 len);
//	
// /* ������Ϣ���еľ�� */
//UINT32 Lamp_Queue_Handle;
//UINT32 Water_Queue_Handle;

///* ������Ϣ���г��� */
//#define  MESSAGE_Queue_LEN  	10
//#define  MESSAGE_QUEUE_SIZE   10

//// ��������
//#define FILL_LIGHT 4
//#define SPRINK 5

//UINT32 receive_data = 0;
///***************************************************************
//  * @brief  ������
//  * @param  ��
//  * @retval ��
//  * @note   ��һ����������Ӳ����ʼ�� 
//			�ڶ���������APPӦ������
//			������������LiteOS����ʼ��������ȣ�����ʧ�������������Ϣ
//  **************************************************************/
//int main(void)
//{	
//	UINT32 uwRet = LOS_OK;  //����һ�����񴴽��ķ���ֵ��Ĭ��Ϊ�����ɹ�
//	
//	/* ������س�ʼ�� */
//  BSP_Init();
//	printf("\n************* ��ʼ���ɹ���*************\n");

//	/* LiteOS �ں˳�ʼ�� */
//	uwRet = LOS_KernelInit();
//	
//  if (uwRet != LOS_OK)
//  {
//		printf("LiteOS ���ĳ�ʼ��ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return LOS_NOK;
//  }
//	
//	uwRet = AppTaskCreate();
//	if (uwRet != LOS_OK)
//  {
//		printf("AppTaskCreate��������ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return LOS_NOK;
//  }

//  /* ����LiteOS������� */
//  LOS_Start();
//	
//	//��������²���ִ�е�����
//	while(1);
//}


///*********************************************************************

//							        ���������������������

//  *******************************************************************/
//static UINT32 AppTaskCreate(void)
//{
//	/* ����һ���������ͱ�������ʼ��ΪLOS_OK */
//	UINT32 uwRet = LOS_OK;
//	
//		/* �����������У��������ݽ���ִ��ģ��ִ��*/
//	uwRet = LOS_QueueCreate("Lamp_Queue",				/* ���е����� */
//													MESSAGE_Queue_LEN,			/* ���еĳ��� */
//													&Lamp_Queue_Handle,	/* ���е�ID(���) */
//													0,						/* ����ģʽ���ٷ���ʱδʹ�� */
//													MESSAGE_QUEUE_SIZE);	/* �ڵ��С����λΪ�ֽ� */
//	if (uwRet != LOS_OK)
//  {
//		printf("Lamp_Queue���д���ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return uwRet;
//  }
//	uwRet = LOS_QueueCreate("Water_Queue",				/* ���е����� */
//													MESSAGE_Queue_LEN,			/* ���еĳ��� */
//													&Water_Queue_Handle,	/* ���е�ID(���) */
//													0,						/* ����ģʽ���ٷ���ʱδʹ�� */
//													MESSAGE_QUEUE_SIZE);	/* �ڵ��С����λΪ�ֽ� */
//	if (uwRet != LOS_OK)
//  {
//		printf("Water_Queue���д���ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return uwRet;
//  }
//	
//	uwRet = Create_Key_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Key_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return uwRet;
//  }
//	
//	uwRet = Create_Connect_Init_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Connect_Init_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return uwRet;
//  }
//	
//	uwRet = Create_Execute_FillLight_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Execute_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return uwRet;
//  }
//	uwRet = Create_Execute_Sprink_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Execute_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return uwRet;
//  }
//	return LOS_OK;
//}


///******************************************************************

//														��������

//  ******************************************************************/
//static UINT32 Create_Connect_Init_Task()
//{
//	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
//	UINT32 uwRet = LOS_OK;			
//	
//	//����һ�����ڴ�������Ĳ����ṹ��
//	TSK_INIT_PARAM_S task_init_param;	

//	task_init_param.usTaskPrio = 1;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Connect_Init_Task";/* ������ */
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Connect_Init_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;		/* ��ջ��С */

//	uwRet = LOS_TaskCreate(&Connect_Init_Task_Handle, &task_init_param);/* �������� */
//	return uwRet;
//}

//static UINT32 Create_Key_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 4;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Key_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Key_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Key_Task_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}

//static UINT32 Create_Read_Publish_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Read_Publish_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Read_Publish_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Read_Publish_Task_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}

//static UINT32 Create_Mqtt_SendHeatbeat_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 5;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Mqtt_SendHeatbeat_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Mqtt_SendHeatbeat_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Mqtt_SendHeatbeat_Task_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}

//static UINT32 Create_Subscribe_React_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Subscribe_React_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Subscribe_React_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Subscribe_React_Task_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}

//static UINT32 Create_Execute_FillLight_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 1;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Execute_FillLight_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Execute_FillLight_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Execute_FillLight_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}

//static UINT32 Create_Execute_Sprink_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Execute_Sprink_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Execute_Sprink_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Execute_Sprink_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}
///******************************************************************
//  
//														����ʵ��

//  *****************************************************************/
//static void Connect_Init_Task(void)
//{
//	UINT32 uwRet = LOS_OK;
//  /* ������һ������ѭ�������ܷ��� */
//	while(1)
//	{
//		Wifi_Config();			//����wifi
//		Server_Connect(); 		//���ӷ�����
//		LOS_TaskDelay(1000);		
//		Mqtt_Connect();
//		LOS_TaskDelay(1000);
//		
//		/********************* ������������������ **************************/
//		uwRet = Create_Mqtt_SendHeatbeat_Task(); 
//		if (uwRet != LOS_OK)
//		{
//			printf("Mqtt_SendHeatbeat���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		}else {
//			printf("������������ɹ���\n");
//		}
//		
//		/*************** ������ȡ���ݲ����͵��ƶ˵����� *********************/
//		uwRet = Create_Read_Publish_Task();
//		if (uwRet != LOS_OK)
//		{
//			printf("Read_Publish_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		}else {
//			printf("������ȡdht11����������ɹ���\n");
//		}
//		
//		/*************** ���������¼�����Ӧ������ *********************/
//		uwRet = Create_Subscribe_React_Task();
//		if (uwRet != LOS_OK)
//		{
//			printf("Subscribe_React_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		}else {
//			printf("����������Ӧ����ɹ���\n");
//		}
//		LOS_TaskDelete(Connect_Init_Task_Handle);			//ɾ������
//	}
//}

//static void Mqtt_SendHeatbeat_Task(void)
//{
//  /* ������һ������ѭ�������ܷ��� */
//	while(1)
//	{
//		Mqtt_SendHeatbeat();
//		printf("\n���������ɹ�\n");
//		LOS_TaskDelay(30000);	
//	}
//}

//static void Key_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	
//	/* ������һ������ѭ�������ܷ��� */
//	while(1)
//	{
//		/* K1 ������ */
//		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )
//		{
//			printf("����LED����\n");
//			uwRet = LOS_TaskSuspend(Connect_Init_Task_Handle);/* ����LED1���� */
//			if(LOS_OK == uwRet)
//			{
//				printf("����LED����ɹ���\n");
//			}
//		}
//		/* K2 ������ */
//		else if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON ) 
//		{
//			printf("�ָ�LED����\n");
//			uwRet = LOS_TaskResume(Connect_Init_Task_Handle); /* �ָ�LED1���� */
//			if(LOS_OK == uwRet)
//			{
//				printf("�ָ�LED����ɹ���\n");
//			}
//			
//		}
//		LOS_TaskDelay(20);   /* 20msɨ��һ�� */
//	}
//}

//static void Read_Publish_Task(void)
//{	
//	DHT11_Data_TypeDef DHT11_Data;
//	extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
//	ADC_Data_TypeDef ADC_Data;
//	
//	char mqtt_message[200];
//	/* ������һ������ѭ�������ܷ��� */
//	while(1)
//	{
//		LED1_TOGGLE;			//LED��ת
////		if( DHT11_Read_TempAndHumidity ( &DHT11_Data ) == SUCCESS)
////		{
////			printf("\r\n ����ʪ��Ϊ%d.%d ��RH �������¶�Ϊ %d.%d�� \r\n",\
////			DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
////		}			
////		else
////		{
////				printf("Read DHT11 ERROR!\r\n");
////		}
////		ADC_Data.light = (-((float)ADC_ConvertedValue[0] /100) + 45)*3;
////		ADC_Data.soil = (-((float)ADC_ConvertedValue[1] /100) + 45)*3;	
////		Mqtt_Publish(&DHT11_Data, ADC_Data.light, ADC_Data.soil);
////		printf("\r\n ��ǿΪ%.2f LUX������ʪ��Ϊ %.2f \r\n",\
////		ADC_Data.light, ADC_Data.soil);
//		LOS_TaskDelay(5000); // ÿ���ȡһ��
//	}
//}

//static void Subscribe_React_Task(void)
//{
//	UINT8 i, j;
//	const CHAR *FillLight= "Lamp";
//	const CHAR *Sprink= "Water";
//	UINT32 uwRet = LOS_OK;		
//	UINT32 send_data = 0;
//	
//	Mqtt_Subscribe();
//	printf("\r\n���ĳɹ�! \r\n");
//	
//	while(1)
//	{
//		UINTPTR uvIntSave;
//		uvIntSave = LOS_IntLock();		//���ж�
//		LED2_TOGGLE;
//		// ��������
//		if(strEsp8266_Fram_Record .InfBit .FramFinishFlag)
//		{
//			strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';
//			printf("\r\n len : %d\r\n",strEsp8266_Fram_Record.InfBit.FramLength);
//			for(i=100;i< strEsp8266_Fram_Record.InfBit.FramLength;i++)
//			{
//				printf("%c",strEsp8266_Fram_Record.Data_RX_BUF[i]);
//			}
//			for(i = 100;i < strEsp8266_Fram_Record.InfBit.FramLength; i++)
//			{
//				for(j = 0;j < 5; j++)
//				{			
//					if(strEsp8266_Fram_Record.Data_RX_BUF[i + j] != FillLight[j] && strEsp8266_Fram_Record.Data_RX_BUF[i+j] != Sprink[j]) 
//					{
//						break;
//					} 
//				}
//				// �������ݺ���÷���
//				if(j == 4 || j==5)
//				{
//					Call_Service(j,i);
//					break;
//				}
//			}
//			// ��Ҫ����
//			strEsp8266_Fram_Record .InfBit .FramLength = 0; 
//	    strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;	
//		}
//		
//		LOS_IntRestore(uvIntSave);	//���ж�
//		LOS_TaskDelay(2000); 
//	}
//}

//static void Execute_FillLight_Task(void)
//{
//	UINT32 uwRet = LOS_OK;
//	UINT32 *command;
//	while(1)
//	{
//		/* ���ж�ȡ�����գ����ȴ�ʱ��Ϊһֱ�ȴ� */
//		uwRet = LOS_QueueRead(Lamp_Queue_Handle,	/* ��ȡ�����գ����е�ID(���) */
//													&command,			/* ��ȡ�����գ������ݱ���λ�� */
//													MESSAGE_QUEUE_SIZE,		/* ��ȡ�����գ������ݵĳ��� */
//													LOS_WAIT_FOREVER); 	/* �ȴ�ʱ�䣺һֱ�� */
//		if(LOS_OK == uwRet)
//		{
//			printf("\r\n���ν��յ���������: %x\n", *command);
//			if(command == 0) 
//			{
//				LAMP_OFF;
//			}else if(command > 0)
//			{
//				LAMP_ON;
//			}
//		}
//		else
//		{
//			printf("���ݽ��ճ���,�������0x%X\n",uwRet);
//		}
//		LOS_TaskDelay(500); 
//	}
//}

//static void Execute_Sprink_Task(void)
//{
//	UINT32 uwRet = LOS_OK;
//	UINT32 *command;
//	while(1)
//	{
//		/* ���ж�ȡ�����գ����ȴ�ʱ��Ϊһֱ�ȴ� */
//		uwRet = LOS_QueueRead(Water_Queue_Handle,	/* ��ȡ�����գ����е�ID(���) */
//													&command,			/* ��ȡ�����գ������ݱ���λ�� */
//													MESSAGE_QUEUE_SIZE,		/* ��ȡ�����գ������ݵĳ��� */
//													LOS_WAIT_FOREVER); 	/* �ȴ�ʱ�䣺һֱ�� */
//		if(LOS_OK == uwRet)
//		{
//			printf("\r\n���ν��յ���������: %x\n",*command);
//		}
//		else
//		{
//			printf("���ݽ��ճ���,�������0x%X\n",uwRet);
//		}
//		LOS_TaskDelay(500); 
//	}
//}
///*******************************************************************

//                    �弶�����ʼ��

//  ******************************************************************/
//static void BSP_Init(void)
//{
//	/*
//	 * STM32�ж����ȼ�����Ϊ4����4bit��������ʾ��ռ���ȼ�����ΧΪ��0~15
//	 */
//	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
//	
//	/* LED ��ʼ�� */
//	LED_GPIO_Config();

//	/* ���ڳ�ʼ��	*/
//	USART_Config();

//  /* ������ʼ�� */
//	Key_GPIO_Config();
//	
//  /* ������ʼ�� */
//	DHT11_Init ();
//  /* esp8266��ʼ�� */	
//	ESP8266_Init();
//  /* ��ȡ����ʪ�ȴ������͹��������� */	
//	ADCx_Init();
//	/* ����Ƴ�ʼ�� */	
//	Lamp_Init();
//	
//}

//static void Call_Service(UINT8 type, UINT8 len) 
//{	
//	UINT32 uwRet = LOS_OK;		
//	UINT32 send_data = 3;
//	// ���������Ҫ������
//	printf("\r\n receive data: %c ", strEsp8266_Fram_Record.Data_RX_BUF[len + type + 2]);

//	//send_data = (UINT32)strEsp8266_Fram_Record.Data_RX_BUF[len + type + 2] - 48;
//	printf("\r\n senddata: %d ", send_data);
//	// ���͵�ִ��ģ�����Ϣ����
//	if(type == SPRINK)
//	{
//		uwRet = LOS_QueueWrite(	Water_Queue_Handle,	/* д�루���ͣ����е�ID(���) */
//												&send_data,				/* д�루���ͣ������� */
//												sizeof(send_data),	/* ���ݵĳ��� */
//												0);									/* �ȴ�ʱ��Ϊ 0  */
//	printf("\r\n 1111111: %d ", send_data);			
//	}else if(type == FILL_LIGHT){
//		uwRet = LOS_QueueWrite(	Lamp_Queue_Handle,	/* д�루���ͣ����е�ID(���) */
//												&send_data,				/* д�루���ͣ������� */
//												sizeof(send_data),	/* ���ݵĳ��� */
//												0);									/* �ȴ�ʱ��Ϊ 0  */
//		printf("\r\n 22222222: %d ", send_data);					
//	}
//	if(LOS_OK != uwRet)
//	{
//		printf("\r\n ���ݲ��ܷ��͵���Ϣ���У��������0x%X\n",uwRet);
//	}
//}

///*********************************************END OF FILE**********************/



///* LiteOS ͷ�ļ� */
//#include "los_sys.h"
//#include "los_task.h"
//#include "los_tick.h"
//#include "los_queue.h"
///* �弶����ͷ�ļ� */
//#include "bsp_usart.h"
//#include "bsp_led.h"
//#include "bsp_key.h" 
//#include "bsp_esp8266.h"
//#include "wifi.h"
//#include "mqtt.h"
//#include "bsp_dht11.h"
//#include "bsp_adc.h"

///********************************** ������ *************************************/
///* ���������� */
//UINT32 Key_Task_Handle;
//UINT32 Connect_Init_Task_Handle;
//UINT32 Read_Publish_Task_Handle;
//UINT32 Mqtt_SendHeatbeat_Task_Handle;
//UINT32 Subscribe_React_Task_Handle;
//UINT32 Execute_FillLight_Handle;
//UINT32 Execute_Sprink_Handle;

///********************************** �������� *************************************/
//static UINT32 AppTaskCreate(void);
//static UINT32 Create_Key_Task(void);
//static UINT32 Create_Connect_Init_Task(void);
//static UINT32 Create_Read_Publish_Task(void);
//static UINT32 Create_Mqtt_SendHeatbeat_Task(void);
//static UINT32 Create_Subscribe_React_Task(void);
//static UINT32 Create_Execute_FillLight_Task(void);
//static UINT32 Create_Execute_Sprink_Task(void);

//static void BSP_Init(void);
//static void Key_Task(void);
//static void Connect_Init_Task(void);
//static void Read_Publish_Task(void);
//static void Mqtt_SendHeatbeat_Task(void);
//static void Subscribe_React_Task(void);
//static void Execute_FillLight_Task(void);
//static void Execute_Sprink_Task(void);
//static void Call_Service(UINT8 type, UINT8 len);
//	

//// ��������
//#define FILL_LIGHT 4
//#define SPRINK 5

//volatile UINT32 receive_data = 0;
///***************************************************************
//  * @brief  ������
//  * @param  ��
//  * @retval ��
//  * @note   ��һ����������Ӳ����ʼ�� 
//			�ڶ���������APPӦ������
//			������������LiteOS����ʼ��������ȣ�����ʧ�������������Ϣ
//  **************************************************************/
//int main(void)
//{	
//	UINT32 uwRet = LOS_OK;  //����һ�����񴴽��ķ���ֵ��Ĭ��Ϊ�����ɹ�
//	
//	/* ������س�ʼ�� */
//  BSP_Init();
//	printf("\n************* ��ʼ���ɹ���*************\n");

//	/* LiteOS �ں˳�ʼ�� */
//	uwRet = LOS_KernelInit();
//	
//  if (uwRet != LOS_OK)
//  {
//		printf("LiteOS ���ĳ�ʼ��ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return LOS_NOK;
//  }
//	
//	uwRet = AppTaskCreate();
//	if (uwRet != LOS_OK)
//  {
//		printf("AppTaskCreate��������ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return LOS_NOK;
//  }

//  /* ����LiteOS������� */
//  LOS_Start();
//	
//	//��������²���ִ�е�����
//	while(1);
//}


///*********************************************************************

//							        ���������������������

//  *******************************************************************/
//static UINT32 AppTaskCreate(void)
//{
//	/* ����һ���������ͱ�������ʼ��ΪLOS_OK */
//	UINT32 uwRet = LOS_OK;
//	
//	uwRet = Create_Key_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Key_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return uwRet;
//  }
//	
//	uwRet = Create_Connect_Init_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Connect_Init_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return uwRet;
//  }
//	
//	uwRet = Create_Execute_FillLight_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Execute_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return uwRet;
//  }
//	uwRet = Create_Execute_Sprink_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Execute_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		return uwRet;
//  }
//	return LOS_OK;
//}


///******************************************************************

//														��������

//  ******************************************************************/
//static UINT32 Create_Connect_Init_Task()
//{
//	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
//	UINT32 uwRet = LOS_OK;			
//	
//	//����һ�����ڴ�������Ĳ����ṹ��
//	TSK_INIT_PARAM_S task_init_param;	

//	task_init_param.usTaskPrio = 1;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Connect_Init_Task";/* ������ */
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Connect_Init_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;		/* ��ջ��С */

//	uwRet = LOS_TaskCreate(&Connect_Init_Task_Handle, &task_init_param);/* �������� */
//	return uwRet;
//}

//static UINT32 Create_Key_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 4;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Key_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Key_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Key_Task_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}

//static UINT32 Create_Read_Publish_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Read_Publish_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Read_Publish_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Read_Publish_Task_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}

//static UINT32 Create_Mqtt_SendHeatbeat_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 5;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Mqtt_SendHeatbeat_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Mqtt_SendHeatbeat_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Mqtt_SendHeatbeat_Task_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}

//static UINT32 Create_Subscribe_React_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Subscribe_React_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Subscribe_React_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Subscribe_React_Task_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}

//static UINT32 Create_Execute_FillLight_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 1;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Execute_FillLight_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Execute_FillLight_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Execute_FillLight_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}

//static UINT32 Create_Execute_Sprink_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* �������ȼ�����ֵԽС�����ȼ�Խ�� */
//	task_init_param.pcName = "Execute_Sprink_Task";	/* ������*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Execute_Sprink_Task;/* ��������� */
//	task_init_param.uwStackSize = 1024;	/* ��ջ��С */
//	
//	uwRet = LOS_TaskCreate(&Execute_Sprink_Handle, &task_init_param);/* �������� */

//	return uwRet;
//}
///******************************************************************
//  
//														����ʵ��

//  *****************************************************************/
//static void Connect_Init_Task(void)
//{
//	UINT32 uwRet = LOS_OK;
//  /* ������һ������ѭ�������ܷ��� */
//	while(1)
//	{
//		Wifi_Config();			//����wifi
//		Server_Connect(); 		//���ӷ�����
//		LOS_TaskDelay(1000);		
//		Mqtt_Connect();
//		LOS_TaskDelay(1000);
//		
//		/********************* ������������������ **************************/
//		uwRet = Create_Mqtt_SendHeatbeat_Task(); 
//		if (uwRet != LOS_OK)
//		{
//			printf("Mqtt_SendHeatbeat���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		}else {
//			printf("������������ɹ���\n");
//		}
//		
//		/*************** ������ȡ���ݲ����͵��ƶ˵����� *********************/
//		uwRet = Create_Read_Publish_Task();
//		if (uwRet != LOS_OK)
//		{
//			printf("Read_Publish_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		}else {
//			printf("������ȡdht11����������ɹ���\n");
//		}
//		
//		/*************** ���������¼�����Ӧ������ *********************/
//		uwRet = Create_Subscribe_React_Task();
//		if (uwRet != LOS_OK)
//		{
//			printf("Subscribe_React_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
//		}else {
//			printf("����������Ӧ����ɹ���\n");
//		}
//		LOS_TaskDelete(Connect_Init_Task_Handle);			//ɾ������
//	}
//}

//static void Mqtt_SendHeatbeat_Task(void)
//{
//  /* ������һ������ѭ�������ܷ��� */
//	while(1)
//	{
//		Mqtt_SendHeatbeat();
//		printf("\n���������ɹ�\n");
//		LOS_TaskDelay(30000);	
//	}
//}

//static void Key_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	
//	/* ������һ������ѭ�������ܷ��� */
//	while(1)
//	{
//		/* K1 ������ */
//		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )
//		{
//			printf("����LED����\n");
//			uwRet = LOS_TaskSuspend(Connect_Init_Task_Handle);/* ����LED1���� */
//			if(LOS_OK == uwRet)
//			{
//				printf("����LED����ɹ���\n");
//			}
//		}
//		/* K2 ������ */
//		else if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON ) 
//		{
//			printf("�ָ�LED����\n");
//			uwRet = LOS_TaskResume(Connect_Init_Task_Handle); /* �ָ�LED1���� */
//			if(LOS_OK == uwRet)
//			{
//				printf("�ָ�LED����ɹ���\n");
//			}
//			
//		}
//		LOS_TaskDelay(20);   /* 20msɨ��һ�� */
//	}
//}

//static void Read_Publish_Task(void)
//{	
//	DHT11_Data_TypeDef DHT11_Data;
//	extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
//	ADC_Data_TypeDef ADC_Data;
//	
//	char mqtt_message[200];
//	/* ������һ������ѭ�������ܷ��� */
//	while(1)
//	{
//		LED1_TOGGLE;			//LED��ת
////		if( DHT11_Read_TempAndHumidity ( &DHT11_Data ) == SUCCESS)
////		{
////			printf("\r\n ����ʪ��Ϊ%d.%d ��RH �������¶�Ϊ %d.%d�� \r\n",\
////			DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
////		}			
////		else
////		{
////				printf("Read DHT11 ERROR!\r\n");
////		}
////		ADC_Data.light = (-((float)ADC_ConvertedValue[0] /100) + 45)*3;
////		ADC_Data.soil = (-((float)ADC_ConvertedValue[1] /100) + 45)*3;	
////		Mqtt_Publish(&DHT11_Data, ADC_Data.light, ADC_Data.soil);
////		printf("\r\n ��ǿΪ%.2f LUX������ʪ��Ϊ %.2f \r\n",\
////		ADC_Data.light, ADC_Data.soil);
//		LOS_TaskDelay(5000); // ÿ���ȡһ��
//	}
//}

//static void Subscribe_React_Task(void)
//{
//	UINT8 i, j;
//	const CHAR *FillLight= "Lamp";
//	const CHAR *Sprink= "Water";
//	UINT32 uwRet = LOS_OK;		
//	UINT32 send_data = 0;
//	
//	Mqtt_Subscribe();
//	printf("\r\n���ĳɹ�! \r\n");
//	
//	while(1)
//	{
//		UINTPTR uvIntSave;
//		uvIntSave = LOS_IntLock();		//���ж�
//		LED2_TOGGLE;
//		// ��������
//		if(strEsp8266_Fram_Record .InfBit .FramFinishFlag)
//		{
//			strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';
//			printf("\r\n len : %d\r\n",strEsp8266_Fram_Record.InfBit.FramLength);
//			for(i=100;i< strEsp8266_Fram_Record.InfBit.FramLength;i++)
//			{
//				printf("%c",strEsp8266_Fram_Record.Data_RX_BUF[i]);
//			}
//			for(i = 100;i < strEsp8266_Fram_Record.InfBit.FramLength; i++)
//			{
//				for(j = 0;j < 5; j++)
//				{			
//					if(strEsp8266_Fram_Record.Data_RX_BUF[i + j] != FillLight[j] && strEsp8266_Fram_Record.Data_RX_BUF[i+j] != Sprink[j]) 
//					{
//						break;
//					} 
//				}
//				// �������ݺ���÷���
//				if(j == 4 || j==5)
//				{
//					Call_Service(j,i);
//					break;
//				}
//			}
//			// ��Ҫ����
//			strEsp8266_Fram_Record .InfBit .FramLength = 0; 
//	    strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;	
//		}
//		
//		LOS_IntRestore(uvIntSave);	//���ж�
//		LOS_TaskDelay(2000); 
//	}
//}

//static void Execute_FillLight_Task(void)
//{
//	UINT32 uwRet = LOS_OK;
//	UINT32 *command;
//	while(1)
//	{

//	}
//}

//static void Execute_Sprink_Task(void)
//{
//	UINT32 uwRet = LOS_OK;
//	UINT32 *command;
//	while(1)
//	{
//		
//	}
//}
///*******************************************************************

//                    �弶�����ʼ��

//  ******************************************************************/
//static void BSP_Init(void)
//{
//	/*
//	 * STM32�ж����ȼ�����Ϊ4����4bit��������ʾ��ռ���ȼ�����ΧΪ��0~15
//	 */
//	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
//	
//	/* LED ��ʼ�� */
//	LED_GPIO_Config();

//	/* ���ڳ�ʼ��	*/
//	USART_Config();

//  /* ������ʼ�� */
//	Key_GPIO_Config();
//	
//  /* ������ʼ�� */
//	DHT11_Init ();
//  /* esp8266��ʼ�� */	
//	ESP8266_Init();
//  /* ��ȡ����ʪ�ȴ������͹��������� */	
//	ADCx_Init();
//	/* ����Ƴ�ʼ�� */	
//	Lamp_Init();
//	
//}

//static void Call_Service(UINT8 type, UINT8 len) 
//{	
//	UINT32 uwRet = LOS_OK;		
//	// ���������Ҫ������
//	printf("\r\n receive data: %c ", strEsp8266_Fram_Record.Data_RX_BUF[len + type + 2]);

//	receive_data = (UINT32)strEsp8266_Fram_Record.Data_RX_BUF[len + type + 2] - 48;
//	printf("\r\n senddata: %d ", receive_data);
//	// ���͵�ִ��ģ�����Ϣ����
//	if(type == SPRINK)
//	{
//		
//		
//	}else if(type == FILL_LIGHT){
//	
//	}
//	if(LOS_OK != uwRet)
//	{
//		printf("\r\n ���ݲ��ܷ��͵���Ϣ���У��������0x%X\n",uwRet);
//	}
//}

///*********************************************END OF FILE**********************/



