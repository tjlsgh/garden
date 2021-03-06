#ifndef  __WIFI_H
#define	 __WIFI_H



#include "stm32f10x.h"



/********************************** �û���Ҫ���õĲ���**********************************/
#define      macUser_ESP8266_ApSsid                       "pdc666"                //Ҫ���ӵ��ȵ������
#define      macUser_ESP8266_ApPwd                        "wyhhxxttxs"           //Ҫ���ӵ��ȵ����Կ

#define      macUser_ESP8266_TcpServer_IP                 "a1Dr2ppNrIc.iot-as-mqtt.cn-shanghai.aliyuncs.com"      //Ҫ���ӵķ������� IP
#define      macUser_ESP8266_TcpServer_Port               "1883"               //Ҫ���ӵķ������Ķ˿�



/********************************** �ⲿȫ�ֱ��� ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** ���Ժ������� ***************************************/
void                     ESP8266_StaTcpClient_UnvarnishTest  ( void );
void 											Server_Connect	( void );
void                     Wifi_Config  ( void );

#endif

