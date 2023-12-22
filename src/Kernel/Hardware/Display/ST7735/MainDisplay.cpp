#include "MainDisplay.h"

#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 2

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

MainDisplay& dInstance = MainDisplay::getInstance();

// Инициализация статического члена класса
MainDisplay& MainDisplay::getInstance() {
    static MainDisplay instance;
    return instance;
}

// Приватный конструктор для создания экземпляра класса
MainDisplay::MainDisplay() : display(TFT_CS, TFT_DC, TFT_RST) {
    display.initR(INITR_BLACKTAB);
}

void MainDisplay::init() {
    dInstance.getDisplay().setRotation(1);
    dInstance.getDisplay().fillScreen(ST7735_BLACK);
    dInstance.getDisplay().setTextColor(ST7735_WHITE);
}

void MainDisplay::clearTextBuffer() {
    for (int i = 0; i < numLines; ++i) {
        textBuffer[i] = "";
    }
}

void MainDisplay::addTextToBuffer(const String &text) {
    // Сдвигаем строки вверх
    for (int i = 0; i < numLines - 2; ++i) {
        textBuffer[i] = textBuffer[i + 1];
    }

    // Добавляем новую строку внизу
    textBuffer[numLines - 2] = text;
}

void MainDisplay::displayTextBuffer() {
    if (!GUIMode) {
        // Очищаем дисплей перед выводом нового содержимого
        display.fillScreen(ST7735_BLACK);
        display.setTextSize(1);
        display.setCursor(0, 0);  // Начинаем вывод с верхней части дисплея

        // Выводим строки из буфера на дисплей
        for (int i = 0; i < numLines; ++i) {
            display.println(textBuffer[i]);
        }
    }
}

void MainDisplay::cursorBlink() {
    static bool cursorVisible = true;
    static unsigned long lastBlinkTime = 0;
    const unsigned long blinkInterval = 200;

    if (millis() - lastBlinkTime >= blinkInterval) {
        lastBlinkTime = millis();

        cursorVisible = !cursorVisible;

        display.fillScreen(ST7735_BLACK);

        if (cursorVisible) {
            display.drawPixel(10, 10, ST7735_WHITE);
            display.drawPixel(11, 10, ST7735_WHITE);
            display.drawPixel(12, 10, ST7735_WHITE);
            display.drawPixel(13, 10, ST7735_WHITE);
        }
    }
}

void MainDisplay::setInputMode(bool mode) {
    inputMode = mode;
}

void MainDisplay::updateCursor() {
    if (inputMode) {
        textBuffer[numLines - 1] = "esp:/$ _";
        displayTextBuffer();
        delay(500);

        textBuffer[numLines - 1] = "esp:/$ ";
        displayTextBuffer();
        delay(500);
    }
}

Adafruit_ST7735& MainDisplay::getDisplay() {
    return display;
}

// Добавление графической оболочки для дисплея ST7735

void MainDisplay::drawModuleIcons() {
    // Отрисовка иконок модулей
    for (int i = 0; i < 3; ++i) {
        int iconX = FIRST_MODULE_ICON_X + i * (MODULE_ICON_WIDTH + MODULE_ICON_MARGIN);
        int iconY = FIRST_MODULE_ICON_Y;
        
        dInstance.getDisplay().fillRect(iconX, iconY, MODULE_ICON_WIDTH, MODULE_ICON_HEIGHT, ST7735_BLUE);
    }
}

void MainDisplay::drawBatteryIcon() {
    // Отрисовка иконки заряда батареи
    dInstance.getDisplay().fillRect(BATTERY_ICON_X, BATTERY_ICON_Y, BATTERY_ICON_WIDTH, BATTERY_ICON_HEIGHT, ST7735_BLUE);
}

void MainDisplay::drawSeparators() {
    // Отрисовка разделительных линий
    dInstance.getDisplay().drawFastHLine(0, SEPARATOR_Y1, 160, ST7735_WHITE);
    dInstance.getDisplay().drawFastHLine(0, SEPARATOR_Y2, 160, ST7735_WHITE);
}

// Новый метод для начала вывода графической оболочки
void MainDisplay::startDrawingShell() {
    dInstance.getDisplay().fillScreen(ST7735_BLACK);
    drawModuleIcons();
    drawBatteryIcon();
    drawSeparators();
    
    // Отрисовка рамки основной области
    dInstance.getDisplay().drawRect(MAIN_AREA_X, MAIN_AREA_Y, MAIN_AREA_WIDTH, MAIN_AREA_HEIGHT, ST7735_WHITE);
    
    // Добавьте здесь код для отрисовки других динамических областей при необходимости
}

void MainDisplay::setGUIMode(bool mode) {
    GUIMode = mode;
}

bool MainDisplay::isGUIMode() const {
    return GUIMode;
}