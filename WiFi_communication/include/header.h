#ifndef HEADER_H
#define HEADER_H

/*===============================================================================*/
// Bibliotecas
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "html.h"

/*===============================================================================*/
// Configuração de pinos
#define PIN_LED 2
#define DHT_PIN 13

/*===============================================================================*/
// Informações da rede WiFi transmitida pelo roteador
const String ssidRounter =  "Usa 3G folgado_2.4GHZ"; // nome da rede
const String passwordRounter =  "soentrabonito";     // senha

// String de mensagem enviada do serial para o usuário do servidor
String Sended;

// Servidor criado
WebServer Server(80);

/*===============================================================================*/
// Sensor DHT11
DHT_Unified DHT(DHT_PIN, DHT11);

//Temperatura e umidade
String Temperature; 
String Humidity;

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
sensor_t Sensor;
void setupDHT();
void updateValueDHT();

/*===============================================================================*/
// Delay de funcionamento do sistema
#define delayMS 100
uint32_t delayDHT;

#endif