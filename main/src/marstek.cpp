#include <Arduino.h>

#include "config.h"
#include "marstek.h"

// HardwareSerial RS485Serial(0); // UART0
// ModbusMaster node;

MODE marstekLiveState;

// void marstekBegin()
// {
//   pinMode(MAX485_MODE_PIN, OUTPUT);
//   digitalWrite(MAX485_MODE_PIN, LOW);
//   // 👇 Echte hardware UART initialiseren
//   RS485Serial.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
//   node.begin(1, RS485Serial); // slave ID = 1
//   node.preTransmission(startTransmission);
//   node.postTransmission(endTransmission);
//   Serial.println("Start uitlezen Marstek via RS485...");

//   setRS485Mode(RECEIVER);
// }

void setRS485Mode(MODE state)
{
    digitalWrite(MAX485_MODE_PIN, state);
    marstekLiveState = state;
}

void startTransmission()
{
    setRS485Mode(RECEIVER);
    // digitalWrite(MAX485_MODE_PIN, HIGH);
}

void endTransmission()
{
    setRS485Mode(TRANSMITTER);
    // digitalWrite(MAX485_MODE_PIN, LOW);
}

// int64_t getMarstekData(uint16_t code)
// { 
//     MODE oldMarstekState = marstekLiveState;
//     setRS485Mode(TRANSMITTER);

//     bool conformation = ((node.readHoldingRegisters(code, 1) == node.ku8MBSuccess) ? true : false);

//     delay(1);

//     setRS485Mode(oldMarstekState);

//     return (conformation ? ((int16_t)node.getResponseBuffer(0)) : 404);
// }
