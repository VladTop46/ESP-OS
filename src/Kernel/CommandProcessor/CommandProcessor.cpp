#include "CommandProcessor.h"
#include <Arduino.h>
#include "../Hardware/Display/ST7735/MainDisplay.h"
#include "../../GUI/GUIDrawer.h"
#include "../RTC/RTC.h"
#include "../Utils/ArrayUtils.h"

#include <vector>

extern MainDisplay& dInstance;
extern RTC& rtc;
ArrayUtils arUtils;
GUIDrawer gdraw;

// Структура для хранения информации о команде
struct CommandInfo {
    const char* command;
    const char* description;
    void (*handler)(const std::vector<String>&);  // Указатель на функцию-обработчик команды с аргументами
};

// Обработчики команд
void clearHandler(const std::vector<String>& arguments) {
    // Для команды clear аргументы не обрабатываются
    dInstance.clearTextBuffer();
    dInstance.addTextToBuffer("Display cleared");
    dInstance.displayTextBuffer();
}

void rebootHandler(const std::vector<String>& arguments) {
    // Для команды reboot аргументы не обрабатываются
    dInstance.addTextToBuffer("Reboot in 5 secs...");
    dInstance.displayTextBuffer();
    delay(5000);
    ESP.restart();
}

void unameHandler(const std::vector<String>& arguments) {
    // Обработка аргументов для команды uname
    if (arguments.size() == 1 && arguments[0] == "-r") {
        dInstance.addTextToBuffer("uname -r:");
        dInstance.addTextToBuffer("ESPOS Kernel v0.1");
        dInstance.displayTextBuffer();
    } else {
        dInstance.addTextToBuffer("Invalid arguments");
        dInstance.displayTextBuffer();
    }
}

void GUIHandler(const std::vector<String>& arguments) {
    if (arguments.size() == 1 && arguments[0] == "-v") {
        dInstance.addTextToBuffer("gui -v:");
        dInstance.addTextToBuffer("ESP OS GUI, Version 0.1");
        dInstance.displayTextBuffer();
    } else if (arguments.size() == 1 && arguments[0] == "-start") {
        dInstance.addTextToBuffer("gui -start:");
        dInstance.addTextToBuffer("Launching ESPOS GUI...:");
        dInstance.displayTextBuffer();
        dInstance.setGUIMode(true);
        delay(500);
        gdraw.startDrawingShell();
        delay(1000);
    } else {
        dInstance.addTextToBuffer("gui:");
        dInstance.addTextToBuffer("No arguments. Use -start");
        dInstance.displayTextBuffer();
    }
}

void timeHandler(const std::vector<String>& arguments) {
    if (arguments.size() == 2 && arguments[0] == "-s") {
        std::array<int, 2> timeArray = arUtils.parseTimeArgument(arguments[1]);

        int hours = timeArray[0];
        int minutes = timeArray[1];
        rtc.setTime(hours, minutes);

        dInstance.addTextToBuffer("time -s " + arguments[1]);
        dInstance.addTextToBuffer("Time set.");
        dInstance.displayTextBuffer();
    } else {
        dInstance.addTextToBuffer("time:");
        dInstance.addTextToBuffer("Use time -s HH:MM");
        dInstance.displayTextBuffer();
    }
}

// Таблица команд
const CommandInfo commandTable[] = {
    {"clear", "Clear the display", clearHandler},
    {"reboot", "Reboot the system", rebootHandler},
    {"uname", "Display kernel version", unameHandler},
    {"gui", "Starting GUI", GUIHandler},
    {"time", "Time operations", timeHandler},
    // Добавьте здесь другие команды по мере необходимости
};

void CommandProcessor::process(const String &command) {
    dInstance.setInputMode(false);
    Serial.println("Executed command: " + command);

    // Разделяем команду и аргументы
    int spaceIndex = command.indexOf(' ');
    String cmd, argumentsString;

    if (spaceIndex != -1) {
        cmd = command.substring(0, spaceIndex);
        argumentsString = command.substring(spaceIndex + 1);
    } else {
        cmd = command;
    }

    // Преобразуем строку аргументов в массив аргументов
    std::vector<String> arguments;
    int currentPos = 0;
    int nextSpaceIndex = argumentsString.indexOf(' ', currentPos);

    while (nextSpaceIndex != -1) {
        arguments.push_back(argumentsString.substring(currentPos, nextSpaceIndex));
        currentPos = nextSpaceIndex + 1;
        nextSpaceIndex = argumentsString.indexOf(' ', currentPos);
    }

    arguments.push_back(argumentsString.substring(currentPos));

    // Поиск команды в таблице
    for (const auto& cmdInfo : commandTable) {
        if (cmd == cmdInfo.command) {
            // Вызов обработчика команды с аргументами
            cmdInfo.handler(arguments);
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