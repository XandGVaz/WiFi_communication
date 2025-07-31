/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a função principal para o projeto de comunicação WiFi.
 * Data: 31/07/2025
 */

#include "server.hpp"
#include "dht.hpp"
#include "display.hpp"
#include "light.hpp"
#include "freertos/FreeRTOS.h"


/*===============================================================================*/
// Configuração do microcontrolador
void setup() {
  // Configura pino do led como saída do sistema
  setupLight();

  // Configura server
  setupServer();

  // Configuração do monitor serial
  Serial.begin(115200);

  // Configura sensor DHT
  setupDHT();

  // Configura Display1602
  setupDisplay();

  // Conexão com rede WiFi escolhida
  WiFiConnect();

  // Criação do Server dentro da rede WiFi escolhida
  createServer();
}

/*===============================================================================*/
// Ciclo de funcionamento
void loop() {

  // Verifica se há requisições de novos clientes e configura rotas adequadas
  handleClient();

  // Se ouver dados do serial, são lidos e transmitidos para página HTML
  if(Serial.available()){
    sendData();  
  }
  
}
