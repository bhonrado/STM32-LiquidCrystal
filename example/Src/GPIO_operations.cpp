#include "GPIO_operations.h"

void PrintBinary(uint32_t number)
{
  while (number)
  {
    if (number & 1)
      printf("1");
    else
      printf("0");

    number >>= 1;
  }
  printf("\n");
}

void EnableIO(GPIO_TypeDef *GPIOx)
{
  if (GPIOx == NULL)
  {
    throw std::invalid_argument("GPIOx is NULL");
  }
  if (GPIOx == GPIOA)
  {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  }
  else if (GPIOx == GPIOB)
  {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
  }
  else if (GPIOx == GPIOC)
  {
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  }
  else if (GPIOx == GPIOD)
  {
    RCC->AHBENR |= RCC_AHBENR_GPIODEN;
  }
  else if (GPIOx == GPIOF)
  {
    RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
  }
}

void TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  if (GPIOx == NULL)
  {
    throw std::invalid_argument("GPIOx is NULL");
  }
  GPIOx->ODR ^= GPIO_Pin;
}

PinState ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  if (GPIOx == NULL)
  {
    throw std::invalid_argument("GPIOx is NULL");
  }

  PinState pinStatus;

  if ((GPIOx->IDR & GPIO_Pin) == (uint32_t)LOW)
  {
    pinStatus = LOW;
  }
  else
  {
    pinStatus = HIGH;
  }
  return pinStatus;
}

PinState digitalRead(uint8_t pinName, PinState pinState)
{
  GPIO_TypeDef *GPIOx = GetPort(pinName);
  int GPIO_Pin = GetPinMask(pinName);
  if (GPIO_Pin == -1)
    printf("pin mask not found.\n");
  return ReadPin(GPIOx, GPIO_Pin);
}


//Instead of writing directly in the ODR, the datasheet suggests it's better to use the BSRR/BRR
void WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, PinState pinState)
{
  if (GPIOx == NULL)
  {
    throw std::invalid_argument("GPIOx is NULL");
  }
  //BSRR (to turn on: write 1 to BS locations, to turn off: write 1 to BR locations)
  if (pinState == LOW)
  {
    GPIOx->BRR |= GPIO_Pin; /* bit reset regiter */
  }
  else //pinState == HIGH
  {
    GPIOx->BSRR |= GPIO_Pin; /* bit set-reset regiter */
  }
}

void digitalWrite(uint8_t pinName, PinState pinState)
{
  GPIO_TypeDef *GPIOx = GetPort(pinName);
  int GPIO_Pin = GetPinMask(pinName);
  if (GPIO_Pin == -1)
    printf("pin mask not found.\n");
  WritePin(GPIOx, GPIO_Pin, pinState);
}

void digitalWrite(uint8_t pinName, uint32_t pinState)
{
  GPIO_TypeDef *GPIOx = GetPort(pinName);
  int GPIO_Pin = GetPinMask(pinName);
  if (GPIO_Pin == -1)
    printf("pin mask not found.\n");
  if (pinState == 0)
  {
    WritePin(GPIOx, GPIO_Pin, LOW);
  }
  else
  {
    WritePin(GPIOx, GPIO_Pin, HIGH);
  }
}

void Init_InputPin_PullUp(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t GPIO_Pin_pos)
{
  if (GPIOx == NULL)
  {
    throw std::invalid_argument("GPIOx is NULL");
  }
  uint16_t pos = GPIO_Pin_pos * 2; //bit position for a 32bit register
  //register MODER has 2 bits for configuration of each pin
  uint16_t bit_0 = 0b01;
  uint16_t bit_1 = 0b10;
  uint32_t pinMask0 = bit_0 << pos;
  uint32_t pinMask1 = bit_1 << pos;
  GPIOx->MODER &= ~(uint32_t)pinMask0; //set as input
  //register PUPDR has 2 bit per pin
  //01: Pull-up
  GPIOx->PUPDR |= pinMask0;
  GPIOx->PUPDR &= ~pinMask1;
}

