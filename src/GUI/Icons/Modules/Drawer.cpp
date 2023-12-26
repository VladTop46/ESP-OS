#include "Drawer.h"
#include "../../../Kernel/Hardware/Display/ST7735/MainDisplay.h"

extern MainDisplay& dInstance;

void Drawer::drawIcon(int x, int y, const uint16_t icon[9][9]) {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      uint16_t color = icon[i][j];
      dInstance.getDisplay().drawPixel(x + j, y + i, color);
    }
  }
}