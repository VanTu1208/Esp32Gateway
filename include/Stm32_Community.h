#ifndef STM32COM_H
#define STM32COM_H

#include <SoftwareSerial.h>
extern SoftwareSerial SerialSTM;



void STM32_Setup(int baud);
void STM_Transmit_Process(void *pvParameters);
void STM_Receive_Process(void*);
#endif // LIBRARY_H