#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h> // Подключаем библиотеку для работы с ST7735

#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

class MainDisplay {
public:
    static MainDisplay& getInstance(); // Метод для получения единственного экземпляра класса

    void init();
    void clearTextBuffer();
    void addTextToBuffer(const String &text);
    void displayTextBuffer();
    void cursorBlink();
    void setInputMode(bool mode);
    void updateCursor();

    // Новые методы для графической оболочки
    void drawClock();  // Отрисовка часов
    void drawModuleIcons();  // Отрисовка иконок модулей
    void drawBatteryIcon();  // Отрисовка иконки заряда батареи
    void drawSeparators();  // Отрисовка разделителей

    // Новый метод для начала вывода графической оболочки
    void startDrawingShell();

    void setGUIMode(bool mode);
    bool isGUIMode() const;

    Adafruit_ST7735& getDisplay(); // Изменено на Adafruit_ST7735

    // Удаление конструкторов и операторов присваивания для предотвращения создания копий
    MainDisplay(const MainDisplay&) = delete;
    MainDisplay& operator=(const MainDisplay&) = delete;

private:
    // Приватный конструктор для предотвращения создания экземпляров вне класса
    MainDisplay();

    static const int numLines = 16;
    String textBuffer[numLines - 1];

    String cursorLine;

    Adafruit_ST7735 display; // Изменено на Adafruit_ST7735
    bool inputMode;
    bool GUIMode;
};

#endif
