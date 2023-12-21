#include "InitHardware.h"
#include "Display/OLED/OLED.h"

extern OLED& oledInstance;

void InitHardware::init() {
    oledInstance.init();
}