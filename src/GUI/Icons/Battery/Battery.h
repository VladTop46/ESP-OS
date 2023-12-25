#include <Arduino.h>

#ifndef BATTERY_H
#define BATTERY_H

class Battery {
public:
    Battery();  // Добавлен конструктор
    void drawBatteryIcon(int x, int y, int batteryStage);

private:
    const uint16_t BatteryStageFull[11][21];  // Массив для иконки заряда АКБ
};

#endif // BATTERY_H