
///* LiteOS 头文件 */
//#include "los_sys.h"
//#include "los_task.h"
//#include "los_tick.h"
//#include "los_queue.h"
///* 板级外设头文件 */
//#include "bsp_usart.h"
//#include "bsp_led.h"
//#include "bsp_key.h" 
//#include "bsp_esp8266.h"
//#include "wifi.h"
//#include "mqtt.h"
//#include "bsp_dht11.h"
//#include "bsp_adc.h"

///********************************** 任务句柄 *************************************/
///* 定义任务句柄 */
//UINT32 Key_Task_Handle;
//UINT32 Connect_Init_Task_Handle;
//UINT32 Read_Publish_Task_Handle;
//UINT32 Mqtt_SendHeatbeat_Task_Handle;
//UINT32 Subscribe_React_Task_Handle;
//UINT32 Execute_FillLight_Handle;
//UINT32 Execute_Sprink_Handle;

///********************************** 函数声明 *************************************/
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
// /* 定义消息队列的句柄 */
//UINT32 Lamp_Queue_Handle;
//UINT32 Water_Queue_Handle;

///* 定义消息队列长度 */
//#define  MESSAGE_Queue_LEN  	10
//#define  MESSAGE_QUEUE_SIZE   10

//// 服务类型
//#define FILL_LIGHT 4
//#define SPRINK 5

//UINT32 receive_data = 0;
///***************************************************************
//  * @brief  主函数
//  * @param  无
//  * @retval 无
//  * @note   第一步：开发板硬件初始化 
//			第二步：创建APP应用任务
//			第三步：启动LiteOS，开始多任务调度，启动失败则输出错误信息
//  **************************************************************/
//int main(void)
//{	
//	UINT32 uwRet = LOS_OK;  //定义一个任务创建的返回值，默认为创建成功
//	
//	/* 板载相关初始化 */
//  BSP_Init();
//	printf("\n************* 初始化成功！*************\n");

//	/* LiteOS 内核初始化 */
//	uwRet = LOS_KernelInit();
//	
//  if (uwRet != LOS_OK)
//  {
//		printf("LiteOS 核心初始化失败！失败代码0x%X\n",uwRet);
//		return LOS_NOK;
//  }
//	
//	uwRet = AppTaskCreate();
//	if (uwRet != LOS_OK)
//  {
//		printf("AppTaskCreate创建任务失败！失败代码0x%X\n",uwRet);
//		return LOS_NOK;
//  }

//  /* 开启LiteOS任务调度 */
//  LOS_Start();
//	
//	//正常情况下不会执行到这里
//	while(1);
//}


///*********************************************************************

//							        用来创建所有任务的任务

//  *******************************************************************/
//static UINT32 AppTaskCreate(void)
//{
//	/* 定义一个返回类型变量，初始化为LOS_OK */
//	UINT32 uwRet = LOS_OK;
//	
//		/* 创建两个队列，接收数据交给执行模块执行*/
//	uwRet = LOS_QueueCreate("Lamp_Queue",				/* 队列的名称 */
//													MESSAGE_Queue_LEN,			/* 队列的长度 */
//													&Lamp_Queue_Handle,	/* 队列的ID(句柄) */
//													0,						/* 队列模式，官方暂时未使用 */
//													MESSAGE_QUEUE_SIZE);	/* 节点大小，单位为字节 */
//	if (uwRet != LOS_OK)
//  {
//		printf("Lamp_Queue队列创建失败！失败代码0x%X\n",uwRet);
//		return uwRet;
//  }
//	uwRet = LOS_QueueCreate("Water_Queue",				/* 队列的名称 */
//													MESSAGE_Queue_LEN,			/* 队列的长度 */
//													&Water_Queue_Handle,	/* 队列的ID(句柄) */
//													0,						/* 队列模式，官方暂时未使用 */
//													MESSAGE_QUEUE_SIZE);	/* 节点大小，单位为字节 */
//	if (uwRet != LOS_OK)
//  {
//		printf("Water_Queue队列创建失败！失败代码0x%X\n",uwRet);
//		return uwRet;
//  }
//	
//	uwRet = Create_Key_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Key_Task任务创建失败！失败代码0x%X\n",uwRet);
//		return uwRet;
//  }
//	
//	uwRet = Create_Connect_Init_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Connect_Init_Task任务创建失败！失败代码0x%X\n",uwRet);
//		return uwRet;
//  }
//	
//	uwRet = Create_Execute_FillLight_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Execute_Task任务创建失败！失败代码0x%X\n",uwRet);
//		return uwRet;
//  }
//	uwRet = Create_Execute_Sprink_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Execute_Task任务创建失败！失败代码0x%X\n",uwRet);
//		return uwRet;
//  }
//	return LOS_OK;
//}


