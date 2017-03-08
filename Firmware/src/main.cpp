#include <Arduino.h>

#include "LowPower.h"

#define PIN_LED_LEFT   1 // PD1, pin  3
#define PIN_PUSHBUTTON 2 // PD2, pin  4
#define PIN_BUZZER     3 // PD3, pin  5
#define PIN_LED_RIGHT  5 // PD5, pin 11

#define TIME_GO_UP     SLEEP_4S // 4000
#define TIME_WAIT_UP   SLEEP_2S // 2250
#define TIME_GO_DOWN   SLEEP_4S // 4000
#define TIME_WAIT_DOWN SLEEP_2S // 2250

#define E5  659
#define C6 1046
#define E6 1318
#define G6 1568
#define A6 1760
#define B6 1975
#define C7 2093
#define D7 2349
#define E7 2637
#define F7 2794
#define G7 3136
#define C8 4186

#define FREQ_COUTDOWN  E6
#define FREQ_DOWN      B6
#define FREQ_UP        C7
#define FREQ_FINISHED  D7

#define NUM_REPETITIONS 10

#define DELAY_BLIP 50

int use_buzzer = 0;

void tone_delay(int pin, unsigned int freq, unsigned long duration) {
  if (use_buzzer)
    tone(pin, freq, duration);
  delay(duration);
}

void blip(int pin, int times, int duration, unsigned int freq) {
  if (freq > 0)
    if(use_buzzer)
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
  blip(PIN_LED_LEFT, 1, FREQ_COUTDOWN);
}

void sigCountDownSilent() {
  blip(PIN_LED_LEFT, 1, 0);
}

void sigGoUp() {
  blip(PIN_LED_RIGHT, 1, FREQ_DOWN);
  blip(PIN_LED_RIGHT, 1, FREQ_UP);
}

void sigGoDown() {
  blip(PIN_LED_LEFT, 1, FREQ_UP);
  blip(PIN_LED_LEFT, 1, FREQ_DOWN);
}

void sigWaitUp() {
  blip(PIN_LED_RIGHT, 1, FREQ_UP);
}

void sigWaitDown() {
  blip(PIN_LED_LEFT, 1, FREQ_DOWN);
}

void sigFinished() {
  blip(PIN_LED_RIGHT, 1, 500, FREQ_FINISHED);
}

void sleep(period_t duration) {
  LowPower.powerDown(duration, ADC_OFF, BOD_OFF);
}

void isr() {}

void setup() {
  pinMode(PIN_BUZZER,OUTPUT);
  pinMode(PIN_LED_LEFT,OUTPUT);
  pinMode(PIN_LED_RIGHT,OUTPUT);
  pinMode(PIN_PUSHBUTTON,INPUT_PULLUP);
  if(digitalRead(PIN_PUSHBUTTON) == LOW)
    use_buzzer = false;
  else
    use_buzzer = true;
  digitalWrite(PIN_LED_LEFT,  HIGH);
  digitalWrite(PIN_LED_RIGHT, HIGH);
  if (use_buzzer)
    tone(PIN_BUZZER, E5, 50);
  delay(50);
  digitalWrite(PIN_LED_LEFT,  LOW);
  digitalWrite(PIN_LED_RIGHT, LOW);
}

void loop() {
  // wait 1s
  sleep(SLEEP_1S);
  // count down from 5
  for (size_t i = 0; i < 5; i++) {
    if (i < 2)
      sigCountDownSilent();
    else
      sigCountDown();
   sleep(SLEEP_1S);
  }
  // do N repetitions
  for (int i = 0; i < NUM_REPETITIONS; i++) {
    sigGoUp();      sleep(TIME_GO_UP);
    sigWaitUp();    sleep(TIME_WAIT_UP);
    sigGoDown();    sleep(TIME_GO_DOWN);
    sigWaitDown();  sleep(TIME_WAIT_DOWN);
  }
  // finished!
  sigFinished();
  // prepare for deep sleep
  attachInterrupt(digitalPinToInterrupt(PIN_PUSHBUTTON), isr, CHANGE);
  sleep(SLEEP_FOREVER);
  detachInterrupt(digitalPinToInterrupt(PIN_PUSHBUTTON));
}
