#include <Arduino.h>

#define PIN_BUZZER  6
#define PIN_LED_RED 7
#define PIN_LED_GRN 8

void setup() {
  pinMode(PIN_BUZZER,OUTPUT);
  pinMode(PIN_LED_RED,OUTPUT);
  pinMode(PIN_LED_GRN,OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED_GRN,HIGH);
  delay(100);
  digitalWrite(PIN_LED_GRN,LOW);
  delay(100);
}
