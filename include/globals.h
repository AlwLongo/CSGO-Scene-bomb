
#ifndef GLOBALS_H
#define GLOBALS_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <WString.h>
#include <Keypad.h>
#include <arduino-timer.h>
#include "time_concept.h"

// BUTTON
#define btnRIGHT 0
#define btnUP  1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

#define LED_PIN 2
#define BUZZER_PIN A5

// LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

enum DANGER_STATUS{ STARTED , OK, ON_LAST_MINUTE, ON_LAST_TEN_SECONDS, ENDED};

int read_LCD_buttons()
{                                   // read the buttons
    int adc_key_in = analogRead(0); // read the value from the sensor
    // For V1.1 us this threshold
    if (adc_key_in < 50)
        return btnRIGHT;
    if (adc_key_in < 250)
        return btnUP;
    if (adc_key_in < 450)
        return btnDOWN;
    if (adc_key_in < 650)
        return btnLEFT;
    if (adc_key_in < 850)
        return btnSELECT;

    return btnNONE;

}

// KEYPAD
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
    };

byte colPins[COLS] = {A1, A2, A3, A4};
byte rowPins[ROWS] = {3, 11, 12, 13};
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int  led_status = LOW;

bool toggle_led(const char *m) {
  Serial.print("toggle led called with status: ");
  Serial.print(led_status);
   if (led_status == LOW)
  {
    Serial.print(" To ");
    Serial.println(HIGH);
    digitalWrite(LED_PIN, HIGH); // toggle the LED
    tone(BUZZER_PIN, 500);
    led_status = HIGH;
  }else{
    Serial.print(" To ");
    Serial.println(LOW);
    digitalWrite(LED_PIN, LOW); // toggle the LED
    noTone(BUZZER_PIN);
    led_status = LOW;
  }

  return 1; // repeat? true
}
#endif