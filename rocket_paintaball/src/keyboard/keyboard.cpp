#include "keyboard.h"

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {23, 22, 21, 19};
byte colPins[COLS] = {18, 5, 17, 16};

KeyboardClass::KeyboardClass() : keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS) {}

char KeyboardClass::getKey() {
    return keypad.getKey();
}