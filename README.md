# Liquid Crystal Library for STM32Discovery

This library allows a stm32Discovery board to control LiquidCrystal displays (LCDs) based on the Hitachi HD44780 (or a compatible) chipset, which is found on most text-based LCDs.

This library is based on the Liquid Crystal library for Arduino: the names of the class and functions are same as for the Arduino version, but implemented for the GPIO of the STM32Discovery board. 

So far the library works only in 8-bit mode, which means that you need to use all 8 data pins. 
