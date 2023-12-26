#include "GUIDrawer.h"
#include "../Kernel/Hardware/Display/ST7735/MainDisplay.h"
#include "../Kernel/RTC/RTC.h"

#include "Icons/Battery/Battery.h"


#include <iostream>
#include <thread>
#include <chrono>

#define CLOCK_X 4
#define CLOCK_Y 4
#define CLOCK_WIDTH 4
#define CLOCK_HEIGHT 8

#define MODULE_ICON_WIDTH 8
#define MODULE_ICON_HEIGHT 8
#define MODULE_ICON_MARGIN 2
#define FIRST_MODULE_ICON_X 44
#define FIRST_MODULE_ICON_Y 3

#define BATTERY_ICON_X 137
#define BATTERY_ICON_Y 2

#define MAIN_AREA_X 1
#define MAIN_AREA_Y 17
#define MAIN_AREA_WIDTH 158
#define MAIN_AREA_HEIGHT 88

#define SEPARATOR_Y1 15
#define SEPARATOR_Y2 106

extern MainDisplay& dInstance;
extern RTC& rtc;
Battery battery;

void drawClockDots() {
    while (true) {
        std::array<int, 4> time = rtc.getTime();

        dInstance.getDisplay().drawChar(CLOCK_X, CLOCK_Y, std::to_string(time[0])[0], 0xFFFF, 0x0000, 1, 1);
        dInstance.getDisplay().drawChar(CLOCK_X + ((CLOCK_X * 1) + 2), CLOCK_Y, std::to_string(time[1])[0], 0xFFFF, 0x0000, 1, 1);
        dInstance.getDisplay().drawChar(CLOCK_X + ((CLOCK_X * 2) + 8), CLOCK_Y, std::to_string(time[2])[0], 0xFFFF, 0x0000, 1, 1);
        dInstance.getDisplay().drawChar(CLOCK_X + ((CLOCK_X * 3) + 10), CLOCK_Y, std::to_string(time[3])[0], 0xFFFF, 0x0000, 1, 1);

        dInstance.getDisplay().fillRect(17, 5, 2, 2, ST7735_WHITE);
        dInstance.getDisplay().fillRect(17, 8, 2, 2, ST7735_WHITE);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        dInstance.getDisplay().fillRect(17, 5, 2, 2, ST7735_BLACK);
        dInstance.getDisplay().fillRect(17, 8, 2, 2, ST7735_BLACK);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void GUIDrawer::drawClock() {
    std::thread clockDots(drawClockDots);
    clockDots.detach();
}

void GUIDrawer::drawModuleIcons() {
    // Отрисовка иконок модулей
    for (int i = 0; i < 5; ++i) {
        int iconX = FIRST_MODULE_ICON_X + i * (MODULE_ICON_WIDTH + MODULE_ICON_MARGIN);
        int iconY = FIRST_MODULE_ICON_Y;
        
        dInstance.getDisplay().fillRect(iconX, iconY, MODULE_ICON_WIDTH, MODULE_ICON_HEIGHT, ST7735_BLUE);
    }
}

// ONLY FOR TEST

void batteryDrawer() {
    while (true) {
        battery.drawBatteryIcon(BATTERY_ICON_X, BATTERY_ICON_Y, 100);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        battery.drawBatteryIcon(BATTERY_ICON_X, BATTERY_ICON_Y, 80);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        battery.drawBatteryIcon(BATTERY_ICON_X, BATTERY_ICON_Y, 75);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        battery.drawBatteryIcon(BATTERY_ICON_X, BATTERY_ICON_Y, 50);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        battery.drawBatteryIcon(BATTERY_ICON_X, BATTERY_ICON_Y, 25);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        battery.drawBatteryIcon(BATTERY_ICON_X, BATTERY_ICON_Y, 10);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// ONLY FOR TEST

void GUIDrawer::drawBatteryIcon() {
    // Отрисовка иконки заряда батареи
    std::thread batteryDraw(batteryDrawer);
    batteryDraw.detach();
}

void GUIDrawer::drawSeparators() {
    // Отрисовка разделительных линий
    dInstance.getDisplay().drawFastHLine(0, SEPARATOR_Y1, 160, ST7735_WHITE);
    dInstance.getDisplay().drawFastHLine(0, SEPARATOR_Y2, 160, ST7735_WHITE);
}

// Новый метод для начала вывода графической оболочки
void GUIDrawer::startDrawingShell() {
    dInstance.getDisplay().fillScreen(ST7735_BLACK);
    drawClock();
    drawModuleIcons();
    drawBatteryIcon();
    drawSeparators();
    
    // Отрисовка рамки основной области
    dInstance.getDisplay().drawRect(MAIN_AREA_X, MAIN_AREA_Y, MAIN_AREA_WIDTH, MAIN_AREA_HEIGHT, ST7735_WHITE);
    
    // Добавьте здесь код для отрисовки других динамических областей при необходимости
}