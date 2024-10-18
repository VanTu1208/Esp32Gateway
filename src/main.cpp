#include <Arduino.h>
#include "Wifi_Config.h"
#include "Lora_Module.h"
#include "Stm32_Community.h"
#include "MQTT.h"

uint8_t num[5] = {13, 27, 33, 45, 89};

const char* ssid = "Tuhehe";
const char* password = "78787879";

void setup() {
  Serial.begin(115200);
  setup_wifi(ssid,password);
  STM32_Setup(9600);
  Lora_Setup();
  MQTT_Setup();

  xTaskCreate(MQTT_Process,"MQTT Task",7000,NULL,3,NULL);
  xTaskCreate(MQTT_Send_SensorValue,"Lora Task",7000,NULL,3,NULL);
  xTaskCreate(STM_Transmit_Process,"STM1 Task",7000,num,2,NULL);
  xTaskCreate(STM_Receive_Process,"STM2 Task",7000,NULL,2,NULL);
}


void loop() {}



