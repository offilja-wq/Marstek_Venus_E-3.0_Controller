#include <Arduino.h>

#include "config.h"
#include "iungo.h"
#include "personal.h"

int16_t oldpowerReading;
unsigned long lastIungoCheck;

void iungoBegin()
{
    WiFi.begin(ssid, password);
    while (!wifiConnected()) {
      delay(500);
    }
}

bool wifiConnected()
{
    return (WiFi.status() == WL_CONNECTED);
}

int16_t getIungoPower()
{
    unsigned long now = millis();
    
        delay(((now - lastIungoCheck) < 6000) ? (6000 - (now - lastIungoCheck)) : 0);

    if (!wifiConnected())
        return oldpowerReading;

        int16_t powerReading = oldpowerReading; // Initialiseer met oude waarde
        HTTPClient http;
        http.begin(url_iungo);

        // Let op: 'powerReading == oldpowerReading\' in de conditie zorgt dat hij doorgaat 
        // zolang er GEEN nieuwe data is, tot max 25 pogingen. Want na 6 seconden plus max 21 x 0,2 seconden is meer dan 10 seconden.
        for (int i = 0; ((powerReading == oldpowerReading) && (i <= 20)); i++)
        {
            int httpCode = http.GET();

            if ((httpCode == HTTP_CODE_OK) &&(powerReading != oldpowerReading))
            {
                String data = http.getString();
                StaticJsonDocument<2048> doc;          
                DeserializationError error = deserializeJson(doc, data);
            
                if (!error)
                {
                    JsonArray arr = doc["rv"]["objects"][0]["propsval"];
                    
                    for (JsonObject item : arr) {
                        if ((strcmp(item["id"], "powerReading") == 0) && (powerReading != oldpowerReading)) {
                            // Directe conversie vanuit JSON naar int16_t
                            powerReading = item["value"].as<int16_t>();
                            lastIungoCheck = now;
                        }
                    }
                }
            }
            else
            {
                delay(200);
            }
        }
        
    http.end();
    return powerReading; // Geeft nu een int16_t terug
}