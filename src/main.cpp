#include "Arduino.h"
#include "wifi.hpp"
#include "telegram.hpp"

#define LED 4

TelegramBot bot;
Wifi wifi;
bool isWifi = true;

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    if(!wifi.init()){ 
      isWifi = false;
      wifi.host();
    }
    else bot.init();
}

void loop() {
  if(isWifi){
    telMessage buffer = bot.getUpdates();
    
    for (int i = 0; i < buffer.length; i++) {
      String cmd = buffer.messages[i].text;

      if(bot.validate(buffer.messages[i])) {
        if(cmd == "ON") {
          digitalWrite(LED, HIGH);
          bot.sendMessage(buffer.messages[i].chat_id, "Led turned ON");
        } else if(cmd == "OFF") {
          digitalWrite(LED, LOW);
          bot.sendMessage(buffer.messages[i].chat_id, "Led turned OFF");
        }
      }
    }
  }
  delay(2000);  
}
