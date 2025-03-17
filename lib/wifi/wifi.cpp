#include "wifi.hpp"
#include "Arduino.h"
#include <WiFi.h>

bool Wifi::init() {
    Pref buffer = this->getWifi();
    WiFi.begin(buffer.ssid, buffer.pass);

    int stopper = 0;

    while (WiFi.status() != WL_CONNECTED && stopper < 60) {  
        delay(1000);
        stopper++;
    }

    if (WiFi.status() != WL_CONNECTED) {  
        Serial.println("WiFi not found");
        return false;
    } else {
        Serial.println("Connected to WiFi");
        return true;
    }
}

void Wifi::handleCmd() {
    String response;

    if(server.hasArg("ssid")) {
        String ssid = server.arg("ssid");
        response = "Received SSID: " + ssid;
        wifiPreferences.putString("ssid", ssid);
    } else if (server.hasArg("password")) {
        String password = server.arg("password");
        response = "Received password: " + password;
        wifiPreferences.putString("pass", password);
    } else if (server.hasArg("restart")) {
        wifiPreferences.end();
        delay(1000);
        ESP.restart();
    }
    else {
        response = "No option was found";
    }
    server.send(200, "text/plain", response);
}

void Wifi::host() {
    WiFi.softAP(HOST_SSID, HOST_PASS);

    Serial.println("AP Started");
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());

    server.on("/set", [this]() { this->handleCmd(); }); 
    server.begin();

    while(1) {
        server.handleClient();
    }
}

Pref Wifi::getWifi() {
    Pref buffer;

    wifiPreferences.begin("wifi", false);

    if(wifiPreferences.isKey("ssid")) {
        buffer.ssid = wifiPreferences.getString("ssid");
    } else {
        buffer.ssid = "Fallback";
    }

    if (wifiPreferences.isKey("pass")) {
        buffer.pass = wifiPreferences.getString("pass");
    } else {
        buffer.pass = "Fallback";
    }

    return buffer;
}