void Init_InputPin_PullDown(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t GPIO_Pin_pos)
{
  if (GPIOx == NULL)
  {
    throw std::invalid_argument("GPIOx is NULL");
  }
  uint16_t pos = GPIO_Pin_pos * 2; //bit position for a 32bit register
  //register MODER has 2 bits for configuration of each pin
  uint16_t bit_0 = 0b01;
  uint16_t bit_1 = 0b10;
  uint32_t pinMask0 = bit_0 << pos;
  uint32_t pinMask1 = bit_1 << pos;
  GPIOx->MODER &= ~(uint32_t)pinMask0; //set as input
  //register PUPDR has 2 bit per pin
  //10: Pull-down
  GPIOx->PUPDR &= ~pinMask0;
  GPIOx->PUPDR |= pinMask1;
}

void Init_Output_NoPushPull(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  InitPin(GPIOx, GPIO_Pin, OUTPUT, PUSH_PULL, HIGH_SPEED, NO_PULL_UP_DOWN);
  /*
  if (GPIOx == NULL)
  {
    throw std::invalid_argument("GPIOx is NULL");
  }
  int bitPos = GetBitPosition(GPIO_Pin);
  if (bitPos == -1)
    printf("error. pin position -1\n");
  uint16_t pos = bitPos * 2; //bit position for a 32bit register*/
  /* set as input */
  /* GPIOx->MODER |= GPIO_MODER_MODER0_0 << pos;
  GPIOx->MODER &= ~(GPIO_MODER_MODER0_1 << pos);*/
  /* set no push pull */
  //GPIOx->OTYPER &= ~(uint32_t)GPIO_Pin;
  /* set high speed */
  //GPIOx->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR0_0 << pos) | (GPIO_OSPEEDER_OSPEEDR0_1 << pos);
}

void pinMode(uint8_t pinName, GPIO_MODE mode)
{
  GPIO_TypeDef *GPIOx = GetPort(pinName);
  int GPIO_Pin = GetPinMask(pinName);
  if (GPIO_Pin == -1)
    printf("pin mask not found.\n");
  EnableIO(GPIOx);
  switch (mode)
  {
  case INPUT: /* pull-down */
  {
    InitPin(GPIOx, GPIO_Pin, INPUT, PUSH_PULL, LOW_SPEED, PULL_DOWN);
    break;
  }
  case INPUT_PULLUP:
  {
    InitPin(GPIOx, GPIO_Pin, INPUT, PUSH_PULL, LOW_SPEED, PULL_UP);
    break;
  }
  case OUTPUT:
  {
    InitPin(GPIOx, GPIO_Pin, OUTPUT, PUSH_PULL, HIGH_SPEED, NO_PULL_UP_DOWN);
    break;
  }
  default:
    printf("pin mode not supported. \n");
    break;
  }
}

void Init_Output_PushPull(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t GPIO_Pin_pos)
{
  if (GPIOx == NULL)
  {
    throw std::invalid_argument("GPIOx is NULL");
  }
  uint16_t pos = GPIO_Pin_pos * 2; //bit position for a 32bit register
  //register MODER has 2 bits for configuration of each pin
  uint16_t bit_0 = 1;
  uint16_t bit_1 = 2;
  GPIOx->MODER |= (uint32_t)(bit_0 << pos);
  //register OTYPER has 1 bit per pin
  // set pin to output type to push-pull
  GPIOx->OTYPER &= ~(uint32_t)GPIO_Pin; //set push pull
}

