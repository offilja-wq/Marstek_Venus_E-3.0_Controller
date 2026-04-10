#include <Arduino.h>

#include "config.h"
#include "iungo.h"
#include "marstek.h"


void setup()
{
    Serial.begin(115200);

    marstekBegin();
}

void loop()
{
    Serial.print(getMarstekData(30006));
}