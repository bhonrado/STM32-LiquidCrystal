#include "LCD.h"

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
                             uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                             uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
    : rsPin(rs), rwPin(rw), enablePin(enable), displayMode(8)
{
    dataPins[0] = d0;
    dataPins[1] = d1;
    dataPins[2] = d2;
    dataPins[3] = d3;
    dataPins[4] = d4;
    dataPins[5] = d5;
    dataPins[6] = d6;
    dataPins[7] = d7;
}

void LiquidCrystal::begin(uint8_t cols, uint8_t lines)
{
    InitLCDPins();
    SetupDisplay();
}

void LiquidCrystal::nonExactDelay(int delay)
{
    volatile int i;
    for (i = 0; i < delay; i++)
    {
    }
}

void LiquidCrystal::InitLCDPins()
{
    for (int i = 0; i < displayMode; ++i)
    {
        pinMode(dataPins[i], OUTPUT);
    }

    pinMode(rwPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    pinMode(rsPin, OUTPUT);
}

void LiquidCrystal::SetupDisplay()
{
    SendCommand(LCD_CLEARDISPLAY);
    SendCommand(LCD_FUNCTIONSET | LCD_8BITMODE | LCD_2LINE | LCD_5x8DOTS); // 0b00111000 set to 8-bit mode and 2 line display
    SendCommand(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSORON);        // 0b00001110 turning on display and cursor
    SendCommand(LCD_ENTRYMODESET | LCD_ENTRYLEFT);                         //0b00000110 set the mode to increment address by one
}

void LiquidCrystal::Enable()
{
    nonExactDelay(TIME_DELAY_BEFORE_ENABLE);
    digitalWrite(enablePin, HIGH);
}

void LiquidCrystal::SetToWrite()
{
    digitalWrite(rwPin, LOW);
}

void LiquidCrystal::SetToRead()
{
    digitalWrite(rwPin, HIGH);
}

void LiquidCrystal::CommandMode()
{
    digitalWrite(rsPin, LOW);
}

void LiquidCrystal::CharacterMode()
{
    digitalWrite(rsPin, HIGH);
}

void LiquidCrystal::SendByte(char byte)
{
    for (int i = 0; i < displayMode; i++)
    {
        digitalWrite(dataPins[i], (byte >> i) & 0x01);
    }
    /* digitalWrite(LCDD0, (byte & 0b00000001));
    digitalWrite(LCDD1, (byte & 0b00000010));
    digitalWrite(LCDD2, (byte & 0b00000100));
    digitalWrite(LCDD3, (byte & 0b00001000));
    digitalWrite(LCDD4, (byte & 0b00010000));
    digitalWrite(LCDD5, (byte & 0b00100000));
    digitalWrite(LCDD6, (byte & 0b01000000));
    digitalWrite(LCDD7, (byte & 0b10000000));*/
    nonExactDelay(TIME_DELAY_BEFORE_DISABLE);
    digitalWrite(enablePin, LOW);
}

size_t LiquidCrystal::SendCharacter(char character)
{
    SetToWrite();
    CharacterMode();
    Enable();
    SendByte(character);
    return 1; //one char written
}

void LiquidCrystal::SendCommand(char command)
{
    SetToWrite();
    CommandMode();
    Enable();
    SendByte(command);
}

size_t LiquidCrystal::SendString(const char *cString)
{
    size_t n = 0;
    if (cString != NULL)
    {
        while (*cString != '\0')
        {
            SendCharacter(*cString);
            cString++;
            n++;
        }
    }
    return n;
}

size_t LiquidCrystal::print(char character)
{
    return SendCharacter(character);
}

size_t LiquidCrystal::print(const char str[])
{
    return SendString(str);
}

size_t LiquidCrystal::print(unsigned char b, int base)
{
    return print((unsigned long)b, base);
}

size_t LiquidCrystal::print(int n, int base)
{
    return print((long)n, base);
}

size_t LiquidCrystal::print(unsigned int n, int base)
{
    return print((unsigned long)n, base);
}

size_t LiquidCrystal::print(unsigned long n, int base)
{
    return printNumber(n, base);
}

size_t LiquidCrystal::print(long n, int base)
{
    if (base == 10)
    {
        if (n < 0)
        {
            int t = print('-');
            n = -n;
            return printNumber(n, 10) + t;
        }
        return printNumber(n, 10);
    }
    else
    {
        return printNumber(n, base);
    }
}

size_t LiquidCrystal::print(double n, int digits)
{
    return printFloat(n, digits);
}

size_t LiquidCrystal::printNumber(unsigned long n, uint8_t base)
{
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];

    *str = '\0';

    // prevent crash if called with base == 1
    if (base < 2)
    {
        base = 10;
    }

    do
    {
        char c = n % base;
        n /= base;

        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while (n);

    return SendString(str);
}

size_t LiquidCrystal::printFloat(double number, uint8_t digits)
{
    size_t n = 0;

    // Handle negative numbers
    if (number < 0.0)
    {
        n += print('-');
        number = -number;
    }

    // Round correctly so that print(1.999, 2) prints as "2.00"
    double rounding = 0.5;
    for (uint8_t i = 0; i < digits; ++i)
    {
        rounding /= 10.0;
    }

    number += rounding;

    // Extract the integer part of the number and print it
    unsigned long int_part = (unsigned long)number;
    double remainder = number - (double)int_part;
    n += print(int_part);

    // Print the decimal point, but only if there are digits beyond
    if (digits > 0)
    {
        n += print('.');
    }

    // Extract digits from the remainder one at a time
    while (digits-- > 0)
    {
        remainder *= 10.0;
        unsigned int toPrint = (unsigned int)(remainder);
        n += print(toPrint);
        remainder -= toPrint;
    }
    return n;
}

/*
void LiquidCrystal::SendInt(int integer, uint8_t numOfDigits)
{
    char intStr[numOfDigits];
    sprintf(intStr, "%d", integer);

    SendString(intStr);
}

void LiquidCrystal::SendIntHex(int integer, uint8_t numOfDigits)
{
    char intStr[numOfDigits];
    sprintf(intStr, "%X", integer);

    SendString(intStr);
}

void LiquidCrystal::SendFloat(float floatNumber, uint8_t maxLengthOfDigits)
{ // for 256.36 maxLengthOfDigits = 6 
    char numberStr[maxLengthOfDigits];
    snprintf(numberStr, maxLengthOfDigits + 1, "%f", floatNumber);

    SendString(numberStr);
}
*/

void LiquidCrystal::clear()
{
    SendCommand(LCD_CLEARDISPLAY);
}

void LiquidCrystal::home()
{
    SendCommand(LCD_RETURNHOME);
}

void LiquidCrystal::setCursor(uint8_t col, uint8_t row)
{  
  SendCommand(LCD_SETDDRAMADDR | (col + row * LCD_2LINE_HOME_ADDRESS));
}