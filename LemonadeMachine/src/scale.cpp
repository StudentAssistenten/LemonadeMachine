#include "scale.h"

HX711 scale;

void scaleInit()
{
    Serial.println("Scale setup");
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale();
    scale.tare();                        // Reset the scale to 0
    scale.set_scale(CALIBRATION_FACTOR); // Adjust to this calibration factor
    Serial.println(scale.get_units(), 3);
}