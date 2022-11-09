#ifndef SCALE_H
#define SCALE_H

#include "HX711.h"

#define LOADCELL_DOUT_PIN 4
#define LOADCELL_SCK_PIN 5
#define ZERO_FACTOR 141832.f
#define CALIBRATION_FACTOR -101500.00f

void scaleInit();

extern HX711 scale;

#endif