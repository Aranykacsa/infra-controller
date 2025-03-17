#ifndef IR_H
#define IR_H

#include <IRremoteESP8266.h>    
#include <IRsend.h>

enum IrCmd {
    LG_TV_POWER = 0x20DF10EF,
    SAMSUNG_TV_POWER = 0xE0E06798
};

class IR {
    public:
        IR() : irLed(IR_LED_PIN) {} 
        void init();
        void send(IrCmd cmd);
    private:
        IRsend irLed;
        static constexpr int IR_LED_PIN = 16;
};

#endif