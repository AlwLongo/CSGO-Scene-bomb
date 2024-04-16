

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

#define LED_PIN A2
#define BUZZER_PIN A1

// LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
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
    // For V1.0 comment the other threshold and use the one below:
    /*
    if (adc_key_in < 50) return btnRIGHT;
    if (adc_key_in < 195) return btnUP;
    if (adc_key_in < 380) return btnDOWN;
    if (adc_key_in < 555) return btnLEFT;
    if (adc_key_in < 790) return btnSELECT;
    */
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

byte colPins[COLS] = {12, 13, A4, A3};
byte rowPins[ROWS] = { A5, 2, 3, 11};
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