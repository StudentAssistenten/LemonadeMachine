#include "RGBLed.h"

void colorRGB(color_t color)
{
    switch (color)
    {
    case RED:
        digitalWrite(RGB_RED, HIGH);
        digitalWrite(RGB_GREEN, LOW);
        digitalWrite(RGB_BLUE, LOW);
        break;
    case GREEN:
        digitalWrite(RGB_RED, LOW);
        digitalWrite(RGB_GREEN, HIGH);
        digitalWrite(RGB_BLUE, LOW);
        break;
    case BLUE:
        digitalWrite(RGB_RED, LOW);
        digitalWrite(RGB_GREEN, LOW);
        digitalWrite(RGB_BLUE, HIGH);
        break;
    case YELLOW:
        digitalWrite(RGB_RED, HIGH);
        digitalWrite(RGB_GREEN, HIGH);
        digitalWrite(RGB_BLUE, LOW);
        break;
    case WHITE:
        digitalWrite(RGB_RED, HIGH);
        digitalWrite(RGB_GREEN, HIGH);
        digitalWrite(RGB_BLUE, HIGH);
        break;
    }
}

void RGBLedInit()
{
    pinMode(RGB_RED, OUTPUT);
    pinMode(RGB_GREEN, OUTPUT);
    pinMode(RGB_BLUE, OUTPUT);
    colorRGB(RED);
}