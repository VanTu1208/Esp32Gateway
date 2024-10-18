#include "Stm32_Community.h"

SoftwareSerial SerialSTM(33,32);

void STM32_Setup(int baud){
    SerialSTM.begin(baud);
} 

void STM_Transmit_Process(void *pvParameters) {
    // Ép kiểu tham số pvParameters thành kiểu con trỏ uint8_t*
    uint8_t *num = (uint8_t *)pvParameters;
    
    while (1) {
        for (int i = 0; i < 5; i++) {  // Giả sử mảng num có 5 phần tử
            SerialSTM.print(num[i]);
            Serial.print("Send STM32: "); 
            Serial.println(num[i]);
            vTaskDelay(pdMS_TO_TICKS(2000));  // Tạo độ trễ 2 giây
        }
    }
}

void STM_Receive_Process(void*) {
    while (1) {
        String data = "";
        while (SerialSTM.available() > 0) {
            char receivedChar = SerialSTM.read();
            data = data + receivedChar;
        }

        if (data.length() > 0) {
            Serial.print("Data Receive: ");
            Serial.println(data);
        } else {
            vTaskDelay(pdMS_TO_TICKS(1000));  // Delay nếu không có dữ liệu
        }
    }
}