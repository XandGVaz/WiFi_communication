/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a função principal para o projeto de comunicação WiFi.
 * Data: 02/08/2025
 */

/*===============================================================================*/
// Descrição das tarefas realizadas no sistema de tempo eral
//obs: não inclui tarefas criadas na configuração do server criado pela ESP32 

/*
Task                       Core  Prio     Descrição
------------------------------------------------------------------------------------------------
vTaskClient                 1     4     Lida com requisições de client
vTaskSendData               1     3     Envia valor do monitor serial para o usuário de página
vTaskUpdateTemperatureDHT   0     2     Atualiza valor de temperatura medido pelo sensor dht
vTaskUpdateHumidityDHT      0     2     Atualiza valor de umidade medido pelo sensor dht
vTaskLightMode              0     3     Defino o modo de acendimento (ligado/desligado) da luz
vTaskUpdateMessageDisplay   0     3     Exibe mensagem enviada por usuários no display
*/

/*===============================================================================*/
// Bibliotecas do projeto 
#include "server.hpp"
#include "dht.hpp"
#include "display.hpp"
#include "light.hpp"
#include "freeRTOSVariables.hpp"

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

  // Criação da fila de medições de temperatura
  xQueueTemperatureDHT = xQueueCreate(2, sizeof(float));
  if(xQueueTemperatureDHT == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da fila de medicoes de temperatura");
    while(1);
  }

  // Criação da fila de medições de umidade
  xQueueHumidityDHT = xQueueCreate(2, sizeof(float));
  if(xQueueHumidityDHT == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da fila de medicoes de umidade");
    while(1);
  }

  xQueueLightMode = xQueueCreate(2, sizeof(uint8_t));
  if(xQueueLightMode == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da fila de estados da luz");
    while(1);
  }

  xQueueMessageDisplay = xQueueCreate(2, sizeof(String*));
  if(xQueueMessageDisplay == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da fila de mensagems a serem exebidas no display");
    while(1);
  }

  // Criação de task de tratamento de requisições do client
  xTaskCreatePinnedToCore(vTaskClient, "TASK_CLIENT", configMINIMAL_STACK_SIZE + 4096 , NULL, 4, &xHandleTaskClient, APP_CPU_NUM);
  if(xHandleTaskClient == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da TASK_CLIENT ");
    while(1);
  }

  // Criação de task de verificação e obtenção dos dados a serem enviados para o usuário
  xTaskCreatePinnedToCore(vTaskSendData, "TASK_SEND_DATA", configMINIMAL_STACK_SIZE + 4096, NULL, 3, &xHandleTaskSendData, APP_CPU_NUM);
  if(xHandleTaskSendData == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da TASK_SEND_DATA ");
    while(1);
  }

  // Criação de task de atualização do valor de temperatura (medido pelo DHT)
  xTaskCreatePinnedToCore(vTaskUpdateTemperatureDHT, "TASK_TEMPERATURE_DHT", configMINIMAL_STACK_SIZE + 4096, NULL, 2, &xHandleTaskUpdateTemperatureDHT, PRO_CPU_NUM);
  if(xHandleTaskUpdateTemperatureDHT == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da TASK_TEMPERATURE_DHT");
    while(1);
  }
  
  // Criação de task de atualização do valor de umidade (medido pelo DHT)
  xTaskCreatePinnedToCore(vTaskUpdateHumidityDHT, "TASK_HUMIDITY_DHT", configMINIMAL_STACK_SIZE + 4096, NULL, 2, &xHandleTaskUpdateHumidityDHT, PRO_CPU_NUM);
  if(xHandleTaskUpdateHumidityDHT == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da TASK_HUMIDITY_DHT");
    while(1);
  }

  // Criação de task de definição do estado da luz
  xTaskCreatePinnedToCore(vTaskLightMode, "TASK_LIGHT_MODE", configMINIMAL_STACK_SIZE + 4096, NULL, 3, &xHandleTaskLightMode, PRO_CPU_NUM);
  if(xHandleTaskLightMode == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da TASK_LIGHT_MODE");
    while(1);
  }

  // Criação de task de definição do estado da luz
  xTaskCreatePinnedToCore(vTaskUpdateMessageDisplay, "TASK_UPDATE_MESSAGE_DISPLAY", configMINIMAL_STACK_SIZE + 16384, NULL, 3, &xHandleTaskUpdateMessageDisplay, PRO_CPU_NUM);
  if(xHandleTaskUpdateMessageDisplay == NULL){
    Serial.println(F("------------------------------------"));
    Serial.print("Erro na criação da TASK_UPDATE_MESSAGE_DISPLAY");
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

    // Bloqueio da task por 10 ms
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

// Verifica se há dados a serem enviados para o cliente (via monitor serial)
void vTaskSendData(void *pvParameters){
  while(1){

    // Se ouver dados do serial, são lidos e transmitidos para página HTML
    if(Serial.available()) sendData();

    // Bloqueio da task por 100ms
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

// Atualização do valor de temperatura medida pelo sensor DHT
void vTaskUpdateTemperatureDHT(void *pvParameters){

  float temperature = 0;

  while(1){

    // Atualização da temperatura antes do envio para fila de medições
    temperature = updateTemperatureDHT();

    // Envio do valor de temperatura atualizado para a fila
    xQueueSend(xQueueTemperatureDHT, &temperature, portMAX_DELAY); 

    // Bloqueio da task por 500ms
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Atualização do valor de umidade medida pelo sensor DHT
void vTaskUpdateHumidityDHT(void *pvParameters){

  float humidity = 0;

  while(1){

    // Atualização do valor de umidade medido pelo sensor DHT 
    humidity = updateHumidityDHT();

    // Envio do valor de umidade atualizado para a fila
    xQueueSend(xQueueHumidityDHT, &humidity, portMAX_DELAY);

    // Bloqueio da task por 500ms
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Atualização do estado da luz
void vTaskLightMode(void *pvParameters){

  uint8_t state;

  while(1){

    // Aguarda (bloqueada) o recebimento do novo estado da luz
    xQueueReceive(xQueueLightMode, &state, portMAX_DELAY);

    // Definição do novo estado da luz
    if(state) lightMode(LIGHT_ON);
    else lightMode(LIGHT_OFF);

    // Bloqueio da task por 50ms
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

// Atualização da mensagem do display
void vTaskUpdateMessageDisplay(void *pvParameters){

  String *receivedMessage = new String("");

  while(1){

    // Recepção de nova mensagem da fila
    xQueueReceive(xQueueMessageDisplay, &receivedMessage, portMAX_DELAY);

    // Atualiza mensagem recebida no display
    updateMessageDisplay(*receivedMessage);

    // Mostra mensagem recebida da fila no monitor serial
    Serial.println(F("------------------------------------"));
    Serial.print("Received: ");
    Serial.println(*receivedMessage);
    
    // Deleta string criada
    delete receivedMessage;
    
    // Bloqueio por 50ms
    vTaskDelay(50);
  }
}
