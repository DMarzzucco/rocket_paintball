#pragma once

//screen config
// A4 (SDA) y A5 (SCL) estan fijos por hardware para I2C en el Uno, no se pueden reasignar
#define LCD_COLS 16
#define LCD_ROWS 2

//relay PIN
#define RELAY_PIN 13

//buzzer
#define BUZZER_PIN 12

//led pin
#define LED_PIN_RED 10
#define LED_PIN_GREEN 11

// keyboard config
#define KEYPAD_ROW_PINS {2, 3, 4, 5}
#define KEYPAD_COL_PINS {6, 7, 8, 9}


//puzzle (juego de cables)
#define PUZZLE_PIN_1 A0
#define PUZZLE_PIN_2 A1
#define PUZZLE_PIN_3 A2
#define PUZZLE_PIN_4 A3

const int puzzlePins[] = {PUZZLE_PIN_1, PUZZLE_PIN_2, PUZZLE_PIN_3, PUZZLE_PIN_4};
const int PUZZLE_WIRE_COUNT = sizeof(puzzlePins) / sizeof(puzzlePins[0]);


//const int puzzlePattern[] = {PUZZLE_PIN_3, PUZZLE_PIN_1, PUZZLE_PIN_4, PUZZLE_PIN_2};
const int puzzlePattern[] = {PUZZLE_PIN_1, PUZZLE_PIN_2, PUZZLE_PIN_3, PUZZLE_PIN_4};

//password
const char password[] = "147B";