///******************************************************************

//														创建任务

//  ******************************************************************/
//static UINT32 Create_Connect_Init_Task()
//{
//	//定义一个创建任务的返回类型，初始化为创建成功的返回值
//	UINT32 uwRet = LOS_OK;			
//	
//	//定义一个用于创建任务的参数结构体
//	TSK_INIT_PARAM_S task_init_param;	

//	task_init_param.usTaskPrio = 1;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Connect_Init_Task";/* 任务名 */
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Connect_Init_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;		/* 堆栈大小 */

//	uwRet = LOS_TaskCreate(&Connect_Init_Task_Handle, &task_init_param);/* 创建任务 */
//	return uwRet;
//}

//static UINT32 Create_Key_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 4;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Key_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Key_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Key_Task_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}

//static UINT32 Create_Read_Publish_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Read_Publish_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Read_Publish_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Read_Publish_Task_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}

//static UINT32 Create_Mqtt_SendHeatbeat_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 5;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Mqtt_SendHeatbeat_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Mqtt_SendHeatbeat_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Mqtt_SendHeatbeat_Task_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}

//static UINT32 Create_Subscribe_React_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Subscribe_React_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Subscribe_React_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Subscribe_React_Task_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}

//static UINT32 Create_Execute_FillLight_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 1;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Execute_FillLight_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Execute_FillLight_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Execute_FillLight_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}

//static UINT32 Create_Execute_Sprink_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Execute_Sprink_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Execute_Sprink_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Execute_Sprink_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}
///******************************************************************
//  
//														任务实现

//  *****************************************************************/
//static void Connect_Init_Task(void)
//{
//	UINT32 uwRet = LOS_OK;
//  /* 任务都是一个无限循环，不能返回 */
//	while(1)
//	{
//		Wifi_Config();			//配置wifi
//		Server_Connect(); 		//连接服务器
//		LOS_TaskDelay(1000);		
//		Mqtt_Connect();
//		LOS_TaskDelay(1000);
//		
//		/********************* 创建发送心跳的任务 **************************/
//		uwRet = Create_Mqtt_SendHeatbeat_Task(); 
//		if (uwRet != LOS_OK)
//		{
//			printf("Mqtt_SendHeatbeat任务创建失败！失败代码0x%X\n",uwRet);
//		}else {
//			printf("创建心跳任务成功！\n");
//		}
//		
//		/*************** 创建读取数据并发送到云端的任务 *********************/
//		uwRet = Create_Read_Publish_Task();
//		if (uwRet != LOS_OK)
//		{
//			printf("Read_Publish_Task任务创建失败！失败代码0x%X\n",uwRet);
//		}else {
//			printf("创建读取dht11传感器任务成功！\n");
//		}
//		
//		/*************** 创建订阅事件并响应的任务 *********************/
//		uwRet = Create_Subscribe_React_Task();
//		if (uwRet != LOS_OK)
//		{
//			printf("Subscribe_React_Task任务创建失败！失败代码0x%X\n",uwRet);
//		}else {
//			printf("创建订阅响应任务成功！\n");
//		}
//		LOS_TaskDelete(Connect_Init_Task_Handle);			//删除任务
//	}
//}

//static void Mqtt_SendHeatbeat_Task(void)
//{
//  /* 任务都是一个无限循环，不能返回 */
//	while(1)
//	{
//		Mqtt_SendHeatbeat();
//		printf("\n发送心跳成功\n");
//		LOS_TaskDelay(30000);	
//	}
//}

//static void Key_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	
//	/* 任务都是一个无限循环，不能返回 */
//	while(1)
//	{
//		/* K1 被按下 */
//		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )
//		{
//			printf("挂起LED任务！\n");
//			uwRet = LOS_TaskSuspend(Connect_Init_Task_Handle);/* 挂起LED1任务 */
//			if(LOS_OK == uwRet)
//			{
//				printf("挂起LED任务成功！\n");
//			}
//		}
//		/* K2 被按下 */
//		else if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON ) 
//		{
//			printf("恢复LED任务！\n");
//			uwRet = LOS_TaskResume(Connect_Init_Task_Handle); /* 恢复LED1任务 */
//			if(LOS_OK == uwRet)
//			{
//				printf("恢复LED任务成功！\n");
//			}
//			
//		}
//		LOS_TaskDelay(20);   /* 20ms扫描一次 */
//	}
//}

