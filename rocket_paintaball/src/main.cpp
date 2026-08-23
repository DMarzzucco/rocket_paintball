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

// const byte PASSWORD_LEN = sizeof(password) - 1;

// char inputBuffer[PASSWORD_LEN + 1];
// byte inputIndex = 0;

// void resetInput() {
//   inputIndex = 0;
//   screen.resetCursor();  
// }

void loop() {
  auth.login();
  // char key = keyboard.getKey();

  // if (!key) {
  //   return;
  // }

  // if (key == '#') {
  //   inputBuffer[inputIndex] = '\0';
  //   if (inputIndex == PASSWORD_LEN && strcmp(inputBuffer, password) == 0) {
  //     screen.disabledLauncher();
  //     resetInput();
  //     while (true) {
  //     }
  //   } else {
  //     screen.enabledLaucnher();
  //     resetInput();
  //   }
  //   return;
  // }

  // if (key == '*') {
  //   resetInput();
  //   return;
  // }

  // if (inputIndex < PASSWORD_LEN) {
  //   inputBuffer[inputIndex] = key;
  //   inputIndex++;
  //   screen.writeChar(key);
  // }
}