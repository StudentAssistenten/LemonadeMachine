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
  pinMode(34, INPUT);

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
            { request->send(SPIFFS, "/index.html", "text/html"); });

  server.on("/gatherData.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/gatherData.js", "text/JavaScript"); });

  server.on("/api/toggleMachineState", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    digitalWrite(2, !digitalRead(2));
    request->send(200, "text/plain", "Led toggled"); });

  server.on("/api/machineState", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    String status = digitalRead(2) == HIGH ? "on" : "off";
    request->send(200, "text/plain", status); });

    server.on("/api/scaleValue", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              char str[7];
    sprintf(str, "%d", analogRead(34));
    request->send(200, "text/plain", str); });

  server.begin();
}

void loop() {}