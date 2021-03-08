#include "mqtt_transport.h"
#include "bsp_esp8266.h"

void WiFi_SendString(UINT8* str,UINT8 buflen)
{
	for(int i = 0; i < buflen; i++)
	{
		USART_SendData(macESP8266_USARTx, *str);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET);
		str++;
	}
}

UINT8 transport_sendPacketBuffer(UINT8* buf, UINT8 buflen)
{
	WiFi_SendString(buf,buflen);
	return 1;
}

UINT8 transport_getdata(UINT8* buf, UINT8 count)
{
	memcpy(buf, strUSART_Fram_Record .Data_RX_BUF, count);
	return count;
}
