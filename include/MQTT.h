#ifndef MQTT_H
#define MQTT_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Lora_Module.h"
#include "Wifi_Config.h"

extern WiFiClientSecure espClient;
extern PubSubClient client;

extern const char* mqtt_broker;
extern const int mqtt_port;  // SSL port
extern const char* mqtt_username;
extern const char* mqtt_password;
extern const char* macAddress;


struct SensorData {
  float nh3;
  float h2s;
  float temp;
  float hum;
  String penCode;
  String nodeId;
};

extern String receivedTopic;
extern String receivedPayload;
extern SensorData sensorData;

extern bool stateList[16]; 


void MQTT_Setup();
void publishMessage(const char* topic, const char* payload);
void processData(const String& data);
void callback(char* topic, byte* payload, unsigned int length);
void MQTT_Process(void*);
void MQTT_Send_SensorValue(void*);





extern const char* root_ca;



#endif // LIBRARY_H