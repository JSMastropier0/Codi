#include <Arduino.h>

#define LED 8 // LED_BUILTIN for ESP32C Super Mini

void setup() {
  Serial.begin(115200);
  
  // Set pin mode
  pinMode(LED,OUTPUT);
  Serial.println("setup: Led set to Output");
}

void loop() {
  digitalWrite(LED,HIGH);
  delay(1000);
  Serial.println("loop: Led set HIGH");

  digitalWrite(LED,LOW);
  delay(1000);
  Serial.println("loop: Led set LOW");
}
