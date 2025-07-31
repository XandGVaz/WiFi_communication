/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a implementação da iluminação controlada pelo usuário .
 * Data: 31/07/2025
 */

#include "light.hpp"

/*===============================================================================*/
// Funções de iluminação

// Configura pino de ativação da iluminação
void setupLight(){
  pinMode(PIN_LIGHT, OUTPUT);
}

// Ativação da iluminação
void lightOn(){
    digitalWrite(PIN_LIGHT, HIGH);
}     

// Desativação da iluminação
void lightOff(){
    digitalWrite(PIN_LIGHT, LOW);
}    