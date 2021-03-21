#ifndef  __MQTT_H
#define	 __MQTT_H


#include "stm32f10x.h"
#include "bsp_dht11.h"
#include <stdbool.h>

#define 	HOST_NAME 									"a1Dr2ppNrIc.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define 	HOST_PORT 									"1883"
#define 	MQTT_CLIENT_ID        			("tlg|securemode=3,signmethod=hmacsha1,timestamp=999|")
#define 	MQTT_USER_NAME							("device001&a1Dr2ppNrIc")
#define		MQTT_PASSWORD								("00FD2DDA52AB05C59FB8A7CCE918DE21384C90A3")
#define 	MQTT_PROPERTY_POST					"/sys/a1Dr2ppNrIc/device001/thing/event/property/post"
#define 	MQTT_TOPIC_FillLight    		"/sys/a1Dr2ppNrIc/device001/thing/service/FillLight"
#define 	MQTT_TOPIC_sprink    				"/sys/a1Dr2ppNrIc/device001/thing/service/Sprink"

void 		Mqtt_Connect(void);
void 		Mqtt_SendHeatbeat(void);
int 		Mqtt_Publish(DHT11_Data_TypeDef *DHT11_Data, float LightLux, float soilHumidity);
int 		Mqtt_Subscribe();
bool 		Mqtt_IsReceived();
int     Mqtt_Publish2(unsigned int Lamp_State, unsigned int Water_State);

extern volatile bool mqtt_receive_data_flag;
int str_search(const char*dststr, const char**srcstr, int num);
#endif

