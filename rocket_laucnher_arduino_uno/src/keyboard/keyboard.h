#pragma once

#include <Keypad.h>

class KeyboardClass
{
public:
    KeyboardClass();
    char getKey();

private:
    Keypad keypad;
};