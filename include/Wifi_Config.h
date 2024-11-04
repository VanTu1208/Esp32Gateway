#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include <WiFiManager.h> 
extern int shouldResetWiFi;
extern WiFiManager wifiManager;
extern String resetState;

void setup_wifi(const char* ssid,const char* password);
void WiFi_Reset();

#endif // LIBRARY_H