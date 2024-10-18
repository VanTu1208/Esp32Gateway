#include "Lora_Module.h"

void Lora_Setup(){
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed!");
    while (1);
  }
  Serial.println("LoRa initialized successfully!");
  LoRa.receive();
}

String Lora_receive(){
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        String receivedData = "";
        while (LoRa.available()) {
            receivedData += (char)LoRa.read(); // Read data
        }
        // Print received data
        Serial.print("Received LoRa data: ");
        Serial.println(receivedData);
        return receivedData;
    }
    return "";
}

