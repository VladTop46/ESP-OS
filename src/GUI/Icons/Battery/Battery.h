#include <Arduino.h>

#ifndef BATTERY_H
#define BATTERY_H

class Battery {
public:
    Battery();
    void drawBatteryIcon(int x, int y, int batteryStage);

private:
    const uint16_t BatteryStageFull[11][21];
    const uint16_t BatteryStage90[11][21];
    const uint16_t BatteryStage75[11][21];
    const uint16_t BatteryStage50[11][21];
    const uint16_t BatteryStage25[11][21];
    const uint16_t BatteryStageLow[11][21];
};

#endif // BATTERY_H