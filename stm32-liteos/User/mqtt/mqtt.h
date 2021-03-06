#ifndef  __MQTT_H
#define	 __MQTT_H


#include "stm32f10x.h"
#include "bsp_dht11.h"

#define 	HOST_NAME 						"a1Dr2ppNrIc.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define 	HOST_PORT 						"1883"
#define 	MQTT_CLIENT_ID        ("tlg|securemode=3,signmethod=hmacsha1,timestamp=999|")
#define 	MQTT_USER_NAME				("device001&a1Dr2ppNrIc")
#define		MQTT_PASSWORD					("00FD2DDA52AB05C59FB8A7CCE918DE21384C90A3")
#define 	MQTT_PROPERTY_POST		"/sys/a1Dr2ppNrIc/device001/thing/event/property/post"

void 	Mqtt_Connect(void);
void Mqtt_SendHeatbeat(void);
int Mqtt_Publish(DHT11_Data_TypeDef *DHT11_Data, unsigned int LightLux, double soilHumidity);
int Mqtt_Subscribe(char *pTopic);
int Mqtt_Publish1(DHT11_Data_TypeDef *DHT11_Data, unsigned int LightLux, double soilHumidity);
#endif

