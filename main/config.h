#pragma once

#include <Arduino.h>

// RS485
#include <HardwareSerial.h>
#include <ModbusMaster.h>

#define RX_PIN 3
#define TX_PIN 1
#define MAX485_MODE_PIN 33

// Iungo
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Time.h>

typedef enum : bool
{
    TRANSMITTER,
    RECEIVER
} MODE;

typedef enum : uint16_t
{
    batteryPowerAC = 30006
} RECEIVE_CODE;

typedef enum : uint16_t
{
    
} TRANSMIT_CODE;