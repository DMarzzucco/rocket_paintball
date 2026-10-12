#include "puzzle.h"
#include "config/Config.h"

PuzzleClass::PuzzleClass() : progress(0)
{
    for (int i = 0; i < PUZZLE_WIRE_COUNT; i++)
    {
        wireCut[i] = false;
    }
}

void PuzzleClass::begin()
{
    for (int i = 0; i < PUZZLE_WIRE_COUNT; i++)
    {
        pinMode(puzzlePins[i], INPUT_PULLUP);
    }
}

void PuzzleClass::arm()
{
    progress = 0;
    for (int i = 0; i < PUZZLE_WIRE_COUNT; i++)
    {
        wireCut[i] = false;
    }
}

PuzzleResult PuzzleClass::check()
{
    int cutNow = 0;
    int pinCut = -1;

    for (int i = 0; i < PUZZLE_WIRE_COUNT; i++)
    {
        bool isCut = digitalRead(puzzlePins[i]) == HIGH;
        if (isCut && !wireCut[i])
        {
            wireCut[i] = true;
            cutNow++;
            pinCut = puzzlePins[i];
        }
    }

    if (cutNow == 0)
    {
        return PuzzleResult::NONE;
    }

    if (cutNow > 1 || pinCut != puzzlePattern[progress])
    {
        return PuzzleResult::DETONATED;
    }

    progress++;
    return (progress == PUZZLE_WIRE_COUNT) ? PuzzleResult::DEFUSED : PuzzleResult::NONE;
}
