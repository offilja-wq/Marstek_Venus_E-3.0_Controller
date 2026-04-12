#include <Arduino.h>

#include "config.h"
#include "iungo.h"
#include "MAX485.h"

HardwareSerial RS485Serial(0); // UART0
ModbusMaster node;

void setMarstekData(TRANSMIT_CODE)
{

}

int32_t getMarstekData(RECEIVE_CODE code)
{
  uint32_t result;
  result = node.readHoldingRegisters(code, 1);
  
  if (result == node.ku8MBSuccess)
    return (int16_t)node.getResponseBuffer(0);
}

void handleMarstek()
{
  int32_t temp = getMarstekData(batteryPowerAC);
}

void marstekBegin()
{
  pinMode(MAX485_MODE_PIN, OUTPUT);

  RS485Serial.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  node.begin(1, RS485Serial); // slave ID = 1
  node.preTransmission(startTransmission);
  node.postTransmission(endTransmission);

  setRS485Mode(RECEIVER);
}

void setup()
{
  Serial.begin(115200);

  marstekBegin();
  iungoBegin();
}

void loop()
{
  // handleMarstek();

  Serial.print("Power Inungo: ");
  Serial.println(getIungoPower());

  delay(300);
}