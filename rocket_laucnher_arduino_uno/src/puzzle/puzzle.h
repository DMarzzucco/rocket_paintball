#pragma once

#include <Arduino.h>

enum class PuzzleResult
{
    NONE,
    DEFUSED,
    DETONATED
};

class PuzzleClass
{
private:
    bool wireCut[4];
    int progress;

public:
    PuzzleClass();
    void begin();
    void arm();
    PuzzleResult check();
};
