/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a header de utilização do display.
 * Data: 25/07/2025
 */

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

/*===============================================================================*/
// Bibliotecas de implementação das funções da ArduinoIDE
#include <Arduino.h> // funções arduino
#include <Wire.h>    // i2c

/*===============================================================================*/
// Biblioteca de implementação do display
#include <LiquidCrystal_I2C.h>      // autor: marcoschwartz

/*===============================================================================*/
// Defines
#define SDA 33          // serial data
#define SCL 32          // I2C bus
#define CI_ADDR1 0x27   // lcd1602 que usa PCF8574T, endereço I2C é 0x27 
#define CI_ADDR2 0x3F   // lcd1602 que usa PCF8574AT, endereço I2c é 0x3F

/*===============================================================================*/
// Includ Guard para manipulação de variáveis
#ifdef DEF_MOD_DISPLAY
    #define MOD_DISPLAY extern
#else
    #define MOD_DISPLAY
#endif

/*===============================================================================*/
// Display Display
MOD_DISPLAY LiquidCrystal_I2C *Display;             // ponteiro para classe lcd


/*===============================================================================*/
// Prototypes do Display
void setupDisplay();
void updateMessageDisplay(String value);
bool I2cAddrTest(uint8_t addr);

#endif