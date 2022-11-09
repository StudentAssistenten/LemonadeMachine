#include "lemonade.h"

lemonadeState_t lemonadeState;
lemonadeFlavour_t lemonadeFlavour;

void handleLemonadeMachine()
{
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
        Serial.println(scale.get_units());
        if (scale.get_units() > 0.005) // todo: make it a difference in weight instead of an constant
        {
            lemonadeState = WATERING;
            digitalWrite(RELAIS_OFFSET + lemonadeFlavour, LOW);
            colorRGB(BLUE);
        }
    }
    else if (lemonadeState == WATERING)
    {
        Serial.print("Watering: ");
        Serial.println(scale.get_units());
        if (scale.get_units() > 0.130) // todo: make it a difference in weight instead of an constant
        {
            lemonadeState = IDLE;
            digitalWrite(WATER_PUMP, LOW);
            colorRGB(GREEN);
        }
        else
        {
            digitalWrite(WATER_PUMP, HIGH);
        }
    }
}

void queueLemonade(AsyncWebServerRequest *request)
{
    if (lemonadeState == IDLE)
    {
        lemonadeState = QUEUED;
        lemonadeFlavour = (lemonadeFlavour_t)request->getParam("lemonade")->value().toInt();
    }
}

void lemonadeInit()
{
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(33, OUTPUT);
}