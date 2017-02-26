//remember to add the library
// lib_deps =
//      WiFiConnector

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiConnector.h>
#include <ESP8266WebServer.h>

#ifndef WIFI_SSID
  #define WIFI_SSID      "ssid"
  #define WIFI_PASSPHRASE "password"
#endif

WiFiConnector wifi(WIFI_SSID, WIFI_PASSPHRASE);
ESP8266WebServer server(80);

void init_hardware()
{
        Serial.begin(115200);
        pinMode(LED_BUILTIN, OUTPUT);
        delay(10);
        Serial.println();
        Serial.println("BEGIN");
}

void init_webserver() {
        server.on ( "/", []() {
                bool state = digitalRead(LED_BUILTIN);
                digitalWrite(LED_BUILTIN, !state);
                char buff[100];
                String ms = String(millis());
                sprintf(buff, "{\"help\":\"refresh page to toggle led\",\"millis\": %s }", ms.c_str());
                server.send ( 200, "text/plain", buff );
        });

        server.on ( "/millis", []() {
                char buff[100];
                String ms = String(millis());
                sprintf(buff, "{\"millis\": %s }", ms.c_str());
                server.send ( 200, "text/plain", buff );
        });
}

void init_wifi() {
        wifi.init();
        wifi.on_connecting([&](const void* message)
        {
                Serial.print(".");
                delay(500);
        });

        wifi.on_connected([&](const void* message)
        {
                // Print the IP address
                Serial.print("WIFI CONNECTED => ");
                Serial.println(WiFi.localIP());

                init_webserver();
                server.begin();
                Serial.println("SERVER Started. Refresh page to toggle led.");
        });

        wifi.on_disconnected([&](const void* message) {
                server.close();
        });
}

void setup()
{
        init_hardware();
        init_wifi();
        wifi.connect();
}

void loop()
{
        wifi.loop();
        server.handleClient();
}
