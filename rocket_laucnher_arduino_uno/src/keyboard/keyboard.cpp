#include "keyboard.h"
#include "config/Config.h"

const byte ROWS = 4;
const byte COLS = 4;

byte rowPins[ROWS] = KEYPAD_ROW_PINS;
byte colPins[COLS] = KEYPAD_COL_PINS;

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

KeyboardClass::KeyboardClass() : keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS) {}

char KeyboardClass::getKey() {
    return keypad.getKey();
}