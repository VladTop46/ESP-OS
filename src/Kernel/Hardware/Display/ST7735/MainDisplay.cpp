#include "MainDisplay.h"

#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 2

#define MAIN_AREA_HEIGHT 87
#define MAIN_AREA_WIDTH 156

#define MAIN_AREA_X1 2
#define MAIN_AREA_Y1 18

#define MAIN_AREA_X2 157
#define MAIN_AREA_Y2 104

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
    dInstance.displayTextBuffer();
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

void MainDisplay::setGUIMode(bool mode) {
    GUIMode = mode;
}

bool MainDisplay::isGUIMode() const {
    return GUIMode;
}


