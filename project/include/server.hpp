/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a header de implementação de server controlado pela ESP32.
 * Data: 25/07/2025
 */

#ifndef SERVER_HPP
#define SERVER_HPP

/*===============================================================================*/
// Bibliotecas

// Utilização de funções da ArduinoIDE
#include <Arduino.h>              

// Criação de servidor
#include <WiFi.h>
#include <WebServer.h>

// Página html do servidor, só declarada dentro da biblioteca
#ifdef DEF_MOD_SERVER
#include "html.hpp"
#endif

// Pino de led para verificações
#define PIN_LED 2

// Include Guard para evitar múltipla declaração de variáveis globais
#ifdef DEF_MOD_SERVER
    #define MOD_SERVER extern
#else
    #define MOD_SERVER
#endif

/*===============================================================================*/
// Informações da rede WiFi transmitida pelo roteador
MOD_SERVER const String ssidRounter =  "Usa 3G folgado_2.4GHZ";          // nome da rede
MOD_SERVER const String passwordRounter =  "soentrabonito";     // senha
MOD_SERVER String Sended;                                       // dado enviado para cliente
MOD_SERVER WebServer *Server;                                   // ponteiro para classe server 

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


#endif