/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a função principal para o projeto de comunicação WiFi.
 * Data: 23/01/2025
 */

#include "lib.hpp"

/*===============================================================================*/

void setup() {

  // Configura pino do led como saída do sistema
  setupGPIO();

  // Configura sensor DHT
  setupDHT();

  // Configura LCD1602
  setupLCD();

  // Configuração do monitor serial
  Serial.begin(115200);

  // Conexão com rede WiFi escolhida
  WiFiConnect();

  // Criação do Server dentro da rede WiFi escolhida
  createServer();
}

void loop() {

  // Verifica se há requisições de novos clientes e configura rotas adequadas
  handleClient();

  // Se ouver dados do serial, são lidos e transmitidos para página HTML
  if(Serial.available()){
    sendData();  
  }

}
