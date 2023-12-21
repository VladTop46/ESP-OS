#include "InitHardware.h"
#include "Display/ST7735/MainDisplay.h"

extern MainDisplay& dInstance;

void InitHardware::init() {
    dInstance.init();
}