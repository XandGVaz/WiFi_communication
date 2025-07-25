/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a implementação de utilização do sensor dht.
 * Data: 25/07/2025
 */

#include "dht.hpp"

/*===============================================================================*/
// Funções do sensor DHT

// Função responsável por configurar o sensor DHT
void setupDHT(){
  // Criação do objeto DHT
  DHT = new DHT_Unified(DHT_PIN, DHTTYPE);

  // Iniciação do sensor DHT
  DHT->begin();
  DHT->temperature().getSensor(&Sensor);
  DHT->humidity().getSensor(&Sensor);
}

// Função que lê informações do sensor e atualizar dados de temperatura e umidade
void updateValueDHT(){
  
  sensors_event_t event;                          // evento de sensoriamento
  float temperature, humidity;                    // armazena valores numéricos

  // Obtenção da temperatura
  DHT->temperature().getEvent(&event);
  if(isnan(event.temperature)) temperature = -1;  // verifica erros
  else temperature = event.temperature;

  // Obtenção da umidade
  DHT->humidity().getEvent(&event);
  if(isnan(event.relative_humidity)) humidity = -1;// verifica erros
  else humidity = event.temperature;

  // Atualização dos dados de temperatura e umidade
  Temperature = String(temperature); Humidity = String(humidity);
}