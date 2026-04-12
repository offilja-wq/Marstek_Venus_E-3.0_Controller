#pragma once

#include <Arduino.h>

#include "config.h"

void setRS485Mode(MODE state);

void startTransmission();

void endTransmission();