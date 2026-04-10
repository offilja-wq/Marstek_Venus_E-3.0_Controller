#include <Arduino.h>

#include "config.h"
#include "iungo.h"
#include "marstek.h"

HardwareSerial RS485Serial(0); // UART0
ModbusMaster node;

uint16_t batteryPercentage;
uint16_t batterySOCKwh;
uint16_t currentBatteryPower;
int16_t currentBatteryPowerAC;
uint16_t noCycles;
uint16_t  controlStatus;
uint16_t forceChargeStatus;
uint16_t currentBatteryState;
int16_t currentBatteryPower_sign;
uint16_t ChargeCurrentLimit;
uint16_t DisChargeCurrentLimit;
uint16_t forceChargePower;
uint16_t forceDisChargePower;

void readBatteryData() {
  
  uint32_t result;
  result = node.readHoldingRegisters(30006, 1);
  
  if (result == node.ku8MBSuccess)
  {
    currentBatteryPowerAC = (int16_t)node.getResponseBuffer(0);
  }
  else
  {
    Serial.println("Fout bij lezen 1");
  }  

}

void setup() {
  Serial.begin(115200);
  pinMode(MAX485_MODE_PIN, OUTPUT);
  digitalWrite(MAX485_MODE_PIN, LOW);
  // 👇 Echte hardware UART initialiseren
  RS485Serial.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  node.begin(1, RS485Serial); // slave ID = 1
  node.preTransmission(startTransmission);
  node.postTransmission(endTransmission);
  Serial.println("Start uitlezen Marstek via RS485...");
}

void loop() {

  readBatteryData();

  Serial.print("Battery Power AC (W) : ");
  Serial.println(currentBatteryPowerAC);
  Serial.println("-------------------");

  delay(300);
}