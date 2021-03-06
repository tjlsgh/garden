#ifndef _MQTT_TRANSPORT_H_
#define _MQTT_TRANSPORT_H_

#include "los_sys.h"
#include "stm32f10x.h"

UINT8 transport_sendPacketBuffer(UINT8* buf, UINT8 buflen);
UINT8 transport_getdata(UINT8* buf, UINT8 count);

#endif
