#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>
#include <WebServer.h>

#define MY_SSID "Wi-Fi"
#define MY_PASS "wwhctm989"
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
};

#endif