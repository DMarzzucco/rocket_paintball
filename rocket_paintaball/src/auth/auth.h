#include "../screen/screen.h"
#include "../keyboard/keyboard.h"

class AuthClass
{
private:
    KeyboardClass &keyboard;
    ScreenClass &screen;

public:
    AuthClass(KeyboardClass &keyboard, ScreenClass &screen);
    void login();
    void resetInput();
};