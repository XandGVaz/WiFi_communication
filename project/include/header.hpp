#ifndef HEADER_H
#define HEADER_H

/*===============================================================================*/
// Bibliotecas

// Utilização de funções da ArduinoIDE
#include <Arduino.h>

// Criação de servidor
#include <WiFi.h>
#include <WebServer.h>
#ifdef DEF_MOD_HEADER_1
#include "html.hpp"
#endif

// Uso do sensor DHT
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Uso do LCD1602
#include <LiquidCrystal_I2C.h>  
#include <Wire.h>               

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
#ifdef DEF_MOD_HEADER_1
    #define MOD_HEADER_1 extern
#else
    #define MOD_HEADER_1
#endif

/*===============================================================================*/
// Informações da rede WiFi transmitida pelo roteador

MOD_HEADER_1 const String ssidRounter =  "Usa 3G folgado_2.4GHZ"; // nome da rede
MOD_HEADER_1 const String passwordRounter =  "soentrabonito";     // senha
MOD_HEADER_1 String Sended;                                       // dado enviado para cliente
MOD_HEADER_1 WebServer *Server;                                   // ponteiro para classe server 

/*===============================================================================*/
// Sensor DHT11

MOD_HEADER_1 DHT_Unified *DHT;                   // ponteiro para classe DHT
MOD_HEADER_1 sensor_t Sensor;                    // classe de um sensor da Adafruit (lib usada)
MOD_HEADER_1 String Temperature;                 // dado de temperatura
MOD_HEADER_1 String Humidity;                    // dado de humidade

/*===============================================================================*/
// Display LCD1602
MOD_HEADER_1 LiquidCrystal_I2C *lcd;             // ponteiro para classe lcd

/*===============================================================================*/
// Funções do servidor
void serverInit();
void WiFiConnect();
void handleBlink();
void handleSubmit();
void handleRoot();
void handleUpdate();
void createServer();
void handleClient();
void sendData();

/*===============================================================================*/
// Funções do sensor
void dhtInit();
void setupDHT();
void updateValueDHT();

/*===============================================================================*/
// Funções do LCD1602
void lcdInit();
void setupLCD();
void updateValueLCD(String value);
bool I2cAddrTest(uint8_t addr);


#endif