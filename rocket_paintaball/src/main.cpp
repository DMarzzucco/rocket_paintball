#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <cstring>

#include "keyboard/keyboard.h"
#include "screen/screen.h"
#include "auth/auth.h"
#include "buzzer/buzzer.h"
#include "config/Config.h"

KeyboardClass keyboard = KeyboardClass();
ScreenClass screen = ScreenClass();
BuzzerClass buzzer = BuzzerClass();
AuthClass auth= AuthClass(keyboard, screen, buzzer);

void setup() {
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  screen.init();
}

void loop() {
  auth.login();
}