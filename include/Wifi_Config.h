#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include <WiFi.h>
#include <WiFiManager.h> 

extern WiFiManager wifiManager;
extern String resetState;

void setup_wifi(const char* ssid,const char* password);
void WiFi_Reset();

#endif // LIBRARY_H