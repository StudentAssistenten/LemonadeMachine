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
#define calibration_factor -105500

void makeLemondade(AsyncWebServerRequest *request);

void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(34, INPUT);

    Serial.println("Scale setup");
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale();
    scale.tare();                        // Reset the scale to 0
    scale.set_scale(calibration_factor); // Adjust to this calibration factor
    Serial.println(scale.get_units(), 3);

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
    }

    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html"); });

    server.on("/gatherData.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/gatherData.js", "text/JavaScript"); });

    server.on("/api/toggleMachineState", HTTP_GET, [](AsyncWebServerRequest *request)
              { digitalWrite(2, !digitalRead(2));
                request->send(200, "text/plain", "Led toggled"); });

    server.on("/api/machineState", HTTP_GET, [](AsyncWebServerRequest *request)
              { String status = digitalRead(2) == HIGH ? "on" : "off";
                request->send(200, "text/plain", status); });

    server.on("/api/scaleValue", HTTP_GET, [](AsyncWebServerRequest *request)
              { char str[7];
                sprintf(str, "%f", scale.get_units());
                request->send(200, "text/plain", str); });

    server.on("/api/makeLemonade", HTTP_GET, [](AsyncWebServerRequest *request)
              { if(request->hasParam("lemonade"))
                {
                    makeLemondade(request);
                    request->send(200, "text/plain", "OK");
                } else {
                    request->send(200, "text/plain", "Not OK");
                } });

    server.begin();
}

void loop() {}

void makeLemondade(AsyncWebServerRequest *request)
{
    AsyncWebParameter* p = request->getParam("lemonade");
    if(p->value() == "1")
    {
        digitalWrite(25, HIGH);
        delay(1000);
        digitalWrite(25, LOW);
    }
    else if(p->value() == "2")
    {
        digitalWrite(26, HIGH);
        delay(1000);
        digitalWrite(26, LOW);
    }
    else if(p->value() == "3")
    {
        digitalWrite(27, HIGH);
        delay(1000);
        digitalWrite(27, LOW);
    }
}