//static void Read_Publish_Task(void)
//{	
//	DHT11_Data_TypeDef DHT11_Data;
//	extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
//	ADC_Data_TypeDef ADC_Data;
//	
//	char mqtt_message[200];
//	/* 任务都是一个无限循环，不能返回 */
//	while(1)
//	{
//		LED1_TOGGLE;			//LED翻转
////		if( DHT11_Read_TempAndHumidity ( &DHT11_Data ) == SUCCESS)
////		{
////			printf("\r\n 环境湿度为%d.%d ％RH ，环境温度为 %d.%d℃ \r\n",\
////			DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
////		}			
////		else
////		{
////				printf("Read DHT11 ERROR!\r\n");
////		}
////		ADC_Data.light = (-((float)ADC_ConvertedValue[0] /100) + 45)*3;
////		ADC_Data.soil = (-((float)ADC_ConvertedValue[1] /100) + 45)*3;	
////		Mqtt_Publish(&DHT11_Data, ADC_Data.light, ADC_Data.soil);
////		printf("\r\n 光强为%.2f LUX，土壤湿度为 %.2f \r\n",\
////		ADC_Data.light, ADC_Data.soil);
//		LOS_TaskDelay(5000); // 每秒读取一次
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
//	printf("\r\n订阅成功! \r\n");
//	
//	while(1)
//	{
//		UINTPTR uvIntSave;
//		uvIntSave = LOS_IntLock();		//关中断
//		LED2_TOGGLE;
//		// 处理数据
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
//				// 解析数据后调用服务
//				if(j == 4 || j==5)
//				{
//					Call_Service(j,i);
//					break;
//				}
//			}
//			// 需要重置
//			strEsp8266_Fram_Record .InfBit .FramLength = 0; 
//	    strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;	
//		}
//		
//		LOS_IntRestore(uvIntSave);	//开中断
//		LOS_TaskDelay(2000); 
//	}
//}

//static void Execute_FillLight_Task(void)
//{
//	UINT32 uwRet = LOS_OK;
//	UINT32 *command;
//	while(1)
//	{
//		/* 队列读取（接收），等待时间为一直等待 */
//		uwRet = LOS_QueueRead(Lamp_Queue_Handle,	/* 读取（接收）队列的ID(句柄) */
//													&command,			/* 读取（接收）的数据保存位置 */
//													MESSAGE_QUEUE_SIZE,		/* 读取（接收）的数据的长度 */
//													LOS_WAIT_FOREVER); 	/* 等待时间：一直等 */
//		if(LOS_OK == uwRet)
//		{
//			printf("\r\n本次接收到的数据是: %x\n", *command);
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
//			printf("数据接收出错,错误代码0x%X\n",uwRet);
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
//		/* 队列读取（接收），等待时间为一直等待 */
//		uwRet = LOS_QueueRead(Water_Queue_Handle,	/* 读取（接收）队列的ID(句柄) */
//													&command,			/* 读取（接收）的数据保存位置 */
//													MESSAGE_QUEUE_SIZE,		/* 读取（接收）的数据的长度 */
//													LOS_WAIT_FOREVER); 	/* 等待时间：一直等 */
//		if(LOS_OK == uwRet)
//		{
//			printf("\r\n本次接收到的数据是: %x\n",*command);
//		}
//		else
//		{
//			printf("数据接收出错,错误代码0x%X\n",uwRet);
//		}
//		LOS_TaskDelay(500); 
//	}
//}
///*******************************************************************

//                    板级外设初始化

//  ******************************************************************/
//static void BSP_Init(void)
//{
//	/*
//	 * STM32中断优先级分组为4，即4bit都用来表示抢占优先级，范围为：0~15
//	 */
//	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
//	
//	/* LED 初始化 */
//	LED_GPIO_Config();

//	/* 串口初始化	*/
//	USART_Config();

//  /* 按键初始化 */
//	Key_GPIO_Config();
//	
//  /* 按键初始化 */
//	DHT11_Init ();
//  /* esp8266初始化 */	
//	ESP8266_Init();
//  /* 读取土壤湿度传感器和光敏传感器 */	
//	ADCx_Init();
//	/* 补光灯初始化 */	
//	Lamp_Init();
//	
//}

