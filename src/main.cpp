#include <Arduino.h>
#include "Wifi_Config.h"
#include "Lora_Module.h"
#include "Stm32_Community.h"
#include "MQTT.h"
#include "getTime.h"
#include "buzzer.h"


const char* ssid = "Tuhehe";
const char* password = "78787879";

void setup() {
  Serial.begin(115200);
  buzzer_Setup();
  Serial.print("shouldResetWiFi: "); Serial.println(shouldResetWiFi);
  if (shouldResetWiFi == 0) setup_wifi(ssid,password);
  else {
    WiFi_Reset();
  }
  STM32_Setup(9600);
  Lora_Setup();
  MQTT_Setup();
  getTime_Setup();

  xTaskCreate(MQTT_Process,"MQTT Task",7000,NULL,3,NULL);
  xTaskCreate(MQTT_Send_SensorValue,"Lora Task",7000,NULL,3,NULL);
  xTaskCreate(getPowerPerMinute,"Time1 Task",7000,NULL,1,NULL);
  
}

void loop() {}



