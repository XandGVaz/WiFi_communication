/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a função principal para o projeto de comunicação WiFi.
 * Data: 31/07/2025
 */

// API do FreeRTOS
#include "freertos/FreeRTOS.h"

// Bibliotecas do projeto 
#include "server.hpp"
#include "dht.hpp"
#include "display.hpp"
#include "light.hpp"

/*===============================================================================*/
// Handles das tasks
xTaskHandle xHandleTaskClient = NULL;            
xTaskHandle xHandleTaskSendData = NULL;
xTaskHandle xHandleTaskUpdateTemperatureDHT = NULL;
xTaskHandle xHandleTaskUpdateHumidityDHT = NULL;

/*===============================================================================*/
// Prototypes das tasks
void vTaskClient(void *pvParameters);               
void vTaskSendData(void *pvParameters);
void vTaskUpdateTemperatureDHT(void *pvParameters);
void vTaskUpdateHumidityDHT(void *pvParameters);


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

  // Criação das tasks
  xTaskCreate(vTaskClient, "TASK_CLIENT", configMINIMAL_STACK_SIZE + 2048 , NULL, 10, &xHandleTaskClient);
  if(xHandleTaskClient == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da TASK_CLIENT ");
    while(1);
  }
  xTaskCreate(vTaskSendData, "TASK_SEND_DATA", configMINIMAL_STACK_SIZE + 1024, NULL, 3, &xHandleTaskSendData);
  if(xHandleTaskSendData == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da TASK_SEND_DATA ");
    while(1);
  }
  xTaskCreate(vTaskUpdateTemperatureDHT, "TASK_TEMPERATURE_DHT", configMINIMAL_STACK_SIZE + 2048, NULL, 1, &xHandleTaskUpdateTemperatureDHT);
  if(xHandleTaskUpdateTemperatureDHT == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da TASK_TEMPERATURE_DHT");
    while(1);
  }
  xTaskCreate(vTaskUpdateHumidityDHT, "TASK_HUMIDITY_DHT", configMINIMAL_STACK_SIZE + 2048, NULL, 1, &xHandleTaskUpdateHumidityDHT);
  if(xHandleTaskUpdateHumidityDHT == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da TASK_HUMIDITY_DHT");
    while(1);
  }

}

void loop() {
}

/*===============================================================================*/
// Funções das tasks

// Processa requisições dos clientes de forma não bloqueante
void vTaskClient(void *pvParameters){
  while(1){

    // Verifica se há requisições de novos clientes e configura rotas adequadas
    handleClient();

    // Executada a cada 20 ms
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

// Verifica se há dados a serem enviados para o cliente (via monitor serial)
void vTaskSendData(void *pvParameters){
  while(1){

    // Se ouver dados do serial, são lidos e transmitidos para página HTML
    if(Serial.available()) sendData();

    // Delay de 50ms
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

// Atualização do valor de temperatura medida pelo sensor DHT
void vTaskUpdateTemperatureDHT(void *pvParameters){
  while(1){

    // Atualização do valor de temperatura medido pelo sensor DHT
    updateTemperatureDHT();

    // Delay de 1s
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// Atualização do valor de umidade medida pelo sensor DHT
void vTaskUpdateHumidityDHT(void *pvParameters){
  while(1){

    // Atualização do valor de umidade medido pelo sensor DHT 
    updateHumidityDHT();

    // Delay de 1s
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
