#include "auth.h"
#include "config/Config.h"

AuthClass::AuthClass(
    KeyboardClass &keyboard,
    ScreenClass &screen) : keyboard(keyboard), screen(screen) {}

const byte PASSWORD_LEN = sizeof(password) - 1;

char inputBuffer[PASSWORD_LEN + 1];
byte inputIndex = 0;

void AuthClass::resetInput()
{
    inputIndex = 0;
    screen.resetCursor();
}

void AuthClass::login()
{
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
            buzzer_green();
            screen.disabledLauncher();
            while (true)
            {
            }
        }
        else
        {
            digitalWrite(LED_PIN_RED, HIGH);
            digitalWrite(BUZZER_PIN, HIGH);
            screen.enabledLaucnher();
            delay(3000);
            digitalWrite(LED_PIN_RED, LOW);
            digitalWrite(BUZZER_PIN, LOW);
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

void AuthClass::buzzer_green() {
    digitalWrite(LED_PIN_GREEN, HIGH);
    digitalWrite(LED_PIN_RED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(350);
    digitalWrite(LED_PIN_GREEN, LOW);
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    delay(350);
    digitalWrite(LED_PIN_GREEN, HIGH);
    digitalWrite(LED_PIN_RED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(350);
    digitalWrite(LED_PIN_GREEN, LOW);
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
}