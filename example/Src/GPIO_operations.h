#ifndef GPIO_OPEARTIONS_H
#define GPIO_OPEARTIONS_H

#include <stdexcept>
#include <stdint.h>
#include <stdio.h>
#include "LQFP64_pinout.h"


enum PinState
{
  LOW,
  HIGH
};

/* MODER */
enum GPIO_MODE 
{
  INPUT,
  OUTPUT,
  ALTERNATE,
  ANALOG,
  INPUT_PULLUP /* for arduino compatibility */
};

/* OTYPER */
enum GPIO_OUTPUT_TYPE
{
  PUSH_PULL,
  OPEN_DRAIN
};

/* OSPEEDR */
enum GPIO_OUTPUT_SPEED
{
  LOW_SPEED,
  MEDIUM_SPEED,
  HIGH_SPEED,
};

/* PUPDR */
enum GPIO_PULL_UP_DOWN_TYPE
{
  NO_PULL_UP_DOWN,
  PULL_UP,
  PULL_DOWN,
};


void PrintBinary(uint32_t number); /* this is used only for debuging */

/* Enable GPIO */
void EnableIO(GPIO_TypeDef *GPIOx);

/* Read and Write functions */
PinState ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, PinState pinState);
void TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/* GPIO Configuration Functions */
void Init_InputPin_PullUp(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t GPIO_Pin_pos);
void Init_InputPin_PullDown(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t GPIO_Pin_pos);
void Init_Output_PushPull(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t GPIO_Pin_pos);
void Init_IOPin_AlternateFunction(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t GPIO_Pin_pos);
void Init_Output_NoPushPull(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
/* one funtion to rule them all... */
void InitPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_MODE mode, GPIO_OUTPUT_TYPE otype, GPIO_OUTPUT_SPEED speed, GPIO_PULL_UP_DOWN_TYPE pullType);

/* Arduino compatible functions  */
void pinMode(uint8_t pinName, GPIO_MODE mode);
void digitalWrite(uint8_t pinName, PinState pinState);
void digitalWrite(uint8_t pinName, uint32_t pinState);
PinState digitalRead(uint8_t pinName, PinState pinState);


#endif