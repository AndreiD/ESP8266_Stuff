#include <Arduino.h>
#include <ESP8266WiFi.h>

boolean ledState = false;




void setup() {
        Serial.begin(115200);
        pinMode(LED_BUILTIN, OUTPUT);
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        delay(100);
        Serial.println("Setup done");

}

void blink(){
        ledState ? ledState=false : ledState=true;
        digitalWrite(LED_BUILTIN,ledState);
}


void loop() {
        delay(1000);
        Serial.println("scan start");

        // WiFi.scanNetworks will return the number of networks found
        int n = WiFi.scanNetworks();
        Serial.println("scan done");
        if (n == 0)
                Serial.println("no networks found");
        else
        {
                Serial.print(n);
                Serial.println(" networks found");
                for (int i = 0; i < n; ++i)
                {
                        // Print SSID and RSSI for each network found
                        Serial.print(i + 1);
                        Serial.print(": ");
                        Serial.print(WiFi.SSID(i));
                        Serial.print(" (");
                        Serial.print(WiFi.RSSI(i));
                        Serial.print(")");
                        Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
                        delay(10);
                }
        }
        Serial.println("");
        delay(4000);

}
