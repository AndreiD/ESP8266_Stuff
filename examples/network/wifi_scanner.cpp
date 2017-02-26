#include <Arduino.h>
#include <SSD1306.h>
#include <robotofont.h>
#include <ESP8266WiFi.h>

boolean ledState = false;



SSD1306 display(0x3c, D5, D6);

void setup() {
        Serial.begin(115200);
        display.init();
        display.displayOn();
        display.flipScreenVertically();
        display.setFont(Roboto_Medium_24);
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
        display.drawString(0, 0, "CO2 2234\nVOC 1234");
        display.display();
        Serial.println("~~~ working ~~~");
        blink();

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
