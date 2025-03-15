#include "wifi.hpp"
#include "Arduino.h"
#include <WiFi.h>

void Wifi::init() {
    WiFi.begin(MY_SSID, MY_PASS);

    int stopper = 0;
    
    while (WiFi.status() != WL_CONNECTED) {
        if(stopper == 100) {
            break;
        }

        stopper++;
        delay(1000);
    }

    if (stopper == 100) Serial.println("Wifi not found"); // setup wifi
    else Serial.println("Connected to WiFi");
}