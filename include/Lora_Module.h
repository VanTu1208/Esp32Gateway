#ifndef LORAMODULE_H
#define LORAMODULE_H

#include <SPI.h>
#include <LoRa.h>

#define LORA_CS   5   // Chip Select
#define LORA_RST  4   // Reset
#define LORA_IRQ  2   // DIO0 (IRQ)
#define LORA_SCK  18  // SCK
#define LORA_MISO 19  // MISO
#define LORA_MOSI 23  // MOSI


void Lora_Setup();
String Lora_receive();

#endif // LIBRARY_H