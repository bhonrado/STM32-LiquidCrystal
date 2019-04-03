#ifndef LQFP64_PINOUT_H
#define LQFP64_PINOUT_H

#include <stdint.h>
#include <stdexcept>
#include "stm32f051x8.h"

/*             PIN NAMES                */
//#define VBAT 1
#define PC13 2
#define PC14 3
#define PC15 4
#define PF0  5
#define PF1  6
//#define NRST 7
#define PC0  8
#define PC1  9
#define PC2  10
#define PC3  11
//#define VSSA 12
//#define VDDA 13
#define PA0  14
#define PA1  15
#define PA2  16
#define PA3  17
#define PF4  18
#define PF5  19
#define PA4  20
#define PA5  21
#define PA6  22
#define PA7  23
#define PC4  24
#define PC5  25
#define PB0  26
#define PB1  27
#define PB2  28
#define PB10 29
#define PB11 30
//#define VSS  31
//#define VDD  32
#define PB12 33
#define PB13 34
#define PB14 35
#define PB15 36
#define PC6  37
#define PC7  38
#define PC8  39
#define PC9  40
#define PA8  41
#define PA9  42
#define PA10 43
#define PA11 44
#define PA12 45
#define PA13 46 //SWDIO
#define PF6  47
#define PF7  48
#define PA14 49 //SWCLK
#define PA15 50
#define PC10 51
#define PC11 52
#define PC12 53
#define PD2  54
#define PB3  55
#define PB4  56
#define PB5  57
#define PB6  58
#define PB7  59
//#define BOOT0 60
#define PB8  61
#define PB9  62
//#define VSS  63
//#define VDD  64

#define GPIO_PIN_0                 ((uint16_t)0x0001U)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002U)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004U)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008U)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010U)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020U)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040U)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080U)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100U)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200U)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400U)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800U)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000U)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000U)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000U)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000U)  /* Pin 15 selected   */

int GetPinMask(uint8_t pinName);
int GetBitPosition(unsigned number);
int GetPinNumber(uint8_t pinName);
GPIO_TypeDef *GetPort(uint8_t pinName);

#endif