#include "lemonade.h"

lemonadeState_t lemonadeState = IDLE;
lemonadeFlavour_t lemonadeFlavour = LEMON;
float sweetenesAmount = 0.0;
float currentWeight = 0;

#define BASE_SWEETNESS 0.014
#define TOTAL_LIQUID 0.130

void handleLemonadeMachine()
{
    currentWeight = scale.get_units();
    if (lemonadeState == QUEUED)
    {
        lemonadeState = FLAVORING;
        scale.tare(); // Reset the scale to 0
        colorRGB(WHITE);
        digitalWrite(RELAIS_OFFSET + lemonadeFlavour, HIGH);
    }
    else if (lemonadeState == FLAVORING)
    {
        Serial.print("Flavoring: ");
        Serial.println(currentWeight);
        if (currentWeight > 0.014) // TODO: make this value dependant of site input (0.007 is ideal sweetness)
        {
            lemonadeState = WATERING;
            digitalWrite(RELAIS_OFFSET + lemonadeFlavour, LOW);
            digitalWrite(WATER_PUMP, HIGH);
            colorRGB(BLUE);
        }
    }
    else if (lemonadeState == WATERING)
    {
        Serial.print("Watering: ");
        Serial.println(currentWeight);
        if (currentWeight > (TOTAL_LIQUID)) // TODO: make this value dependant of site input
        {
            lemonadeState = IDLE;
            digitalWrite(WATER_PUMP, LOW);
            colorRGB(GREEN);
        }
    }
}

void queueLemonade(AsyncWebServerRequest *request)
{
    if (lemonadeState == IDLE)
    {
        lemonadeState = QUEUED;
        lemonadeFlavour = (lemonadeFlavour_t)request->getParam("lemonade")->value().toInt();
        sweetenesAmount = BASE_SWEETNESS * request->getParam("sweetness")->value().toFloat();
        Serial.printf("Lemonade type %d queued, sweetness : %f", (uint8_t) lemonadeFlavour, sweetenesAmount);
    }
}

void lemonadeInit()
{
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(33, OUTPUT);
}