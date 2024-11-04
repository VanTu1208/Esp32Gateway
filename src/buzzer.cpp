#include "buzzer.h"
int buzzerPin = 22;    


void buzzer_Setup() {
  pinMode(buzzerPin,OUTPUT);
}

void fail_Lora() {
  // Tạo tiếng "tít" đầu tiên
  tone(buzzerPin, 1000);  // Phát âm với tần số 1000 Hz
  delay(200);             // Kéo dài 200ms
  
  // Tắt buzzer
  noTone(buzzerPin);      // Dừng âm thanh
  delay(200);             // Tạm dừng 200ms

  // Tạo tiếng "tít" thứ hai
  tone(buzzerPin, 1000);  // Phát lại âm với tần số 1000 Hz
  delay(200);             // Kéo dài 200ms

  // Tắt buzzer
  noTone(buzzerPin);      // Dừng âm thanh
  delay(200);             // Tạm dừng 200ms

  // Tạo tiếng "tít" thứ ba
  tone(buzzerPin, 1000);  // Phát lại âm với tần số 1000 Hz
  delay(200);             // Kéo dài 200ms

  // Tắt buzzer
  noTone(buzzerPin);      // Dừng âm thanh
}