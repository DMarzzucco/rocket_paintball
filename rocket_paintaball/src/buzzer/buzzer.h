#pragma once

#include <Arduino.h>

class BuzzerClass
{
private:
    void plus_run(const uint8_t pins[], uint8_t pinCount, unsigned long onTime, unsigned long offTime = 0, uint8_t repeats = 1);

public:
    void buzzer_red();
    void buzzer_tick();
    void buzzer_green();
    void buzzer_wrong();
};