//static void Call_Service(UINT8 type, UINT8 len) 
//{	
//	UINT32 uwRet = LOS_OK;		
//	UINT32 send_data = 3;
//	// 这个才是需要的数据
//	printf("\r\n receive data: %c ", strEsp8266_Fram_Record.Data_RX_BUF[len + type + 2]);

//	//send_data = (UINT32)strEsp8266_Fram_Record.Data_RX_BUF[len + type + 2] - 48;
//	printf("\r\n senddata: %d ", send_data);
//	// 发送到执行模块的消息队列
//	if(type == SPRINK)
//	{
//		uwRet = LOS_QueueWrite(	Water_Queue_Handle,	/* 写入（发送）队列的ID(句柄) */
//												&send_data,				/* 写入（发送）的数据 */
//												sizeof(send_data),	/* 数据的长度 */
//												0);									/* 等待时间为 0  */
//	printf("\r\n 1111111: %d ", send_data);			
//	}else if(type == FILL_LIGHT){
//		uwRet = LOS_QueueWrite(	Lamp_Queue_Handle,	/* 写入（发送）队列的ID(句柄) */
//												&send_data,				/* 写入（发送）的数据 */
//												sizeof(send_data),	/* 数据的长度 */
//												0);									/* 等待时间为 0  */
//		printf("\r\n 22222222: %d ", send_data);					
//	}
//	if(LOS_OK != uwRet)
//	{
//		printf("\r\n 数据不能发送到消息队列！错误代码0x%X\n",uwRet);
//	}
//}

///*********************************************END OF FILE**********************/



///* LiteOS 头文件 */
//#include "los_sys.h"
//#include "los_task.h"
//#include "los_tick.h"
//#include "los_queue.h"
///* 板级外设头文件 */
//#include "bsp_usart.h"
//#include "bsp_led.h"
//#include "bsp_key.h" 
//#include "bsp_esp8266.h"
//#include "wifi.h"
//#include "mqtt.h"
//#include "bsp_dht11.h"
//#include "bsp_adc.h"

///********************************** 任务句柄 *************************************/
///* 定义任务句柄 */
//UINT32 Key_Task_Handle;
//UINT32 Connect_Init_Task_Handle;
//UINT32 Read_Publish_Task_Handle;
//UINT32 Mqtt_SendHeatbeat_Task_Handle;
//UINT32 Subscribe_React_Task_Handle;
//UINT32 Execute_FillLight_Handle;
//UINT32 Execute_Sprink_Handle;

///********************************** 函数声明 *************************************/
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

//// 服务类型
//#define FILL_LIGHT 4
//#define SPRINK 5

//volatile UINT32 receive_data = 0;
///***************************************************************
//  * @brief  主函数
//  * @param  无
//  * @retval 无
//  * @note   第一步：开发板硬件初始化 
//			第二步：创建APP应用任务
//			第三步：启动LiteOS，开始多任务调度，启动失败则输出错误信息
//  **************************************************************/
//int main(void)
//{	
//	UINT32 uwRet = LOS_OK;  //定义一个任务创建的返回值，默认为创建成功
//	
//	/* 板载相关初始化 */
//  BSP_Init();
//	printf("\n************* 初始化成功！*************\n");

//	/* LiteOS 内核初始化 */
//	uwRet = LOS_KernelInit();
//	
//  if (uwRet != LOS_OK)
//  {
//		printf("LiteOS 核心初始化失败！失败代码0x%X\n",uwRet);
//		return LOS_NOK;
//  }
//	
//	uwRet = AppTaskCreate();
//	if (uwRet != LOS_OK)
//  {
//		printf("AppTaskCreate创建任务失败！失败代码0x%X\n",uwRet);
//		return LOS_NOK;
//  }

//  /* 开启LiteOS任务调度 */
//  LOS_Start();
//	
//	//正常情况下不会执行到这里
//	while(1);
//}


///*********************************************************************

//							        用来创建所有任务的任务

