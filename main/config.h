#pragma once

#include <Arduino.h>

#include <HardwareSerial.h>
#include <ModbusMaster.h>

#define RX_PIN 3
#define TX_PIN 1
#define MAX485_MODE_PIN 33

typedef enum : bool
{
    TRANSMITTER,
    RECEIVER
} MODE;