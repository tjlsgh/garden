#include "mqtt.h"
#include "mqtt_transport.h"
#include "MQTTPacket.h"
#include "bsp_esp8266.h"
#include "bsp_dht11.h"

unsigned char buf[300];
char mqtt_message[300];
//unsigned int buflen = sizeof(buf)/sizeof(buf[0]);
unsigned int buflen = sizeof(buf);

// mqtt����
void Mqtt_Connect(void)
{
	unsigned int  len = 0;
  MQTTPacket_connectData data = MQTTPacket_connectData_initializer;//���ÿɱ�ͷ����
	data.clientID.cstring = MQTT_CLIENT_ID;//�豸ΨһID
	data.keepAliveInterval = 60;//�����ʱ�����������������������͵����ʱ��������λ���룩
	data.cleansession = 1;//1������֮ǰ��������Ϣ
	data.username.cstring = MQTT_USER_NAME ;//�û���
	data.password.cstring = MQTT_PASSWORD;//����
	data.MQTTVersion = 4;
	len = MQTTSerialize_connect(buf, buflen, &data); //�������ӱ��Ĳ���ȡ����
	transport_sendPacketBuffer(buf,len);//ͨ��Ӳ���ӿڷ��͸��������Ѿ���װ�õı���
	while(!strEsp8266_Fram_Record.InfBit.FramFinishFlag){};//�ȴ����ӳɹ�----------�˴����Ļ����ؽ���  ע�ͣ�1��
	strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;
	printf("mqtt ���ӳɹ���\n");
}

// ����������
void Mqtt_SendHeatbeat(void)
{
	//unsigned char h_buf[200] = {0};
	u8 len = MQTTSerialize_pingreq(buf, 200);//����mqtt��������װ����
	transport_sendPacketBuffer(buf, len);//��������
}

// ��װ����
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
// ����
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
//// ����
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

// ����
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
