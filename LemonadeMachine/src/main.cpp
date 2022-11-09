#include "WiFi.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"
#include "HX711.h"

const char *ssid = "Quinten";
const char *password = "12345678";

HX711 scale;

AsyncWebServer server(80);

#define LOADCELL_DOUT_PIN 4
#define LOADCELL_SCK_PIN 5
#define ZERO_FACTOR 141832.f
#define CALIBRATION_FACTOR -101500.00f
#define RELAIS_OFFSET 25
#define WATER_PUMP 33
#define ONBOARD_LED 2
#define RGB_RED 23
#define RGB_GREEN 22
#define RGB_BLUE 21

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

enum color_t
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE
};

lemonadeState_t lemonadeState = IDLE;
lemonadeFlavour_t lemonadeFlavour = LEMON;

void queueLemonade(AsyncWebServerRequest *request);
void colorRGB(color_t color);
void BSPInit();

void setup()
{
    BSPInit();
    digitalWrite(ONBOARD_LED, HIGH);

    if (!SPIFFS.begin())
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
        digitalWrite(ONBOARD_LED, !digitalRead(ONBOARD_LED));
    }
    colorRGB(GREEN);
    digitalWrite(ONBOARD_LED, HIGH);
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html"); });

    server.on("/gatherData.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/gatherData.js", "text/JavaScript"); });

    server.on("/api/machineState", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(lemonadeState)); });

    server.on("/api/scaleValue", HTTP_GET, [](AsyncWebServerRequest *request)
              { char str[7];
                sprintf(str, "%f", scale.get_units());
                request->send(200, "text/plain", str); });

    server.on("/api/makeLemonade", HTTP_GET, [](AsyncWebServerRequest *request)
              { if(request->hasParam("lemonade"))
                {
                    queueLemonade(request);
                    request->send(200, "text/plain", "OK");
                } else {
                    request->send(200, "text/plain", "Not OK");
                } });

    server.begin();
}

void loop()
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

void BSPInit()
{
    Serial.begin(115200);
    pinMode(ONBOARD_LED, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(RGB_RED, OUTPUT);
    pinMode(RGB_GREEN, OUTPUT);
    pinMode(RGB_BLUE, OUTPUT);

    colorRGB(RED);

    Serial.println("Scale setup");
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale();
    scale.tare();                        // Reset the scale to 0
    scale.set_scale(CALIBRATION_FACTOR); // Adjust to this calibration factor
    Serial.println(scale.get_units(), 3);
}

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