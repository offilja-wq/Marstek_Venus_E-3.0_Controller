#include <HardwareSerial.h>
#include <ModbusMaster.h>

#define RXD2 3
#define TXD2 1
#define MAX485_DE 33
#define MAX485_RE 33

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

void preTransmission() {
  digitalWrite(MAX485_DE, HIGH);
}

void postTransmission() {
  digitalWrite(MAX485_DE, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_DE, LOW);
  // 👇 Echte hardware UART initialiseren
  RS485Serial.begin(115200, SERIAL_8N1, RXD2, TXD2);
  node.begin(1, RS485Serial); // slave ID = 1
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  Serial.println("Start uitlezen Marstek via RS485...");
}

void loop() {

  readBatteryData();

  Serial.println("");
  Serial.print("Battery Power AC (W) : ");
  Serial.println(currentBatteryPowerAC);
  currentBatteryPower = 0;

  Serial.print("Battery Power intern: ");
  Serial.println(currentBatteryPower_sign);

  Serial.print("Status: ");
  Serial.println(currentBatteryState);

  Serial.print("Percentage batterij: ");
  Serial.println(batteryPercentage);

  Serial.print("Batterij Kwh: ");
  Serial.println(batterySOCKwh);
  Serial.print("Aantal cyclussen: ");    Serial.println(noCycles);
  Serial.print("forceControlStatus: ");  Serial.println(controlStatus);
  Serial.print("forceChargeStatus: ");   Serial.println(forceChargeStatus);
  Serial.print("ChargeCurrentLimit: ");   Serial.println(ChargeCurrentLimit);
  Serial.print("DisChargeCurrentLimit: ");   Serial.println(DisChargeCurrentLimit);
  Serial.print("forceChargePower: ");   Serial.println(forceChargePower);
  Serial.print("forceDisChargePower: ");   Serial.println(forceDisChargePower);



  Serial.println("-------------------");

  delay(3000);
}

void readBatteryData() {
  
  uint32_t result;
  result = node.readHoldingRegisters(30006, 1);
  
  if (result == node.ku8MBSuccess) {
    currentBatteryPowerAC = (int16_t)node.getResponseBuffer(0);
  } else {
    Serial.println("Fout bij lezen 1");
  }  
  delay(1);
  result = node.readHoldingRegisters(35100, 1);
  if (result == node.ku8MBSuccess) {
    currentBatteryState = node.getResponseBuffer(0);
  } else {
    Serial.println("Fout bij lezen 2 ");
  }  
  delay(1);
  result = node.readHoldingRegisters(30001, 1);
  if (result == node.ku8MBSuccess) {
    currentBatteryPower = (int16_t)node.getResponseBuffer(0);
    currentBatteryPower_sign = currentBatteryPower;
  } else {
    Serial.println("Fout bij lezen 3");
  }  
  
  delay(1);
  result = node.readHoldingRegisters(34002, 1);
  if (result == node.ku8MBSuccess) {
  batteryPercentage  = node.getResponseBuffer(0);  
  } else {
    Serial.println("Fout bij lezen 3");
  }  

  delay(1);
  result = node.readHoldingRegisters(32105, 1);
  if (result == node.ku8MBSuccess) {
  batterySOCKwh   = node.getResponseBuffer(0);
    
  } else {
    Serial.println("Fout bij lezen 3");
  }  

  delay(1);
  result = node.readHoldingRegisters(34003, 1);
  if (result == node.ku8MBSuccess) {
  noCycles    = node.getResponseBuffer(0);    
  } else {
    Serial.println("Fout bij lezen 3");
  }  


  delay(1);
  result = node.readHoldingRegisters(42000, 1);
  if (result == node.ku8MBSuccess) {
  controlStatus    = node.getResponseBuffer(0);    
  } else {
    Serial.println("Fout bij lezen 3");
  }  

  delay(1);
  result = node.readHoldingRegisters(42010, 1);
  if (result == node.ku8MBSuccess) {
  forceChargeStatus  = node.getResponseBuffer(0);    
  } else {
    Serial.println("Fout bij lezen 3");
  }  
  
  delay(1);
  result = node.readHoldingRegisters(35111, 1);
  if (result == node.ku8MBSuccess) {
  ChargeCurrentLimit   = node.getResponseBuffer(0);    
  } else {
    Serial.println("Fout bij lezen 3");
  }  
  delay(1);
  result = node.readHoldingRegisters(35112, 1);
  if (result == node.ku8MBSuccess) {
  DisChargeCurrentLimit   = node.getResponseBuffer(0);    
  } else {
    Serial.println("Fout bij lezen 3");
  }
  
  delay(1);
  result = node.readHoldingRegisters(42020, 1);
  if (result == node.ku8MBSuccess) {
  forceChargePower    = node.getResponseBuffer(0);    
  } else {
    Serial.println("Fout bij lezen 3");
  }

 
  delay(1);
  result = node.readHoldingRegisters(42021, 1);
  if (result == node.ku8MBSuccess) {
  forceDisChargePower    = node.getResponseBuffer(0);    
  } else {
    Serial.println("Fout bij lezen 3");
  }
}