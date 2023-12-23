#include <Arduino.h>

#ifndef GUIDRAWER_H
#define GUIDRAWER_H

class GUIDrawer {
public:

    void drawClock();  // Отрисовка часов
    void drawModuleIcons();  // Отрисовка иконок модулей
    void drawBatteryIcon();  // Отрисовка иконки заряда батареи
    void drawSeparators();  // Отрисовка разделителей

    void startDrawingShell();

private:

};

#endif
