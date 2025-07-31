/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a header de implementação da iluminação controlada pelo usuário.
 * Data: 31/07/2025
 */

#ifndef LIGHT_HPP
#define LIGHT_HPP

/*===============================================================================*/
// Biblioteca de funções da biblioteca arduino
#include <Arduino.h>

/*===============================================================================*/
// Pino de ativação da iluminação
#define PIN_LIGHT 2

/*===============================================================================*/
// Prototypes das funções de iluminação
void setupLight();  // configura pino de ativação da iluminação
void lightOn();     // ativação da iluminação
void lightOff();    // desativação da iluminação

#endif