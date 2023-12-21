#include "CommandProcessor.h"
#include <Arduino.h>
#include "../Hardware/Display/OLED/OLED.h"

extern OLED& oledInstance;

// Структура для хранения информации о команде
struct CommandInfo {
    const char* command;
    const char* description;
    void (*handler)();  // Указатель на функцию-обработчик команды
};

// Обработчики команд
void clearHandler() {
    oledInstance.clearTextBuffer();
    oledInstance.addTextToBuffer("Display cleared");
}

void rebootHandler() {
    oledInstance.addTextToBuffer("Reboot in 5 secs...");
    delay(5000);
    ESP.restart();
}

void unameHandler() {
    oledInstance.addTextToBuffer("uname -r:");
    oledInstance.addTextToBuffer("ESPOS Kernel v0.1");
}

// Таблица команд
const CommandInfo commandTable[] = {
    {"clear", "Clear the display", clearHandler},
    {"reboot", "Reboot the system", rebootHandler},
    {"uname -r", "Display kernel version", unameHandler},
    // Добавьте здесь другие команды по мере необходимости
};

void CommandProcessor::process(const String &command) {
    oledInstance.setInputMode(false);
    Serial.println("Executed command: " + command);

    // Поиск команды в таблице
    for (const auto& cmd : commandTable) {
        if (command == cmd.command) {
            // Вызов обработчика команды
            cmd.handler();
            oledInstance.displayTextBuffer();
            oledInstance.setInputMode(true);
            return;
        }
    }

    // Если команда не найдена
    oledInstance.addTextToBuffer("Not found: " + command);
    Serial.println("Not found: " + command);
    oledInstance.displayTextBuffer();
    oledInstance.setInputMode(true);
}
