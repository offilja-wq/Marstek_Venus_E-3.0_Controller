#include <Arduino.h>

#include "config.h"
#include "marstek.h"

// HardwareSerial RS485Serial(0); // UART0
// ModbusMaster node;

MODE marstekLiveState;

void setRS485Mode(MODE state)
{
    digitalWrite(MAX485_MODE_PIN, state);
    marstekLiveState = state;
}

void startTransmission()
{
    setRS485Mode(RECEIVER);
}

void endTransmission()
{
    setRS485Mode(TRANSMITTER);
}