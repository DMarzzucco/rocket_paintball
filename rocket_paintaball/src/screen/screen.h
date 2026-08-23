#include <LiquidCrystal_I2C.h>

class ScreenClass
{
private:
    LiquidCrystal_I2C lcd;
    int cursorCol;
    int cursorRow;
    
    public:
    ScreenClass();
    void init();
    void writeChar(char c);
    void disabledLauncher ();
    void enabledLaucnher();
    void resetCursor();
};