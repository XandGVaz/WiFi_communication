/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém as variáveis para trabalho com a API freeRTOS.
 * Data: 01/08/2025
 */

#ifndef FREERTOS_VARIABLES_HPP
#define FREERTOS_VARIABLES_HPP

/*===============================================================================*/
// Bibliotecas do FreeRTOS
#include <freertos/FreeRTOS.h>  // API do FreeRTOS
#include <freertos/task.h>      // uso de tasks com freeRTOS
#include <freertos/queue.h>     // uso de filas com freeRTOS

/*===============================================================================*/
// Includ Guard para manipulação de variáveis
#ifdef DEF_MOD_FREERTOS
    #define MOD_FREERTOS extern
#else
    #define MOD_FREERTOS
#endif

/*===============================================================================*/
// Handles das tasks
MOD_FREERTOS xTaskHandle xHandleTaskClient;               // task tratamento de client            
MOD_FREERTOS xTaskHandle xHandleTaskSendData;             // task atualização de mensagem
MOD_FREERTOS xTaskHandle xHandleTaskUpdateTemperatureDHT; // task atualização de temperatura
MOD_FREERTOS xTaskHandle xHandleTaskUpdateHumidityDHT;    // task atualização de umidade
MOD_FREERTOS xTaskHandle xHandleTaskLightMode;            // task de modo da luz
MOD_FREERTOS xTaskHandle xHandleTaskUpdateMessageDisplay; // task atualização mensagem no display

/*===============================================================================*/
// Handles das filas
MOD_FREERTOS xQueueHandle xQueueTemperatureDHT;   // fila de dados de temperatura 
MOD_FREERTOS xQueueHandle xQueueHumidityDHT;      // fila de dados de umidade 
MOD_FREERTOS xQueueHandle xQueueLightMode;        // fila de estados da luz
MOD_FREERTOS xQueueHandle xQueueMessageDisplay;   // fila de mensagens para display

/*===============================================================================*/
// Prototypes das tasks
void vTaskClient(void *pvParameters);               // task tratamento de client
void vTaskSendData(void *pvParameters);             // task atualização de mensagem
void vTaskUpdateTemperatureDHT(void *pvParameters); // task atualização de temperatura
void vTaskUpdateHumidityDHT(void *pvParameters);    // task atualização de umidade
void vTaskLightMode(void *pvParameters);            // task de modo da luz
void vTaskUpdateMessageDisplay(void *pvParameters);  // task atualização mensagem no display

#endif