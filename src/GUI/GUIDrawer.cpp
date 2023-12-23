#include "GUIDrawer.h"
#include "../Kernel/Hardware/Display/ST7735/MainDisplay.h"

#define CLOCK_X 4
#define CLOCK_Y 3
#define CLOCK_WIDTH 3
#define CLOCK_HEIGHT 8

#define MODULE_ICON_WIDTH 8
#define MODULE_ICON_HEIGHT 8
#define MODULE_ICON_MARGIN 2
#define FIRST_MODULE_ICON_X 44
#define FIRST_MODULE_ICON_Y 3

#define BATTERY_ICON_X 127
#define BATTERY_ICON_Y 2
#define BATTERY_ICON_WIDTH 1
#define BATTERY_ICON_HEIGHT 10

#define MAIN_AREA_X 1
#define MAIN_AREA_Y 17
#define MAIN_AREA_WIDTH 158
#define MAIN_AREA_HEIGHT 88

#define SEPARATOR_Y1 15
#define SEPARATOR_Y2 106

extern MainDisplay& dInstance;

void GUIDrawer::drawModuleIcons() {
    // Отрисовка иконок модулей
    for (int i = 0; i < 5; ++i) {
        int iconX = FIRST_MODULE_ICON_X + i * (MODULE_ICON_WIDTH + MODULE_ICON_MARGIN);
        int iconY = FIRST_MODULE_ICON_Y;
        
        dInstance.getDisplay().fillRect(iconX, iconY, MODULE_ICON_WIDTH, MODULE_ICON_HEIGHT, ST7735_BLUE);
    }
}

void GUIDrawer::drawBatteryIcon() {
    // Отрисовка иконки заряда батареи
    dInstance.getDisplay().fillRect(BATTERY_ICON_X, BATTERY_ICON_Y, BATTERY_ICON_WIDTH, BATTERY_ICON_HEIGHT, ST7735_BLUE);
}

void GUIDrawer::drawSeparators() {
    // Отрисовка разделительных линий
    dInstance.getDisplay().drawFastHLine(0, SEPARATOR_Y1, 160, ST7735_WHITE);
    dInstance.getDisplay().drawFastHLine(0, SEPARATOR_Y2, 160, ST7735_WHITE);
}

// Новый метод для начала вывода графической оболочки
void GUIDrawer::startDrawingShell() {
    dInstance.getDisplay().fillScreen(ST7735_BLACK);
    drawModuleIcons();
    drawBatteryIcon();
    drawSeparators();
    
    // Отрисовка рамки основной области
    dInstance.getDisplay().drawRect(MAIN_AREA_X, MAIN_AREA_Y, MAIN_AREA_WIDTH, MAIN_AREA_HEIGHT, ST7735_WHITE);
    
    // Добавьте здесь код для отрисовки других динамических областей при необходимости
}