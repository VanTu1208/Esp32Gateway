#include "Wifi_Config.h"

WiFiManager wifiManager;

String resetState = "";

RTC_DATA_ATTR int shouldResetWiFi = 0;

void setup_wifi(const char* ssid,const char* password) {
  vTaskDelay(pdMS_TO_TICKS(10));
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(pdMS_TO_TICKS(500));
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void WiFi_Reset(){
  shouldResetWiFi = 1;
  Serial.println("Reset Starting...");
  wifiManager.setBreakAfterConfig(true);
  wifiManager.resetSettings();
  // Tạo cổng cài đặt WiFi thông qua WiFiManager
 if (!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    resetState = "Waiting...";
    delay(3000);
    ESP.restart();
    delay(5000);
    
  }
  Serial.println("Đã kết nối WiFi thành công!");
  Serial.print("Địa chỉ IP: ");
  Serial.println(WiFi.localIP());
  resetState = "OK";
  shouldResetWiFi = 0;
}