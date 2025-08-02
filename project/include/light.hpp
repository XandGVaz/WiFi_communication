/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a header de implementação da iluminação controlada pelo usuário.
 * Data: 01/08/2025
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
// Includ Guard para manipulação de variáveis e tipos
#ifdef DEF_MOD_LIGHT
    #define MOD_LIGHT extern
#else
    #define MOD_LIGHT
#endif

/*===============================================================================*/
// Enumeração para os possíveis estados da luz
typedef enum{
    LIGHT_OFF = 0U,
    LIGHT_ON = 1U
}light_state_t;

/*===============================================================================*/
// Prototypes das funções de iluminação
void setupLight();                   // configura pino de ativação da iluminação
void lightMode(light_state_t state); // definição do estadom da luz (ligada/desligada)

#endif