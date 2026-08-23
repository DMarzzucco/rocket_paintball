#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <cstring>

#include "keyboard/keyboard.h"
#include "screen/screen.h"
#include "auth/auth.h"
#include "config/Config.h"


KeyboardClass keyboard = KeyboardClass();
ScreenClass screen = ScreenClass();
AuthClass auth= AuthClass(keyboard, screen);


void setup() {
  screen.init();
}

void loop() {
  auth.login();
}