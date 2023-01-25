#ifndef LEMONADE_H
#define LEMONADE_H

#include "server.h"
#include "HX711.h"
#include "scale.h"
#include "RGBLed.h"

#define RELAIS_OFFSET 25
#define WATER_PUMP 33

enum lemonadeState_t
{
    IDLE,
    FLAVORING,
    WATERING,
    QUEUED
};

enum lemonadeFlavour_t
{
    LEMON,
    STRAWBERRIE,
    BOSVRUCHTEN
};

void queueLemonade(AsyncWebServerRequest *request);
void handleLemonadeMachine();
void lemonadeInit();

float getSweetnessAmount();
float getCurrentWeight();
String getLemonadeFlavour();
String getLemonadeState();

#endif