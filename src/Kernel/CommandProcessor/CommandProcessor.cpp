#include "CommandProcessor.h"
#include <Arduino.h>
#include "../Hardware/Display/ST7735/MainDisplay.h"

extern MainDisplay& dInstance;

// Структура для хранения информации о команде
struct CommandInfo {
    const char* command;
    const char* description;
    void (*handler)();  // Указатель на функцию-обработчик команды
};

// Обработчики команд
void clearHandler() {
    dInstance.clearTextBuffer();
    dInstance.addTextToBuffer("Display cleared");
}

void rebootHandler() {
    dInstance.addTextToBuffer("Reboot in 5 secs...");
    delay(5000);
    ESP.restart();
}

void unameHandler() {
    dInstance.addTextToBuffer("uname -r:");
    dInstance.addTextToBuffer("ESPOS Kernel v0.1");
}

// Таблица команд
const CommandInfo commandTable[] = {
    {"clear", "Clear the display", clearHandler},
    {"reboot", "Reboot the system", rebootHandler},
    {"uname -r", "Display kernel version", unameHandler},
    // Добавьте здесь другие команды по мере необходимости
};

void CommandProcessor::process(const String &command) {
    dInstance.setInputMode(false);
    Serial.println("Executed command: " + command);

    // Поиск команды в таблице
    for (const auto& cmd : commandTable) {
        if (command == cmd.command) {
            // Вызов обработчика команды
            cmd.handler();
            dInstance.displayTextBuffer();
            dInstance.setInputMode(true);
            return;
        }
    }

    // Если команда не найдена
    dInstance.addTextToBuffer("Not found: " + command);
    Serial.println("Not found: " + command);
    dInstance.displayTextBuffer();
    dInstance.setInputMode(true);
}
