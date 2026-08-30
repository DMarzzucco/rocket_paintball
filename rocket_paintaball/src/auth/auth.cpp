#include "auth.h"
#include "config/Config.h"

AuthClass::AuthClass(
    KeyboardClass &keyboard,
    ScreenClass &screen,
    BuzzerClass &buzzer) : keyboard(keyboard), screen(screen), buzzer(buzzer) {}

const byte PASSWORD_LEN = sizeof(password) - 1;

char inputBuffer[PASSWORD_LEN + 1];
byte inputIndex = 0;

void AuthClass::resetInput()
{
    inputIndex = 0;
    screen.resetCursor();
}

void AuthClass::checkTimer()
{
    if (!timerRunning)
    {
        return;
    }

    unsigned long elapsed = millis() - timerStart;

    if (elapsed >= TIMER_DURATION)
    {
        timerRunning = false;
        screen.timerFinish();
        buzzer.buzzer_red();
        resetInput();
        return;
    }

    int secondsLeft = (TIMER_DURATION - elapsed) / 1000 + 1;
    if (secondsLeft != lastSecondsLeft)
    {
        lastSecondsLeft = secondsLeft;
        screen.showCountdown(secondsLeft);
        buzzer.buzzer_tick();
    }
}

void AuthClass::login()
{
    checkTimer();

    char key = keyboard.getKey();

    if (!key)
    {
        return;
    }

    if (key == '#')
    {
        inputBuffer[inputIndex] = '\0';
        if (inputIndex == PASSWORD_LEN && strcmp(inputBuffer, password) == 0)
        {
            buzzer.buzzer_green();
            if (timerRunning)
            {
                timerRunning = false;
                screen.disabledLauncher();
                resetInput();
            }
            else
            {
                screen.enabledLaucnher();
                resetInput();
                timerRunning = true;
                timerStart = millis();
                lastSecondsLeft = -1;
                inputIndex = 0;
            }
        }
        else
        {
            screen.wrongPassword();
            buzzer.buzzer_wrong();
            if (timerRunning)
            {
                timerStart -= WRONG_PASSWORD_PENALTY;
                checkTimer();
            }
            resetInput();
        }
        return;
    }

    if (key == '*')
    {
        resetInput();
        return;
    }

    if (inputIndex < PASSWORD_LEN)
    {
        inputBuffer[inputIndex] = key;
        inputIndex++;
        screen.writeChar(key);
    }
}