#include "lemonade.h"

lemonadeState_t lemonadeState = IDLE;
lemonadeFlavour_t lemonadeFlavour = LEMON;
float sweetnessAmount = 0.0;
float currentWeight = 0;
lemonadeFlavour_t secondFlavour = LEMON;
bool twoFlavours = false;

#define BASE_SWEETNESS 0.014
#define TOTAL_LIQUID 0.130

float getSweetnessAmount()
{
    return sweetnessAmount;
}

float getCurrentWeight()
{
    return currentWeight;
}

String getLemonadeFlavour()
{
    switch (lemonadeFlavour)
    {
    case LEMON:
        return "Citroen";
        break;
    case STRAWBERRIE:
        return "Aardbei";
        break;
    case BOSVRUCHTEN:
        return "Bosvruchten";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

String getLemonadeState()
{
    switch (lemonadeState)
    {
    case IDLE:
        return "IDLE";
        break;
    case FLAVORING:
        return "FLAVORING";
        break;
    case WATERING:
        return "WATERING";
        break;
    case QUEUED:
        return "QUEUED";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

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
#ifdef DEBUG_LEMONADE
        Serial.print("Flavoring: ");
        Serial.println(currentWeight);
#endif
        if (twoFlavours)
        {
            if (currentWeight > (BASE_SWEETNESS + 0.004))
            {
                digitalWrite(RELAIS_OFFSET + secondFlavour, LOW);
                lemonadeState = WATERING;
                colorRGB(BLUE);
                digitalWrite(WATER_PUMP, HIGH);
            }
            else if (currentWeight > (BASE_SWEETNESS + 0.004) / 2)
            {
                digitalWrite(RELAIS_OFFSET + lemonadeFlavour, LOW);
                digitalWrite(RELAIS_OFFSET + secondFlavour, HIGH);
            }
        }
        else
        {
            if (currentWeight > sweetnessAmount)
            {
                lemonadeState = WATERING;
                digitalWrite(RELAIS_OFFSET + lemonadeFlavour, LOW);
                digitalWrite(WATER_PUMP, HIGH);
                colorRGB(BLUE);
            }
        }
    }
    else if (lemonadeState == WATERING)
    {
#ifdef DEBUG_LEMONADE
        Serial.print("Watering: ");
        Serial.println(currentWeight);
#endif
        if (currentWeight > (TOTAL_LIQUID))
        {
            lemonadeState = IDLE;
            digitalWrite(WATER_PUMP, LOW);
            colorRGB(GREEN);
        }
    }
}

void queueLemonade(AsyncWebServerRequest *request)
{
    Serial.println("Queueing lemonade");
    if (lemonadeState == IDLE)
    {
        lemonadeState = QUEUED;
        lemonadeFlavour = (lemonadeFlavour_t)request->getParam("lemonade")->value().toInt();
        if (request->hasParam("secondFlavour"))
        {
            Serial.println("Two flavours");	
            secondFlavour = (lemonadeFlavour_t)request->getParam("secondFlavour")->value().toInt();
            twoFlavours = true;
        }
        else
        {
            sweetnessAmount = BASE_SWEETNESS * request->getParam("sweetness")->value().toFloat() + 0.004;
            twoFlavours = false;
        }
        Serial.printf("Lemonade type %d queued, sweetness : %f", (uint8_t)lemonadeFlavour, sweetnessAmount);
        if (twoFlavours)
        {
            Serial.printf(" with second flavour %d", (uint8_t)secondFlavour);
        }
        Serial.printf("\n");
    }
}

void lemonadeInit()
{
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(33, OUTPUT);
}