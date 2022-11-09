#ifndef SERVER_H
#define SERVER_H

#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

extern AsyncWebServer server;

void serverInit();

#endif