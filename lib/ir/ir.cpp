#include "ir.hpp"

void IR::init() {
    irLed.begin();
}

void IR::send(IrCmd cmd) {
    irLed.sendNEC(cmd, 32);  
}