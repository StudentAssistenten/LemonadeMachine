#include "server.h"

#include "main.h"

AsyncWebServer server(80);

void serverInit()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html"); });

    server.on("/gatherData.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/gatherData.js", "text/JavaScript"); });

    // server.on("/api/machineState", HTTP_GET, [](AsyncWebServerRequest *request)
    //           { request->send(200, "text/plain", String(lemonadeState)); });  TODO: get state from lemonade.cpp

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