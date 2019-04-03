#ifndef LCD_H
#define LCD_H

#include <stdexcept>
#include "GPIO_operations.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2


#define TIME_DELAY_BEFORE_ENABLE 400
#define TIME_DELAY_BEFORE_DISABLE 800

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04 /* set the moin direction of cursor and display  */
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01 /* shift the display to the left */
#define LCD_ENTRYSHIFTDECREMENT 0x00 /* shift the display to the right */

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

//DDRAM address
#define LCD_2LINE_HOME_ADDRESS 0x40

class LiquidCrystal
{
  public:
    LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
                  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

    void begin(uint8_t cols, uint8_t lines);
    void clear();
    void home();
    void setCursor(uint8_t col, uint8_t row);

    size_t print(const char str[]);
    size_t print(char character);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(double, int = 2);

  private:
    uint8_t rsPin;
    uint8_t rwPin;
    uint8_t enablePin;
    uint8_t dataPins[8];
    uint8_t displayMode; //only implemented for 8bit

    void InitLCDPins();
    void SetupDisplay();
    void nonExactDelay(int delay);
    void SetToWrite();
    void SetToRead();
    void CommandMode();
    void CharacterMode();
    void Enable();
    void SendByte(char byte);
    void SendCommand(char command);
    size_t SendCharacter(char character);
    size_t SendString(const char *cString);

    size_t printNumber(unsigned long n, uint8_t base);
    size_t printFloat(double number, uint8_t digits);
};

#endif