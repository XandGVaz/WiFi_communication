/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a implementação da iluminação controlada pelo usuário .
 * Data: 01/08/2025
 */

#include "light.hpp"

/*===============================================================================*/
// Funções de iluminação

// Configura pino de ativação da iluminação
void setupLight(){
  pinMode(PIN_LIGHT, OUTPUT);
}

// Definição do estado da luz (ligada/desligada)
void lightMode(light_state_t state){
  if(state == LIGHT_ON) digitalWrite(PIN_LIGHT, HIGH);  // ativação da iluminação
  else digitalWrite(PIN_LIGHT, LOW);                    // desativação da iluminação
}