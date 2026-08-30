#pragma once

#include "../screen/screen.h"
#include "../keyboard/keyboard.h"
#include "../buzzer/buzzer.h"

class AuthClass
{
private:
    KeyboardClass &keyboard;
    ScreenClass &screen;
    BuzzerClass &buzzer;
    bool timerRunning = false;
    unsigned long timerStart = 0;
    int lastSecondsLeft = -1;
    static const unsigned long TIMER_DURATION = 120000UL;
    static const unsigned long WRONG_PASSWORD_PENALTY = 20000UL;
    void buzzer_green();
    void buzzer_red();
    void buzzer_tick();
    void buzzer_wrong();
    void checkTimer();

public:
    AuthClass(KeyboardClass &keyboard, ScreenClass &screen, BuzzerClass &buzzer);
    void login();
    void resetInput();
};