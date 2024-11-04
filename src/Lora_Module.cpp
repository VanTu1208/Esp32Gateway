#include "Lora_Module.h"
std::vector<String> receivedDataList;
void storeData(const String& data) {
    receivedDataList.push_back(data);
}

void Lora_Setup(){
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed!");
    //while (1);
    fail_Lora();
  }
  Serial.println("LoRa initialized successfully!");
  LoRa.receive();
}

void Lora_receive(){
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        String receivedData = "";
        while (LoRa.available()) {
            receivedData += (char)LoRa.read(); // Read data
        }
        // Print received data
        Serial.print("Received LoRa data: ");
        Serial.println(receivedData);
        storeData(receivedData);
    }
}

