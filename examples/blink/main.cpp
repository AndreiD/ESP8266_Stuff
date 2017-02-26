#include <Arduino.h>

boolean ledState = false;

void setup() {
        Serial.begin(115200);
        pinMode(LED_BUILTIN, OUTPUT);
        Serial.println("Setup done");

}

void blink(){
        ledState ? ledState=false : ledState=true;
        digitalWrite(LED_BUILTIN,ledState);
}


void loop() {
        Serial.println("~~~ working ~~~");
        blink();
        delay(500);
}
