#include "Arduino.h"
#include "wifi.hpp"
#include "telegram.hpp"
#include "ir.hpp"

TelegramBot bot;
Wifi wifi;
IR ir;
bool isWifi = true;

void setup() {
    Serial.begin(115200);

    delay(150);

    ir.init();

    if (!wifi.init()){ 
      isWifi = false;
      wifi.host();
    } else bot.init();
}

void loop() {
  if(isWifi){
    telMessage buffer = bot.getUpdates();
    
    for (int i = 0; i < buffer.length; i++) {
      String cmd = buffer.messages[i].text;
      cmd.toLowerCase(); 
      if(bot.validate(buffer.messages[i])) {
        if(cmd.indexOf("samsung") != -1) {
          ir.send(IrCmd::SAMSUNG_TV_POWER);
          bot.sendMessage(buffer.messages[i].chat_id, "Led turned ON");
        } else if(cmd == "lg") {
          ir.send(IrCmd::LG_TV_POWER);
          bot.sendMessage(buffer.messages[i].chat_id, "Led turned OFF");
        }
      }
    }
  }
  delay(2000);  
}