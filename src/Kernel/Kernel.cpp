#include <Arduino.h>

#include "Kernel.h"
#include "Hardware/InitHardware.h"
#include "Hardware/Display/OLED/OLED.h"

InitHardware hw;
extern OLED& oledInstance;

void Kernel::init() {
  Serial.begin(9600);
  Serial.println("ESPOS v0.1 bootup...");

  hw.init();
  boot();
}

void Kernel::boot() {
  // Очищаем буфер перед началом загрузки
  oledInstance.clearTextBuffer();

  // Мигаем курсором в течение 10 секунд
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    oledInstance.cursorBlink();
  }

  // Добавляем заголовочную строку
  oledInstance.addTextToBuffer("Loading ESPOS kernel");
  Serial.println("Loading ESPOS kernel");
  oledInstance.displayTextBuffer();

  delay(3000);

  // Процесс загрузки
  for (int i = 0; i < 10; ++i) {
    String bootText = "Loading: Step " + String(i + 1) + "/10";
    Serial.println(bootText);
    oledInstance.addTextToBuffer(bootText);
    oledInstance.displayTextBuffer();

    delay(100);
  }

  // Очищаем дисплей после окончания загрузки
  oledInstance.getDisplay().clearDisplay();
  oledInstance.getDisplay().display();
  oledInstance.clearTextBuffer();

  delay(500);
}

void Kernel::kernel() {
  oledInstance.addTextToBuffer("ESPOS v0.1 loaded.");
  oledInstance.addTextToBuffer("Awaiting command...");

  oledInstance.displayTextBuffer();
  oledInstance.setInputMode(true);
}