//  *******************************************************************/
//static UINT32 AppTaskCreate(void)
//{
//	/* 定义一个返回类型变量，初始化为LOS_OK */
//	UINT32 uwRet = LOS_OK;
//	
//	uwRet = Create_Key_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Key_Task任务创建失败！失败代码0x%X\n",uwRet);
//		return uwRet;
//  }
//	
//	uwRet = Create_Connect_Init_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Connect_Init_Task任务创建失败！失败代码0x%X\n",uwRet);
//		return uwRet;
//  }
//	
//	uwRet = Create_Execute_FillLight_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Execute_Task任务创建失败！失败代码0x%X\n",uwRet);
//		return uwRet;
//  }
//	uwRet = Create_Execute_Sprink_Task();
//  if (uwRet != LOS_OK)
//  {
//		printf("Execute_Task任务创建失败！失败代码0x%X\n",uwRet);
//		return uwRet;
//  }
//	return LOS_OK;
//}


///******************************************************************

//														创建任务

//  ******************************************************************/
//static UINT32 Create_Connect_Init_Task()
//{
//	//定义一个创建任务的返回类型，初始化为创建成功的返回值
//	UINT32 uwRet = LOS_OK;			
//	
//	//定义一个用于创建任务的参数结构体
//	TSK_INIT_PARAM_S task_init_param;	

//	task_init_param.usTaskPrio = 1;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Connect_Init_Task";/* 任务名 */
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Connect_Init_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;		/* 堆栈大小 */

//	uwRet = LOS_TaskCreate(&Connect_Init_Task_Handle, &task_init_param);/* 创建任务 */
//	return uwRet;
//}

//static UINT32 Create_Key_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 4;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Key_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Key_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Key_Task_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}

//static UINT32 Create_Read_Publish_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Read_Publish_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Read_Publish_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Read_Publish_Task_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}

//static UINT32 Create_Mqtt_SendHeatbeat_Task()
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 5;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Mqtt_SendHeatbeat_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Mqtt_SendHeatbeat_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Mqtt_SendHeatbeat_Task_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}

//static UINT32 Create_Subscribe_React_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Subscribe_React_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Subscribe_React_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Subscribe_React_Task_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}

//static UINT32 Create_Execute_FillLight_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 1;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Execute_FillLight_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Execute_FillLight_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Execute_FillLight_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}

//static UINT32 Create_Execute_Sprink_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	TSK_INIT_PARAM_S task_init_param;

//	task_init_param.usTaskPrio = 2;	/* 任务优先级，数值越小，优先级越高 */
//	task_init_param.pcName = "Execute_Sprink_Task";	/* 任务名*/
//	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Execute_Sprink_Task;/* 任务函数入口 */
//	task_init_param.uwStackSize = 1024;	/* 堆栈大小 */
//	
//	uwRet = LOS_TaskCreate(&Execute_Sprink_Handle, &task_init_param);/* 创建任务 */

//	return uwRet;
//}
///******************************************************************
//  
//														任务实现

//  *****************************************************************/
//static void Connect_Init_Task(void)
//{
//	UINT32 uwRet = LOS_OK;
//  /* 任务都是一个无限循环，不能返回 */
//	while(1)
//	{
//		Wifi_Config();			//配置wifi
//		Server_Connect(); 		//连接服务器
//		LOS_TaskDelay(1000);		
//		Mqtt_Connect();
//		LOS_TaskDelay(1000);
//		
//		/********************* 创建发送心跳的任务 **************************/
//		uwRet = Create_Mqtt_SendHeatbeat_Task(); 
//		if (uwRet != LOS_OK)
//		{
//			printf("Mqtt_SendHeatbeat任务创建失败！失败代码0x%X\n",uwRet);
//		}else {
//			printf("创建心跳任务成功！\n");
//		}
//		
//		/*************** 创建读取数据并发送到云端的任务 *********************/
//		uwRet = Create_Read_Publish_Task();
//		if (uwRet != LOS_OK)
//		{
//			printf("Read_Publish_Task任务创建失败！失败代码0x%X\n",uwRet);
//		}else {
//			printf("创建读取dht11传感器任务成功！\n");
//		}
//		
//		/*************** 创建订阅事件并响应的任务 *********************/
//		uwRet = Create_Subscribe_React_Task();
//		if (uwRet != LOS_OK)
//		{
//			printf("Subscribe_React_Task任务创建失败！失败代码0x%X\n",uwRet);
//		}else {
//			printf("创建订阅响应任务成功！\n");
//		}
//		LOS_TaskDelete(Connect_Init_Task_Handle);			//删除任务
//	}
//}

//static void Mqtt_SendHeatbeat_Task(void)
//{
//  /* 任务都是一个无限循环，不能返回 */
//	while(1)
//	{
//		Mqtt_SendHeatbeat();
//		printf("\n发送心跳成功\n");
//		LOS_TaskDelay(30000);	
//	}
//}

