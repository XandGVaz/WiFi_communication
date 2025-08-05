/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a função principal para o projeto de comunicação WiFi.
 * Data: 02/08/2025
 */

/*===============================================================================*/
// Bibliotecas do projeto 
#include "server.hpp"
#include "dht.hpp"
#include "display.hpp"
#include "light.hpp"
#include "freeRTOSVariables.hpp"
#include "rtos.hpp"

/*===============================================================================*/
// Configuração do microcontrolador
void setup() {

  // Configura aparelho de luz
  setupLight();
  
  // Configura sensor DHT
  setupDHT();
  
  // Configura Display1602
  setupDisplay();

  // Configuração do monitor serial
  Serial.begin(115200);

  // Configura server
  setupServer();

  // Conexão com rede WiFi escolhida
  WiFiConnect();

  // Criação do Server dentro da rede WiFi escolhida
  createServer();

  // Iniciação do RTOS
  setupRTOS();
}

void loop() {
}
