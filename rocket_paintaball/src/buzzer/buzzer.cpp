#include "buzzer.h"
#include "config/Config.h"

void BuzzerClass::buzzer_red()
{
    const uint8_t pins[] = {LED_PIN_RED, BUZZER_PIN};
    plus_run(pins, 2, 2000);
}

void BuzzerClass::buzzer_tick()
{
    const uint8_t pins[] = {LED_PIN_RED, BUZZER_PIN};
    plus_run(pins, 2, 50);
}

void BuzzerClass::buzzer_green()
{
    const uint8_t pins[] = {LED_PIN_GREEN, LED_PIN_RED, BUZZER_PIN};
    plus_run(pins, 3, 350, 350, 2);
}

void BuzzerClass::buzzer_wrong()
{
    const uint8_t pins[] = {LED_PIN_RED, BUZZER_PIN};
    plus_run(pins, 5, 50, 50, 5);
}

void BuzzerClass::plus_run(const uint8_t pins[], uint8_t pinCount, unsigned long onTime, unsigned long offTime, uint8_t repeats)
{
    for (uint8_t i = 0; i < repeats; i++)
    {
        for (uint8_t p = 0; p < pinCount; p++)
            digitalWrite(pins[p], HIGH);
        delay(onTime);

        for (uint8_t p = 0; p < pinCount; p++)
            digitalWrite(pins[p], LOW);
        if (offTime > 0)
            delay(offTime);
    }
}