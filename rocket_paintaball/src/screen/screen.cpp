#include "screen.h"
#include "config/Config.h"

ScreenClass::ScreenClass() : lcd(0x27, LCD_COLS, LCD_ROWS), cursorCol(0), cursorRow(0) {}

void ScreenClass::init()
{
    Wire.begin(I2C_SDA, I2C_SCL);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Desactivar");
    lcd.setCursor(0, 1);
    lcd.print("lanzamiento");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INGRESAR-CLAVE:");
}

void ScreenClass::writeChar(char c)
{
    if (cursorCol >= LCD_COLS)
    {
        cursorCol = 0;
        cursorRow++;
        if (cursorRow >= LCD_ROWS)
        {
            lcd.clear();
            cursorRow = 0;
        }
        lcd.setCursor(cursorCol, cursorRow);
    }
    lcd.setCursor(cursorCol, 1);
    lcd.print(c);
    cursorCol++;
}

void ScreenClass::resetCursor()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("INGRESAR-CLAVE:");
    lcd.setCursor(0, 1);
    cursorCol = 0;
    cursorRow = 0;
}

void ScreenClass::disabledLauncher()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lanzamiento");
    lcd.setCursor(0, 1);
    lcd.print("desactivad");
    delay(2000);
}

void ScreenClass::enabledLaucnher()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pass incorrecta.");
    lcd.setCursor(0, 1);
    lcd.print("BOOOM.");
    delay(2000);
}