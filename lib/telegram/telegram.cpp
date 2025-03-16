#include "telegram.hpp"
#include "Arduino.h"
#include <iostream>

void TelegramBot::init() {
    bot = new UniversalTelegramBot(TOKEN, client);  // Initialize in constructor
    client.setInsecure(); 
    bot->sendMessage(CHAT_ID, "ESP32 connected!", "");
}

telMessage TelegramBot::getUpdates() {
    int messageCount = bot->getUpdates(bot->last_message_received + 1);
    
    telMessage buffer {
        .length = messageCount,
        .messages = bot->messages
    };
    return buffer;
}

void TelegramBot::sendMessage(const String chatId, const String message) {
    bot->sendMessage(chatId, message, "");
}

bool TelegramBot::validate(telegramMessage message) { //add user
    for (int i = 0; i < sizeof(users); i++) {
        if (users[i] == message.from_id) {
            return true;
        }
    }

    return false;
}