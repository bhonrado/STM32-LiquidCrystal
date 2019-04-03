#include "LQFP64_pinout.h"

int GetPinMask(uint8_t pinName)
{
    int result = -1;
    switch (pinName)
    {
    case PC13:
        result = GPIO_PIN_13;
        break;
    case PC14:
        result = GPIO_PIN_14;
        break;
    case PC15:
        result = GPIO_PIN_15;
        break;
    case PF0:
        result = GPIO_PIN_0;
        break;
    case PF1:
        result = GPIO_PIN_1;
        break;
    case PC0:
        result = GPIO_PIN_0;
        break;
    case PC1:
        result = GPIO_PIN_1;
        break;
    case PC2:
        result = GPIO_PIN_2;
        break;
    case PC3:
        result = GPIO_PIN_3;
        break;
    case PA0:
        result = GPIO_PIN_0;
        break;
    case PA1:
        result = GPIO_PIN_1;
        break;
    case PA2:
        result = GPIO_PIN_2;
        break;
    case PA3:
        result = GPIO_PIN_3;
        break;
    case PF4:
        result = GPIO_PIN_4;
        break;
    case PF5:
        result = GPIO_PIN_5;
        break;
    case PA4:
        result = GPIO_PIN_4;
        break;
    case PA5:
        result = GPIO_PIN_5;
        break;
    case PA6:
        result = GPIO_PIN_6;
        break;
    case PA7:
        result = GPIO_PIN_7;
        break;
    case PC4:
        result = GPIO_PIN_4;
        break;
    case PC5:
        result = GPIO_PIN_5;
        break;
    case PB0:
        result = GPIO_PIN_0;
        break;
    case PB1:
        result = GPIO_PIN_1;
        break;
    case PB2:
        result = GPIO_PIN_2;
        break;
    case PB10:
        result = GPIO_PIN_10;
        break;
    case PB11:
        result = GPIO_PIN_11;
        break;
    case PB12:
        result = GPIO_PIN_12;
        break;
    case PB13:
        result = GPIO_PIN_13;
        break;
    case PB14:
        result = GPIO_PIN_14;
        break;
    case PB15:
        result = GPIO_PIN_15;
        break;
    case PC6:
        result = GPIO_PIN_6;
        break;
    case PC7:
        result = GPIO_PIN_7;
        break;
    case PC8:
        result = GPIO_PIN_8;
        break;
    case PC9:
        result = GPIO_PIN_9;
        break;
    case PA8:
        result = GPIO_PIN_8;
        break;
    case PA9:
        result = GPIO_PIN_9;
        break;
    case PA10:
        result = GPIO_PIN_10;
        break;
    case PA11:
        result = GPIO_PIN_11;
        break;
    case PA12:
        result = GPIO_PIN_12;
        break;
    case PF6:
        result = GPIO_PIN_6;
        break;
    case PF7:
        result = GPIO_PIN_7;
        break;
    case PA15:
        result = GPIO_PIN_15;
        break;
    case PC10:
        result = GPIO_PIN_10;
        break;
    case PC11:
        result = GPIO_PIN_11;
        break;
    case PC12:
        result = GPIO_PIN_12;
        break;
    case PD2:
        result = GPIO_PIN_2;
        break;
    case PB3:
        result = GPIO_PIN_3;
        break;
    case PB4:
        result = GPIO_PIN_4;
        break;
    case PB5:
        result = GPIO_PIN_5;
        break;
    case PB6:
        result = GPIO_PIN_6;
        break;
    case PB7:
        result = GPIO_PIN_7;
        break;
    case PB8:
        result = GPIO_PIN_8;
        break;
    case PB9:
        result = GPIO_PIN_9;
        break;
    default:
        break;
    }
    return result;
}

// A utility function to check whether n is power of 2 or not. See http://goo.gl/17Arj
int isPowerOfTwo(unsigned n)
{
    return n && (!(n & (n - 1)));
}
//https://www.geeksforgeeks.org/find-position-of-the-only-set-bit/
int GetBitPosition(unsigned number)
{
    if (!isPowerOfTwo(number))
        return -1;
    unsigned i = 1, pos = 0;
    // Iterate through bits of n till we find a set bit
    // i&n will be non-zero only when 'i' and 'n' have a set bit
    // at same position
    while (!(i & number))
    {
        // Unset current bit and set the next bit in 'i'
        i = i << 1;

        // increment position
        ++pos;
    }

    return pos;
}

int GetPinNumber(uint8_t pinName)
{
    int pinMask = GetPinMask(pinName);
    if (pinMask == -1)
        return -1;
    int bitPos = GetBitPosition(pinMask);
    if (bitPos == -1)
        return -1;
    return bitPos;
}

GPIO_TypeDef * GetPort(uint8_t pinName)
{
    if(pinName == PA0 || pinName == PA1 || pinName == PA2 
        || pinName == PA3 || pinName == PA4 || pinName == PA5 
        || pinName == PA6 || pinName == PA7 || pinName == PA8 
        || pinName == PA9 || pinName == PA10 || pinName == PA11
        || pinName == PA12 || pinName == PA13 || pinName == PA14 
        || pinName == PA15 )
    {
        return GPIOA;
    }
    else if (pinName == PB0 || pinName == PB1 || pinName == PB2 
        || pinName == PB3 || pinName == PB4 || pinName == PB5 
        || pinName == PB6 || pinName == PB7 || pinName == PB8 
        || pinName == PB9 || pinName == PB10 || pinName == PB11
        || pinName == PB12 || pinName == PB13 || pinName == PB14 
        || pinName == PB15 )
    {
        return GPIOB;
    }
    else if (pinName == PC0 || pinName == PC1 || pinName == PC2 
        || pinName == PC3 || pinName == PC4 || pinName == PC5 
        || pinName == PC6 || pinName == PC7 || pinName == PC8 
        || pinName == PC9 || pinName == PC10 || pinName == PC11
        || pinName == PC12 || pinName == PC13 || pinName == PC14 
        || pinName == PC15 )
    {
        return GPIOC;
    }
    else if (pinName == PD2 )
    {
        return GPIOD;
    }
    else if (pinName == PF0 || pinName == PF1 || pinName == PF4 
        || pinName == PF5 || pinName == PF6 || pinName == PF7 )
    {
        return GPIOF;
    }
    else
    {
        throw std::invalid_argument("pinName is not a valid pin.");
    }
}