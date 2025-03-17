#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

struct Pref {
    String ssid;
    String pass;
};

//#define MY_SSID "Wi-Fi"
#define MY_SSID "Affinity Workshop"
//#define MY_PASS "wwhctm989"
#define MY_PASS "AW37696009"
#define HOST_SSID "CONTROLLER_WIFI"
#define HOST_PASS "CONTROLLER_WIFI"

class Wifi {
    public:
        Wifi(): server(80) { }  
        bool init();
        void host();    
    private:
        WebServer server;
        void handleCmd();
        Pref getWifi();

        Preferences wifiPreferences;
        
};

#endif