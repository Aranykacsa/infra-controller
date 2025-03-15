#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <Arduino.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <vector>
#include <string>

#define TOKEN "7800435271:AAFaBm7b-QZIe1iDEkWKEnyNRtr2rkQ8v6M"
#define CHAT_ID "6418346641"

struct telMessage {
    int length;
    telegramMessage* messages;
};

class TelegramBot {
    public:
        TelegramBot() : bot(TOKEN, client) {}
        void init();
        telMessage getUpdates();
        bool validate(telegramMessage message);
        void sendMessage(const String chatId, const String message);
    private:
        WiFiClientSecure client;
        UniversalTelegramBot bot;        
        std::vector<String> users{"6418346641"};    
    };

#endif