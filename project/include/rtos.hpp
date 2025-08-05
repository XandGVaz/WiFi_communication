/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém o header do RTOS .
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

#ifndef RTOS_HPP
#define RTOS_HPP

/*===============================================================================*/
// Includ Guard para manipulação de variáveis
#ifdef DEF_MOD_RTOS
    #define MOD_RTOS extern
#else
    #define MOD_RTOS
#endif



/*===============================================================================*/
// Inclusão da bibliotecas

// Variáveis do RTOS
#include "freeRTOSVariables.hpp"

// Arduino
#include "Arduino.h"

/*===============================================================================*/
// Configuração do RTOS
void setupRTOS();

/*===============================================================================*/
// Prototypes das tasks
void vTaskClient(void *pvParameters);               // task tratamento de client
void vTaskSendData(void *pvParameters);             // task atualização de mensagem
void vTaskUpdateTemperatureDHT(void *pvParameters); // task atualização de temperatura
void vTaskUpdateHumidityDHT(void *pvParameters);    // task atualização de umidade
void vTaskLightMode(void *pvParameters);            // task de modo da luz
void vTaskUpdateMessageDisplay(void *pvParameters); // task atualização mensagem no display

#endif