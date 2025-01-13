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
IPAddress localIP (192,168,1,100);
IPAddress gateway (192,168,1,10);
IPAddress subnet (255,255,255,0);

// Informações da rede WiFi transmitida pelo roteador
const String ssidRounter =  "Usa 3G folgado_2.4GHZ"; // nome da rede
const String passwordRounter =  "soentrabonito";     // senha

// Server WiFI
WebServer server(80);

// String de mensagem enviada do serial para o usuário do servidor
String output;

#endif