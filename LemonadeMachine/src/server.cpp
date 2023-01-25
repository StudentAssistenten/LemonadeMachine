#include "server.h"

#include "main.h"

AsyncWebServer server(80);

void serverInit()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html"); });

    server.on("/Controle", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/control.html", "text/html"); });

    server.on("/gatherData.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/gatherData.js", "text/JavaScript"); });

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

    server.on("/api/setPumpHigh", HTTP_GET, [](AsyncWebServerRequest *request)
              { if(request->hasParam("pump"))
                {
                    int offset = request->getParam("pump")->value().toInt();
                    if(offset > 0)
                        digitalWrite(RELAIS_OFFSET + (offset - 1), HIGH);
                    else
                        digitalWrite(WATER_PUMP, HIGH);

                    request->send(200, "text/plain", "OK");
                } else {
                    request->send(200, "text/plain", "Not OK");
                } });

    server.on("/api/setPumpLow", HTTP_GET, [](AsyncWebServerRequest *request)
              { if(request->hasParam("pump"))
                {
                    int offset = request->getParam("pump")->value().toInt();
                    if(offset > 0)
                        digitalWrite(RELAIS_OFFSET + (offset - 1), LOW);
                    else
                        digitalWrite(WATER_PUMP, LOW);

                    request->send(200, "text/plain", "OK");
                } else {
                    request->send(200, "text/plain", "Not OK");
                } });

    // ------ Control
    server.on("/api/CurrentMachineState", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", getLemonadeState()); });

    server.on("/api/ScaleData", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(getCurrentWeight())); });

    server.on("/api/Uptime", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(millis() / 1000)); });

    server.on("/api/LemonadeFlavour", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", getLemonadeFlavour()); });

    server.on("/api/LemonadeSweetness", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(getSweetnessAmount() * 100)); });

    server.begin();
}