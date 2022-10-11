#include "WiFi.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

const char *ssid = "Quinten";
const char *password = "12345678";

AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);

  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.begin(ssid, password);
  // WiFi.softAP(ssid, password);

  // Serial.println(WiFi.softAPIP());

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/home.html", "text/html"); });

  server.on("/gatherData.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/gatherData.js", "text/html"); });

  server.on("/api/toggleLed", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    digitalWrite(2, !digitalRead(2));
    request->send(200, "text/plain", "Led toggled"); });

  server.on("/api/ledStatus", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    String status = digitalRead(2) == HIGH ? "on" : "off";
    request->send(200, "text/plain", status); });

  server.begin();
}

void loop() {}