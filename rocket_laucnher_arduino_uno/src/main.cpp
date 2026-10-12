#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

#include "keyboard/keyboard.h"
#include "trigger/trigger.h"
#include "screen/screen.h"
#include "auth/auth.h"
#include "buzzer/buzzer.h"
#include "puzzle/puzzle.h"
#include "config/Config.h"

TriggerClass trigger = TriggerClass();
KeyboardClass keyboard = KeyboardClass();
ScreenClass screen = ScreenClass();
BuzzerClass buzzer = BuzzerClass();
PuzzleClass puzzle = PuzzleClass();
AuthClass auth= AuthClass(keyboard, trigger, screen, buzzer, puzzle);

void setup() {
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  screen.init();
  puzzle.begin();
}

void loop() {
  auth.login();
}