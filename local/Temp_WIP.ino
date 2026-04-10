// time lib
// #include <Time.h>
// #include <WiFi.h>

//  Marstek
#include <HardwareSerial.h>
#include <ModbusMaster.h>
#include <ArduinoJson.h>

#define RXD2 3
#define TXD2 1
#define MAX485_DE 33
#define MAX485_RE 33
// End marstek


const int minBatteryPercentage = 12;
const int minPowerexport= -75;
const int minPowerload = 50;

const int MaxReturnPower = -800;
const int MaxLoadPower = 1000;
const int BatteryCapacity = 2500;

HardwareSerial RS485Serial(0); // UART0
ModbusMaster node;


const char* ssid = "Verjaardag";
const char* wachtwoord = "ruthilja";
const char* url_iungo = "http://192.168.2.4/iungo/api_request/objmgr_get_objects_init?oid=538d72d9";

int16_t  iungo_usage;
int16_t  iungo_usage_oud;

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



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  setupWifi();
  // Serial.println("Na setup wifi");

  // Marstek
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
  // put your main code here, to run repeatedly:

  //iungo_usage = ophalenIungoLoad(iungo_usage_oud);
  //iungo_usage_oud = iungo_usage;
  Serial.print("In de loop, iungo_usage:");
  //Serial.println(iungo_usage);

  uint32_t result;
  result = node.readHoldingRegisters(30006, 1);
  
  if (result == node.ku8MBSuccess) {
    currentBatteryPowerAC = (int16_t)node.getResponseBuffer(0);
  } else {
    Serial.println("Fout bij lezen 1");
  }

  Serial.println(currentBatteryPowerAC);

  // readBatteryData();
  // Serial.println("LOSSSS");
  //  uint32_t result;
  // result = node.readHoldingRegisters(30006, 1);
  
  // if (result == node.ku8MBSuccess) {
  //   currentBatteryPowerAC = (int16_t)node.getResponseBuffer(0);
  // } else {
  //   Serial.println("Fout bij lezen 1");
  // }  

  
  delay(3000);
  //currentBatteryPowerAC = readcurrentBatteryPowerAC();
  //currentBatteryState = readcurrentBatteryState();
  
  // Serial.println('Batterijpercentage : ', batteryPercentage);
  delay(1000);
}





void preTransmission() {
  delay(10);
  digitalWrite(MAX485_DE, HIGH);
}
void postTransmission() {
  delay(10);
  digitalWrite(MAX485_DE, LOW);
}

void readBatteryData() {
  uint32_t result; 
  delay(10);
  result = node.readHoldingRegisters(30006, 1);
  if (result == node.ku8MBSuccess) {
    currentBatteryPowerAC = (int16_t)node.getResponseBuffer(0);
  } else {
    Serial.println("Fout bij lezen 1");
  }  
  delay(10);
  result = node.readHoldingRegisters(35100, 1);
  if (result == node.ku8MBSuccess) {
    currentBatteryState = node.getResponseBuffer(0);
  } else {
    Serial.println("Fout bij lezen 2 ");
  }  
  delay(10);
  result = node.readHoldingRegisters(30001, 1);
  if (result == node.ku8MBSuccess) {
    currentBatteryPower = (int16_t)node.getResponseBuffer(0);
    currentBatteryPower_sign = currentBatteryPower;
  } else {
    Serial.println("Fout bij lezen 3");
  }  
  
  delay(10);
  result = node.readHoldingRegisters(34002, 1);
  if (result == node.ku8MBSuccess) {
  batteryPercentage  = node.getResponseBuffer(0);  
  } else {
    Serial.println("Fout bij lezen 3");
  }  

  delay(10);
  result = node.readHoldingRegisters(32105, 1);
  if (result == node.ku8MBSuccess) {
  batterySOCKwh   = node.getResponseBuffer(0);
    
  } else {
    Serial.println("Fout bij lezen 32105");
  }  

  delay(10);
  result = node.readHoldingRegisters(34003, 1);
  if (result == node.ku8MBSuccess) {
  noCycles    = node.getResponseBuffer(0);    
  } else {
    Serial.println("Fout bij lezen 3");
  }  


  delay(10);
  result = node.readHoldingRegisters(42000, 1);
  if (result == node.ku8MBSuccess) {
  controlStatus    = node.getResponseBuffer(0);    
  } else {
    Serial.println("Fout bij lezen 42000");
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
  

int16_t readcurrentBatteryPowerAC() {
    uint32_t result;
    int16_t value = 0;
    delay(1);
    result = node.readHoldingRegisters(30006, 1);
    if (result == node.ku8MBSuccess) {
        value = (int16_t)node.getResponseBuffer(0);
    } else {
        Serial.println("Fout bij lezen BatteryPowerAC");
    } 
  return value;
}

int16_t readcurrentBatteryState() {
    uint32_t result;
    int16_t value = 0;
    delay(1);
    result = node.readHoldingRegisters(35100, 1);
    if (result == node.ku8MBSuccess) {
        value = (int16_t)node.getResponseBuffer(0);
    } else {
        Serial.println("Fout bij lezen currentBatteryState");
    } 
  return value;
}



// client configuration from esp32 sources
#include <WiFi.h>
#include <HTTPClient.h>

// json library for communication



unsigned long last_iungo_check = 0;

void setupWifi() {
    WiFi.begin(ssid, wachtwoord);
    Serial.print("Verbinden met WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nVerbonden!");
}

// Verander de returnwaarde naar int16_t als dat je doel is
int16_t ophalenIungoLoad(int16_t usage_oud) {
  unsigned long current_moment = millis();
  long delay_time = current_moment - last_iungo_check;
  
  if (delay_time < 6000) {
    delay(6000 - delay_time);
  }

  if (WiFi.status() == WL_CONNECTED) {
    int16_t usage = usage_oud; // Initialiseer met oude waarde
    HTTPClient http;
    http.begin(url_iungo);
    
    int i = 0;
    // Let op: 'usage == usage_oud' in de conditie zorgt dat hij doorgaat 
    // zolang er GEEN nieuwe data is, tot max 25 pogingen. Want na 6 seconden plus max 21 x 0,2 seconden is meer dan 10 seconden.
    do {
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
          String data = http.getString();
          StaticJsonDocument<2048> doc;
          DeserializationError error = deserializeJson(doc, data);
          
          if (!error) {
            JsonArray arr = doc["rv"]["objects"][0]["propsval"];
            for (JsonObject item : arr) {
              if (strcmp(item["id"], "usage") == 0) {
                // Directe conversie vanuit JSON naar int16_t
                usage = item["value"].as<int16_t>(); 
              }
            }
            
            if (usage != usage_oud) {
              last_iungo_check = millis();
            }
          }
        }
        i++;
        if (usage == usage_oud) delay(200); // Korte pauze tussen pogingen
    } while (usage == usage_oud && i < 21);
    
    http.end();
    return usage; // Geeft nu een int16_t terug
  }
  return usage_oud;
}



