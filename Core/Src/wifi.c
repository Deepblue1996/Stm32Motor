//
// Created by mayn on 2020/11/26 0026.
//

#include <stdbool.h>
#include "wifi.h"
#include "log.h"
#include "string.h"

volatile uint8_t isConnect = false;

/**
 * 连接服务器
 * @return
 */
uint8_t connectService() {
    if (isConnect) {
        return true;
    }
//    Log("AT+CIPSTART=\"TCP\",\"119.23.172.242\",8088\r\n");
//    char *string5 = sendResponse2("AT+CIPSTART=\"TCP\",\"119.23.172.242\",8088\r\n", "OK");
    Log("AT+CIPSTART=\"TCP\",\"192.168.0.112\",8088\r\n");
    char *string5 = sendResponse2("AT+CIPSTART=\"TCP\",\"192.168.0.112\",8088\r\n", "OK");
    if (strstr(string5, "ALREADY CONNECTED") != NULL) {
        Log("device connected\r\n");
        isConnect = true;
        return true;
    } else {
        //Log("%c\r\n", string5);
        isConnect = false;
        return false;
    }
}