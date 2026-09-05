#pragma once

//screen config 
#define I2C_SDA 25
#define I2C_SCL 26

#define LCD_COLS 16
#define LCD_ROWS 2

//led pin
#define LED_PIN_RED 12
#define LED_PIN_GREEN 2

//puzzle (juego de cables)
#define PUZZLE_PIN_1 14
#define PUZZLE_PIN_2 4
#define PUZZLE_PIN_3 32
#define PUZZLE_PIN_4 33

const int puzzlePins[] = {PUZZLE_PIN_1, PUZZLE_PIN_2, PUZZLE_PIN_3, PUZZLE_PIN_4};
const int PUZZLE_WIRE_COUNT = sizeof(puzzlePins) / sizeof(puzzlePins[0]);


//const int puzzlePattern[] = {PUZZLE_PIN_3, PUZZLE_PIN_1, PUZZLE_PIN_4, PUZZLE_PIN_2};
const int puzzlePattern[] = {PUZZLE_PIN_1, PUZZLE_PIN_2, PUZZLE_PIN_3, PUZZLE_PIN_4};

//buzzer
#define BUZZER_PIN 13

// keyboard config 
#define KEYPAD_ROW_PINS {23, 22, 21, 19}
#define KEYPAD_COL_PINS {18, 5, 17, 16}

//password
const char password[] = "147B";

