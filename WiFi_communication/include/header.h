#ifndef HEADER_H
#define HEADER_H

// Bibliotecas
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "html.h"

// Pinos dos leds
#define PIN_LED 2

// IP, gateway e DNS da ESP 32
IPAddress LocalIP (192,168,1,100);
IPAddress Gateway (192,168,1,10);
IPAddress Subnet (255,255,255,0);

// Informações da rede WiFi transmitida pelo roteador
const String ssidRounter =  "Usa 3G folgado_2.4GHZ"; // nome da rede
const String passwordRounter =  "soentrabonito";     // senha

// String de mensagem enviada do serial para o usuário do servidor
String Sended;

// Servidor criado
WebServer Server(80);

// Funções
void WiFiConnect();
void handleBlink();
void handleSubmit();
void handleRoot();
void handleUpdate();
void createServer();
void handleClient();
void sendData();

#endif