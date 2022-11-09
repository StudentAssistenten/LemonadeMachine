#include "main.h"

void BSPInit();

void setup()
{
  BSPInit();
}

void loop()
{
  handleLemonadeMachine();
}

void BSPInit()
{
  Serial.begin(115200);
  lemonadeInit();
  RGBLedInit();
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  WiFiInit();
  serverInit();
  digitalWrite(ONBOARD_LED, HIGH);
  colorRGB(GREEN);
}
