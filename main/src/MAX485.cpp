#include <Arduino.h>

#include "config.h"
#include "MAX485.h"

MODE marstekLastState;

void setRS485Mode(MODE state)
{
    if(marstekLastState == state)
        return;

    digitalWrite(MAX485_MODE_PIN, state);
    marstekLastState = state;
}

void startTransmission()
{
    setRS485Mode(RECEIVER);
}

void endTransmission()
{
    setRS485Mode(TRANSMITTER);
}