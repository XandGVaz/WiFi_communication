/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a implementação de utilização do sensor dht.
 * Data: 25/07/2025
 */

#define DEF_MOD_DHT
#include "dht.hpp"

/*===============================================================================*/
// Funções do sensor DHT

// Função responsável por configurar o sensor DHT
void setupDHT(){
  // Criação do objeto DHT
  DHT = new DHT_Unified(DHT_PIN, DHTTYPE);

  Temperature = String(-1);
  Humidity = String(-1);

  // Iniciação do sensor DHT
  DHT->begin();
  DHT->temperature().getSensor(&Sensor);
  DHT->humidity().getSensor(&Sensor);
}

// Função que lê informações do sensor e atualizar dados de temperatura
void updateTemperatureDHT(){
  sensors_event_t event;  // evento de sensoriamento
  float temperature;      // armazena valor numérico da temperatura

  // Obtenção da temperatura
  DHT->temperature().getEvent(&event);
  if(isnan(event.temperature)) temperature = -1;  // verifica erros
  else temperature = event.temperature;
  

  // Atualização dos dados de temperatura
  Temperature = String(temperature);
}

// Função que lê informações do sensor e atualizar dados de umidade
void updateHumidityDHT(){
  sensors_event_t event;      // evento de sensoriamento
  float humidity;             // armazena valor numérico da umidade

  // Obtenção da umidade
  DHT->humidity().getEvent(&event);
  if(isnan(event.relative_humidity)) humidity = -1;// verifica erros
  else humidity = event.relative_humidity;

  // Atualização dos dados de umidade
  Humidity = String(humidity);
}