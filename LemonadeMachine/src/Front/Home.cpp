#include "Home.h"

char homePage[] = {"<h1>Lemonade Machine</h1>\
<h3>Huidige status: %d</h3>\
"};

void printHomePage(WiFiClient client)
{
    client.printf(homePage, 5);
}