void Init_IOPin_AlternateFunction(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t GPIO_Pin_pos)
{
  if (GPIOx == NULL)
  {
    throw std::invalid_argument("GPIOx is NULL");
  }
  uint16_t pos = GPIO_Pin_pos * 2; //bit position for a 32bit register
  //register MODER has 2 bits for configuration of each pin
  uint16_t bit_0 = 0b01;
  uint16_t bit_1 = 0b10;
  uint32_t pinMask0 = bit_0 << pos;
  uint32_t pinMask1 = bit_1 << pos;

  // MODER 10: Alternate function mode
  GPIOx->MODER &= ~(uint32_t)pinMask0;
  GPIOx->MODER |= (uint32_t)pinMask1;

  //register PUPDR has 2 bit per pin
  // PUPDR 00: No pull-up, pull-down
  GPIOx->PUPDR &= ~(uint32_t)pinMask0;
  GPIOx->PUPDR &= ~(uint32_t)pinMask1;

  // OSPEEDR 11: high speed
  GPIOx->OSPEEDR |= (uint32_t)(pinMask0 | pinMask1);
}

void InitPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_MODE mode, GPIO_OUTPUT_TYPE otype, GPIO_OUTPUT_SPEED speed, GPIO_PULL_UP_DOWN_TYPE pullType)
{
  if (GPIOx == NULL)
  {
    throw std::invalid_argument("GPIOx is NULL");
  }

  int bitPos = GetBitPosition(GPIO_Pin);
  if (bitPos == -1)
    printf("error. pin position -1\n");

  switch (mode)
  {
  case INPUT:
  {
    /* set input mode :00 */
    GPIOx->MODER &= ~(GPIO_MODER_MODER0_0 << (bitPos * 2));
    GPIOx->MODER &= ~(GPIO_MODER_MODER0_1 << (bitPos * 2));
    break;
  }
  case OUTPUT:
  {
    /* set output mode :01 */
    GPIOx->MODER |= GPIO_MODER_MODER0_0 << (bitPos * 2);
    GPIOx->MODER &= ~(GPIO_MODER_MODER0_1 << (bitPos * 2));
    break;
  }
  case ALTERNATE:
  {
    /* set alternate mode :10 */
    GPIOx->MODER &= ~(GPIO_MODER_MODER0_0 << (bitPos * 2));
    GPIOx->MODER |= GPIO_MODER_MODER0_1 << (bitPos * 2);
    break;
  }
  case ANALOG:
  {
    /* set analog mode :11 */
    GPIOx->MODER |= GPIO_MODER_MODER0_1 << (bitPos * 2);
    GPIOx->MODER |= GPIO_MODER_MODER0_0 << (bitPos * 2);
    break;
  }
  default:
    break;
  }

  switch (otype) /* output */
  {
  case PUSH_PULL:
  {
    /* 0 */
    GPIOx->OTYPER &= ~(GPIO_OTYPER_OT_0 << bitPos);
    break;
  }
  case OPEN_DRAIN:
  {
    /* 1 */
    GPIOx->OTYPER |= GPIO_OTYPER_OT_0 << bitPos;
    break;
  }
  default:
    break;
  }

  switch (pullType) /* input*/
  {
  case NO_PULL_UP_DOWN:
  { /* 00 */
    GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0_0 << (bitPos * 2));
    GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0_1 << (bitPos * 2));
    break;
  }
  case PULL_UP:
  { /* 01 */
    GPIOx->PUPDR |= GPIO_PUPDR_PUPDR0_0 << (bitPos * 2);
    GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0_1 << (bitPos * 2));
    break;
  }
  case PULL_DOWN:
  { /* 10 */
    GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0_0 << (bitPos * 2));
    GPIOx->PUPDR |= GPIO_PUPDR_PUPDR0_1 << (bitPos * 2);
    break;
  }
  default:
    break;
  }

  switch (speed) /* output */
  {
  case LOW_SPEED:
  {
    /* x0 */
    GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0_0 << (bitPos * 2));
    GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0_1 << (bitPos * 2));
    break;
  }
  case MEDIUM_SPEED:
  {
    /* 01 */
    GPIOx->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR0_0 << (bitPos * 2);
    GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0_1 << (bitPos * 2));
    break;
  }
  case HIGH_SPEED:
  {
    /* 11 */
    GPIOx->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR0_0 << (bitPos * 2);
    GPIOx->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR0_1 << (bitPos * 2);
    break;
  }
  default:
    break;
  }
}