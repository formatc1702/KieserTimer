#include <Arduino.h>

#include "LowPower.h"

#define PIN_BUZZER  6
#define PIN_LED_RED 7
#define PIN_LED_GRN 8

#define TIME_GO_UP     SLEEP_4S // 4000
#define TIME_WAIT_UP   SLEEP_2S // 2250
#define TIME_GO_DOWN   SLEEP_4S // 4000
#define TIME_WAIT_DOWN SLEEP_2S // 2250

#define FREQ_COUTDOWN  440
#define FREQ_UP        880
#define FREQ_DOWN      660
#define FREQ_FINISHED 1100

#define NUM_REPETITIONS 10

#define DELAY_BLIP 50

void tone_delay(int pin, unsigned int freq, unsigned long duration) {
  tone(pin, freq, duration);
  delay(duration);
}

void blip(int pin, int times, int duration, unsigned int freq) {
  if (freq > 0)
    tone(PIN_BUZZER, freq, duration);
  for (int i = 0; i < times; i++) {
    digitalWrite(pin,HIGH);
    delay(duration);
    digitalWrite(pin,LOW);
    delay(duration);
  }
}

void blip(int pin, int times, unsigned int freq) {
  blip(pin, times, DELAY_BLIP, freq);
}

void sigCountDown() {
  blip(PIN_LED_RED, 1, FREQ_COUTDOWN);
}

void sigGoUp() {
  blip(PIN_LED_GRN, 1, FREQ_UP);
}

void sigGoDown() {
  blip(PIN_LED_RED, 1, FREQ_DOWN);
}

void sigWaitUp() {
  blip(PIN_LED_GRN, 2, FREQ_UP);
}

void sigWaitDown() {
  blip(PIN_LED_RED, 2, FREQ_DOWN);
}

void sigFinished() {
  blip(PIN_LED_GRN, 1, 500, FREQ_FINISHED);
}

void sleep(int duration) {
  LowPower.powerDown(duration, ADC_OFF, BOD_OFF);
}

void setup() {
  pinMode(PIN_BUZZER,OUTPUT);
  pinMode(PIN_LED_RED,OUTPUT);
  pinMode(PIN_LED_GRN,OUTPUT);

  for (size_t i = 0; i < 5; i++) {
    sigCountDown(); sleep(SLEEP_1S);
  }

  for (int i = 0; i < NUM_REPETITIONS; i++) {
    sigGoUp();      sleep(TIME_GO_UP);
    sigWaitUp();    sleep(TIME_WAIT_UP);
    sigGoDown();    sleep(TIME_GO_DOWN);
    sigWaitDown();  sleep(TIME_WAIT_DOWN);
  }

  sigFinished();    sleep(SLEEP_FOREVER);
}

void loop() {
  while(true);
}
