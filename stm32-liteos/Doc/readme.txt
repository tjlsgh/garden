/*
����ʪ�ȴ�������PA5
������������PA2
��ʪ�ȴ�������PE6
�ƣ�PB12 (�ߵ�ƽ)
ˮ�ã�PB13
*/


1. �������ϴ�����ʱ�� ������д���У��ֿ��ϴ�����ȴ������ ����֪��ԭ����ɶ��
	sprintf(mqtt_message,
				"{\"method\":\"thing.event.property.post\",\"id\":630262306,\"params\":{\
					\"LampState\":%d,\
					\"WaterState\":%d\
					},\"version\":\"1.0\"}",
					Lamp_State, Water_State
	);
		sprintf(mqtt_message,
				"{\"method\":\"thing.event.property.post\",\"id\":630262306,\"params\":{\
					\"EnvTemperature\": %d.%d,\
					\"EnvHumidity\":%d.%d,\
					\"LightLux\":%.1f,\
					\"SoilHumidity\":%.1f\
					},\"version\":\"1.0\"}",
					DHT11_Data->temp_int,DHT11_Data->temp_deci,
					DHT11_Data->humi_int,DHT11_Data->humi_deci,
					LightLux,SoilHumidity
	);
	