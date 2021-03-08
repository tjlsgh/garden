#include "mqtt.h"
#include "mqtt_transport.h"
#include "MQTTPacket.h"
#include "bsp_esp8266.h"
#include "bsp_dht11.h"

unsigned char buf[300];
char mqtt_message[300];
//unsigned int buflen = sizeof(buf)/sizeof(buf[0]);
unsigned int buflen = sizeof(buf);

// mqtt连接
void Mqtt_Connect(void)
{
	unsigned int  len = 0;
  MQTTPacket_connectData data = MQTTPacket_connectData_initializer;//配置可变头部分
	data.clientID.cstring = MQTT_CLIENT_ID;//设备唯一ID
	data.keepAliveInterval = 60;//保活计时器，即连续两次心跳包发送的最大时间间隔（单位：秒）
	data.cleansession = 1;//1：丢弃之前的连接信息
	data.username.cstring = MQTT_USER_NAME ;//用户名
	data.password.cstring = MQTT_PASSWORD;//密码
	data.MQTTVersion = 4;
	len = MQTTSerialize_connect(buf, buflen, &data); //构建连接报文并获取长度
	transport_sendPacketBuffer(buf,len);//通过硬件接口发送给服务器已经封装好的报文
	while(!strEsp8266_Fram_Record.InfBit.FramFinishFlag){};//等待连接成功----------此处下文会着重讲述  注释（1）
	strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;
	printf("mqtt 连接成功！\n");
}

// 发送心跳包
void Mqtt_SendHeatbeat(void)
{
	//unsigned char h_buf[200] = {0};
	u8 len = MQTTSerialize_pingreq(buf, 200);//调用mqtt心跳包封装函数
	transport_sendPacketBuffer(buf, len);//发送数据
}

// 封装数据
void Packet_Data(DHT11_Data_TypeDef *DHT11_Data, float LightLux, float soilHumidity)
{
	sprintf(mqtt_message,
				"{\"method\":\"thing.event.property.post\",\"id\":630262306,\"params\":{\
					\"EnvTemperature\": %d.%d,\
					\"EnvHumidity\":%d.%d,\
					\"LightLux\":%.2f,\
					\"soilHumidity\":%.2f\
					},\"version\":\"1.0\"}",
					DHT11_Data->temp_int,DHT11_Data->temp_deci,
					DHT11_Data->humi_int,DHT11_Data->humi_int,
					LightLux,soilHumidity
	);
}
// 发布
int Mqtt_Publish(DHT11_Data_TypeDef *DHT11_Data, float LightLux, float soilHumidity)
{
		//unsigned char buf[250] = {0};
		Packet_Data(DHT11_Data, LightLux, soilHumidity);
		MQTTString topicString = MQTTString_initializer;
		int msglen = strlen(mqtt_message);
		int buflen = sizeof(buf);
		memset(buf,0,buflen);
		topicString.cstring = MQTT_PROPERTY_POST;
		int32_t  len = MQTTSerialize_publish(buf, buflen, 0, 0, 0, 123, topicString, (unsigned char*)mqtt_message, msglen); 
		transport_sendPacketBuffer(buf,len);
		return 0;
}
//// 发布
//int Mqtt_Publish(char *pTopic,char *pMessage)
//{
//		//unsigned char buf[250] = {0};
//		MQTTString topicString = MQTTString_initializer;
//		int msglen = strlen(pMessage);
//		printf("\n ***** %d ***** \n", msglen);
//		int buflen = sizeof(buf);
//		memset(buf,0,buflen);
//		topicString.cstring = pTopic;
//		int32_t  len = MQTTSerialize_publish(buf, buflen, 0, 0, 0, 123, topicString, (unsigned char*)pMessage, msglen); //
//		transport_sendPacketBuffer(buf,len);
//		return 0;
//}

// 订阅
int Mqtt_Subscribe(char *pTopic)
{
    int32_t len;
    MQTTString topicString = MQTTString_initializer;
    int buflen = sizeof(buf);
    memset(buf,0,buflen);
    topicString.cstring = pTopic;//
    len = MQTTSerialize_subscribe(buf, buflen, 0, 1, 1, &topicString, 0);
		transport_sendPacketBuffer(buf, len);
    return 0;
}
