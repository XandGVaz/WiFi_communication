#ifndef HEADER_H
#define HEADER_H

/*===============================================================================*/
// Bibliotecas

// Utilização de funções da ArduinoIDE
#include <Arduino.h>

// Criação de servidor
#include <WiFi.h>
#include <WebServer.h>
#include "html.hpp"

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

/*===============================================================================*/
// Informações da rede WiFi transmitida pelo roteador

const String ssidRounter =  "Usa 3G folgado_2.4GHZ"; // nome da rede
const String passwordRounter =  "soentrabonito";     // senha
String Sended;                                       // dado enviado para cliente
WebServer Server(80);                                // servidor criado

/*===============================================================================*/
// Sensor DHT11

DHT_Unified DHT(DHT_PIN, DHTTYPE);  // classe do DHT
sensor_t Sensor;                    // classe de um sensor da Adafruit (lib usada)
String Temperature;                 // dado de temperatura
String Humidity;                    // dado de humidade

/*===============================================================================*/
// Display LCD1602
LiquidCrystal_I2C lcd(CI_ADDR1, 16/*colunas*/, 2/*linhas*/); // Objeto lcd

/*===============================================================================*/
// Funções do servidor

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

void setupDHT();
void updateValueDHT();

/*===============================================================================*/
// Funções do LCD1602

void setupLCD();
void updateValueLCD(String value);
bool I2cAddrTest(uint8_t addr);


#endif