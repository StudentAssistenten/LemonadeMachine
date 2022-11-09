#include "WiFiSetup.h"

void WiFiInit()
{
    pinMode(ONBOARD_LED, OUTPUT);
    digitalWrite(ONBOARD_LED, HIGH);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
        digitalWrite(ONBOARD_LED, !digitalRead(ONBOARD_LED));
    }
}