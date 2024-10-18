#include "MQTT.h"

String receivedTopic;
String receivedPayload;
SensorData sensorData;


WiFiClientSecure espClient;
PubSubClient client(espClient);

const char* mqtt_broker = "f550d1a0a28e464a915234c191ab1945.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;  // SSL port
const char* mqtt_username = "Tuslee";
const char* mqtt_password = "ThucTapT9";
const char* macAddress = "1000_0001";

bool stateList[16] = {false}; // Now you can initialize the array here

const char* root_ca =
  "-----BEGIN CERTIFICATE-----\n"
  "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\n"
  "-----END CERTIFICATE-----\n";




void reconnect();
void handleMqttMessage();

void MQTT_Setup(){
    espClient.setCACert(root_ca);
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
}


void publishMessage(const char* topic, const char* payload) {
    if (client.connected()) {
        client.publish(topic, payload);
        Serial.println("Published message: " + String(payload) + " to topic: " + String(topic));
    } else {
        Serial.println("MQTT client not connected, message not sent.");
    }
}


void processData(const String& data) {
  // Parse input data
    sscanf(data.c_str(), "H2S:%f; NH3:%f; Temp:%f; Hum:%f", &sensorData.h2s, &sensorData.nh3, &sensorData.temp, &sensorData.hum);

    char topic[50];
    snprintf(topic, sizeof(topic), "%s/sensors/response", macAddress);

    // Create JSON object
    JsonDocument doc;

    Serial.println("--------------------------------------------");
    // Add sensor data to JSON object
    doc["Pin1"] = sensorData.temp;  // Gán nhiệt độ cho Pin 1
    Serial.print("Temperature: "); Serial.println(int(sensorData.temp));
    
    doc["Pin2"] = sensorData.hum;   // Gán độ ẩm cho Pin 2
    Serial.print("Humidity: "); Serial.println(int(sensorData.hum));
    
    doc["Pin3"] = sensorData.nh3;   // Gán mức NH3 cho Pin 3
    Serial.print("NH3: "); Serial.println(int(sensorData.nh3));

    doc["Pin4"] = sensorData.h2s;   // Gán mức H2S cho Pin 4
    Serial.print("H2S: "); Serial.println(int(sensorData.h2s));
    Serial.println("--------------------------------------------");
    char payload[256];
    serializeJson(doc, payload);

    snprintf(topic, sizeof(topic), "%s/sensors/response", macAddress);
    publishMessage(topic, payload);

}

void callback(char* topic, byte* payload, unsigned int length) {
    receivedTopic = String(topic);
    receivedPayload = String((char*)payload, length);
    handleMqttMessage();
}

void handleMqttMessage() {
    Serial.println("Handling MQTT message: " + receivedTopic + " " + receivedPayload);

    if (receivedTopic == String(macAddress) + "/controls/request") {
    // Handle get state of all controls
        JsonDocument doc;
        JsonArray array = doc.to<JsonArray>();
        
        for (int i = 0; i < 16; i++) {
            JsonObject obj = array.add<JsonObject>();
            obj["Pin"] = i;
            obj["Value"] = stateList[i] ? 1 : 0;
        }
        
        char payload[512];
        serializeJson(doc, payload);
        
        char responseTopic[50];
        snprintf(responseTopic, sizeof(responseTopic), "%s/controls/response", macAddress);
        publishMessage(responseTopic, payload);
    }
    else if (receivedTopic.indexOf(String(macAddress)+"/controls/") != -1 && receivedTopic.endsWith("/request")) {
        // Handle get state of a specific control
        int pin = receivedTopic.substring(receivedTopic.indexOf("/controls/") + 10, receivedTopic.lastIndexOf("/")).toInt();
        
        if (pin >= 0 && pin < 16) {
            char responseTopic[50];
            snprintf(responseTopic, sizeof(responseTopic), "%s/controls/%d/response", macAddress, pin);
            char payload[10];
            snprintf(payload, sizeof(payload), "%d", stateList[pin] ? 1 : 0);
            publishMessage(responseTopic, payload);
        }
    }
    else if (receivedTopic.indexOf(String(macAddress)+"/controls/") != -1 && receivedTopic.endsWith("/command")) {
        // Handle command for a specific control
        int pin = receivedTopic.substring(receivedTopic.indexOf("/controls/") + 10, receivedTopic.lastIndexOf("/")).toInt();
        
        if (pin >= 0 && pin < 16) {
            if (receivedPayload == "0" || receivedPayload == "1") {
            bool newState = (receivedPayload == "1");
            stateList[pin] = newState;
            if(receivedPayload == "1"){
                Serial.print("Bật đèn số "); Serial.println(pin);
            } else {
                Serial.print("Tắt đèn số "); Serial.println(pin);
            }   
            char responseTopic[50];
            snprintf(responseTopic, sizeof(responseTopic), "%s/controls/%d/response", macAddress, pin);
            publishMessage(responseTopic, receivedPayload.c_str());
            }
        }
    }
    else if (receivedTopic == String(macAddress) + "/resetwifi/request") {
        WiFi_Reset();
        char responseTopic[50];
        snprintf(responseTopic, sizeof(responseTopic), "%s/resetwifi/response", macAddress);
        
        // Tạo nội dung phản hồi
        char payload[512];
        snprintf(payload, sizeof(payload), "RESETWIFI: %s", resetState); // resetState là biến chứa trạng thái sau khi reset
        
        // Gửi thông điệp phản hồi
        publishMessage(responseTopic, payload);
    }

}


void MQTT_Process(void*){
    while(1){
        if (!client.connected()) reconnect();
        client.loop();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");

        String clientID = "ESPClient-";
        clientID += macAddress;

        if (client.connect(clientID.c_str(), mqtt_username, mqtt_password)) {
        Serial.println("connected");

        // Subscribe to control topics if needed
        for (int i = 0; i < 16; i++) {
            char topic[50];
            snprintf(topic, sizeof(topic), "%s/controls/%d/#", macAddress, i);
            client.subscribe(topic);
        }
        } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());  // Print the reason for failure
        if (client.state() == -1) {
            Serial.println("Connection refused, incorrect protocol version");
        } else if (client.state() == -2) {
            Serial.println("Connection refused, identifier rejected");
        } else if (client.state() == -3) {
            Serial.println("Connection refused, broker unavailable");
        } else if (client.state() == -4) {
            Serial.println("Connection refused, bad username or password");
        } else if (client.state() == -5) {
            Serial.println("Connection refused, not authorized");
        }
        Serial.println(" try again in 5 seconds");
        vTaskDelay(pdMS_TO_TICKS(5000));
        }
    }
}

void MQTT_Send_SensorValue(void*){
    while(1){
        String receivedData = Lora_receive();
        if(receivedData != "") 
            processData(receivedData);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
  
}