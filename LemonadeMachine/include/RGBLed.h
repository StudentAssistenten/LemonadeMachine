#ifndef RGBLED_H
#define RGBLED_H

#include "Arduino.h"

#define RGB_RED 23
#define RGB_GREEN 22
#define RGB_BLUE 21

enum color_t
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE
};

void colorRGB(color_t color);
void RGBLedInit();

#endif