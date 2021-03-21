/*
土壤湿度传感器：PA5
光敏传感器：PA2
温湿度传感器：PE6
灯：PB12 (高电平)
水泵：PB13
*/


1. 当发送上传数据时， 合起来写不行，分开上传数据却可以了 还不知道原因是啥。
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
	