//static void Key_Task(void)
//{
//	UINT32 uwRet = LOS_OK;				
//	
//	/* 任务都是一个无限循环，不能返回 */
//	while(1)
//	{
//		/* K1 被按下 */
//		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )
//		{
//			printf("挂起LED任务！\n");
//			uwRet = LOS_TaskSuspend(Connect_Init_Task_Handle);/* 挂起LED1任务 */
//			if(LOS_OK == uwRet)
//			{
//				printf("挂起LED任务成功！\n");
//			}
//		}
//		/* K2 被按下 */
//		else if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON ) 
//		{
//			printf("恢复LED任务！\n");
//			uwRet = LOS_TaskResume(Connect_Init_Task_Handle); /* 恢复LED1任务 */
//			if(LOS_OK == uwRet)
//			{
//				printf("恢复LED任务成功！\n");
//			}
//			
//		}
//		LOS_TaskDelay(20);   /* 20ms扫描一次 */
//	}
//}

//static void Read_Publish_Task(void)
//{	
//	DHT11_Data_TypeDef DHT11_Data;
//	extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
//	ADC_Data_TypeDef ADC_Data;
//	
//	char mqtt_message[200];
//	/* 任务都是一个无限循环，不能返回 */
//	while(1)
//	{
//		LED1_TOGGLE;			//LED翻转
////		if( DHT11_Read_TempAndHumidity ( &DHT11_Data ) == SUCCESS)
////		{
////			printf("\r\n 环境湿度为%d.%d ％RH ，环境温度为 %d.%d℃ \r\n",\
////			DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
////		}			
////		else
////		{
////				printf("Read DHT11 ERROR!\r\n");
////		}
////		ADC_Data.light = (-((float)ADC_ConvertedValue[0] /100) + 45)*3;
////		ADC_Data.soil = (-((float)ADC_ConvertedValue[1] /100) + 45)*3;	
////		Mqtt_Publish(&DHT11_Data, ADC_Data.light, ADC_Data.soil);
////		printf("\r\n 光强为%.2f LUX，土壤湿度为 %.2f \r\n",\
////		ADC_Data.light, ADC_Data.soil);
//		LOS_TaskDelay(5000); // 每秒读取一次
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
//	printf("\r\n订阅成功! \r\n");
//	
//	while(1)
//	{
//		UINTPTR uvIntSave;
//		uvIntSave = LOS_IntLock();		//关中断
//		LED2_TOGGLE;
//		// 处理数据
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
//				// 解析数据后调用服务
//				if(j == 4 || j==5)
//				{
//					Call_Service(j,i);
//					break;
//				}
//			}
//			// 需要重置
//			strEsp8266_Fram_Record .InfBit .FramLength = 0; 
//	    strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;	
//		}
//		
//		LOS_IntRestore(uvIntSave);	//开中断
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

//                    板级外设初始化

//  ******************************************************************/
//static void BSP_Init(void)
//{
//	/*
//	 * STM32中断优先级分组为4，即4bit都用来表示抢占优先级，范围为：0~15
//	 */
//	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
//	
//	/* LED 初始化 */
//	LED_GPIO_Config();

//	/* 串口初始化	*/
//	USART_Config();

//  /* 按键初始化 */
//	Key_GPIO_Config();
//	
//  /* 按键初始化 */
//	DHT11_Init ();
//  /* esp8266初始化 */	
//	ESP8266_Init();
//  /* 读取土壤湿度传感器和光敏传感器 */	
//	ADCx_Init();
//	/* 补光灯初始化 */	
//	Lamp_Init();
//	
//}

//static void Call_Service(UINT8 type, UINT8 len) 
//{	
//	UINT32 uwRet = LOS_OK;		
//	// 这个才是需要的数据
//	printf("\r\n receive data: %c ", strEsp8266_Fram_Record.Data_RX_BUF[len + type + 2]);

//	receive_data = (UINT32)strEsp8266_Fram_Record.Data_RX_BUF[len + type + 2] - 48;
//	printf("\r\n senddata: %d ", receive_data);
//	// 发送到执行模块的消息队列
//	if(type == SPRINK)
//	{
//		
//		
//	}else if(type == FILL_LIGHT){
//	
//	}
//	if(LOS_OK != uwRet)
//	{
//		printf("\r\n 数据不能发送到消息队列！错误代码0x%X\n",uwRet);
//	}
//}

///*********************************************END OF FILE**********************/



