#include <Arduino.h>

#define PIN_BUZZER  6
#define PIN_LED_RED 7
#define PIN_LED_GRN 8

#define TIME_GO_UP     4000
#define TIME_WAIT_UP   2250
#define TIME_GO_DOWN   4000
#define TIME_WAIT_DOWN 2250

#define NUM_REPETITIONS 10

#define DELAY_BLIP 50

void blip(int pin, int times, int duration) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin,HIGH);
    delay(duration);
    digitalWrite(pin,LOW);
    delay(duration);
  }
}

void blip(int pin, int times) {
  blip(pin, times, DELAY_BLIP);
}

void sigCountDown() {
  blip(PIN_LED_RED, 1);
}

void sigGoUp() {
  blip(PIN_LED_GRN, 1);
}

void sigGoDown() {
  blip(PIN_LED_RED, 1);
}

void sigWaitUp() {
  blip(PIN_LED_GRN, 2);
}

void sigWaitDown() {
  blip(PIN_LED_RED, 2);
}

void sigFinished() {
  blip(PIN_LED_GRN, 1, 500);
}

void setup() {
  pinMode(PIN_BUZZER,OUTPUT);
  pinMode(PIN_LED_RED,OUTPUT);
  pinMode(PIN_LED_GRN,OUTPUT);

  for (size_t i = 0; i < 5; i++) {
    sigCountDown();
    delay(1000);
  }

  for (int i = 0; i < NUM_REPETITIONS; i++) {
    sigGoUp();
    delay(TIME_GO_UP);
    sigWaitUp();
    delay(TIME_WAIT_UP);
    sigGoDown();
    delay(TIME_GO_DOWN);
    sigWaitDown();
    delay(TIME_WAIT_DOWN);
  }

  sigFinished();
}

void loop() {
  while(true);
}
