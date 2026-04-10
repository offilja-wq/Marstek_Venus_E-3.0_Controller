#pragma once

#include <Arduino.h>

#include "config.h"

// void marstekBegin();

void setRS485Mode(MODE state);

// int64_t getMarstekData(uint16_t code);

void startTransmission();

void endTransmission();