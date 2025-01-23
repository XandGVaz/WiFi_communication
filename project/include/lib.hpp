/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém as definições de funções e protótipos para o projeto de comunicação WiFi.
 * Data: 23/01/2025
 */

#ifndef HEADER_H
#define HEADER_H

/*===============================================================================*/
// Bibliotecas

// Utilização de funções da ArduinoIDE
#include <Arduino.h>
#include <Wire.h>               

// Criação de servidor
#include <WiFi.h>
#include <WebServer.h>

// Página html do servidor, só declarada dentro da biblioteca
#ifdef DEF_MOD_LIB
#include "html.hpp"
#endif

// Uso do sensor DHT
#include <Adafruit_Sensor.h>        // autor: adafruit
#include <DHT.h>
#include <DHT_U.h>

// Uso do LCD1602
#include <LiquidCrystal_I2C.h>      // autor: marcoschwartz

/*===============================================================================*/
// Definições 

#define PIN_LED 2       // pino de conexão do Led
#define DHT_PIN 13      // pino de saída do sensor DHT
#define DHTTYPE DHT22   // tipo de sensor DHT
#define SDA 33          // serial data
#define SCL 32          // I2C bus
#define CI_ADDR1 0x27   // lcd1602 que usa PCF8574T, endereço I2C é 0x27 
#define CI_ADDR2 0x3F   // lcd1602 que usa PCF8574AT, endereço I2c é 0x3F

// Include Guard para evitar múltipla declaração de variáveis globais
#ifdef DEF_MOD_LIB
    #define MOD_LIB extern
#else
    #define MOD_LIB
#endif

/*===============================================================================*/
// Informações da rede WiFi transmitida pelo roteador

MOD_LIB const String ssidRounter =  "Usa 3G folgado_2.4GHZ"; // nome da rede
MOD_LIB const String passwordRounter =  "soentrabonito";     // senha
MOD_LIB String Sended;                                       // dado enviado para cliente
MOD_LIB WebServer *Server;                                   // ponteiro para classe server 

/*===============================================================================*/
// Sensor DHT11

MOD_LIB DHT_Unified *DHT;                   // ponteiro para classe DHT
MOD_LIB sensor_t Sensor;                    // classe de um sensor da Adafruit (lib usada)
MOD_LIB String Temperature;                 // dado de temperatura
MOD_LIB String Humidity;                    // dado de humidade

/*===============================================================================*/
// Display LCD1602
MOD_LIB LiquidCrystal_I2C *Lcd;             // ponteiro para classe lcd

/*===============================================================================*/
// Prototypes gerais
void setupGPIO();
void setupMonitor();

/*===============================================================================*/
// Prototypes do servidor
void setupServer();
void WiFiConnect();
void handleBlink();
void handleSubmit();
void handleRoot();
void handleUpdate();
void handleClient();
void createServer();
void sendData();

/*===============================================================================*/
// Prototypes do sensor DHT
void setupDHT();
void updateValueDHT();

/*===============================================================================*/
// Prototypes do LCD1602
void setupLCD();
void updateValueLCD(String value);
bool I2cAddrTest(uint8_t addr);


#endif