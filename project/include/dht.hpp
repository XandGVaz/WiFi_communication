/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a header de utilização do sensor dht.
 * Data: 25/07/2025
 */

#ifndef DHT_HPP
#define DHT_HPP

/*===============================================================================*/
// Uso do sensor DHT
#include <Arduino.h>
#include <Adafruit_Sensor.h>        // autor: adafruit
#include <DHT.h>
#include <DHT_U.h>

/*===============================================================================*/
// Definições do DHT
#define DHT_PIN 13      // pino de saída do sensor DHT
#define DHTTYPE DHT22   // tipo de sensor DHT

/*===============================================================================*/
// Include Guard para evitar múltipla declaração de variáveis globais
#ifdef DEF_MOD_DHT
    #define MOD_DHT extern
#else
    #define MOD_DHT
#endif

/*===============================================================================*/
// Sensor DHT11
MOD_DHT DHT_Unified *DHT;                   // ponteiro para classe DHT
MOD_DHT sensor_t Sensor;                    // classe de um sensor da Adafruit (lib usada)
MOD_DHT String Temperature;                 // dado de temperatura
MOD_DHT String Humidity;                    // dado de humidade

/*===============================================================================*/
// Prototypes do sensor DHT
void setupDHT();
void updateValueDHT();

#endif