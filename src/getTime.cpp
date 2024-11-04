#include "getTime.h"

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;  // Múi giờ UTC+7 (cho Việt Nam)
const int daylightOffset_sec = 0;     // Không có giờ mùa hè
int hourStart, minStart,secStart;
int hourEnd, minEnd,secEnd;
void getTime_Setup(){
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void getPowerPerMinute(void*) {
  int previousHour = -1;
  while(1){
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Không lấy được thời gian.");
    }
    else{
      Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
      if (timeinfo.tm_min != previousHour) {
        hourStart = hourEnd; minStart = minEnd; secStart = secEnd; 
        hourEnd = timeinfo.tm_hour; minEnd = timeinfo.tm_min; secEnd = timeinfo.tm_sec;
        Serial.print(hourStart); Serial.print(":"); Serial.print(minStart); Serial.print(":"); Serial.print(secStart); 
        Serial.print(" to "); 
        Serial.print(hourEnd); Serial.print(":"); Serial.print(minEnd);Serial.print(":"); Serial.println(secEnd);
        Serial.println("Get Power From STM32");
        STM_Transmit_Process("getPower");
        delay(40);
        previousHour = timeinfo.tm_min;
        String PowerReceive = STM_Receive_Process();
        Serial.print("Power Average: "); Serial.println(PowerReceive);
        char responseTopic[50];
        snprintf(responseTopic, sizeof(responseTopic), "%s/power_average/response", macAddress);
        // Tạo nội dung phản hồi
        char payload[512];
        snprintf(payload, sizeof(payload),"Time %02d:%02d:%02d To %02d:%02d:%02d: %s Wh",
             hourStart, minStart, secStart,
             hourEnd, minEnd, secEnd,
             PowerReceive
    );
        publishMessage(responseTopic, payload);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
