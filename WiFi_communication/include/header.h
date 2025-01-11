#ifndef LIBB_H
#define LIBB_H

#include <Arduino.h>
#include <WiFi.h>

// Pinos dos leds
#define RED_LED 2
#define BLUE_LED 4
#define GREEN_LED 6

// IP, gateway e DNS da rede transmitida pela ESP 32
IPAddress local_ip();
IPAddress gateway();
IPAddress dns (255,255,255,0);



#endif