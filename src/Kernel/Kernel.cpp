#include <Arduino.h>

#include "Kernel.h"
#include "Hardware/InitHardware.h"
#include "Hardware/Display/ST7735/MainDisplay.h"
#include "CommandProcessor/CommandProcessor.h"
#include "RTC/RTC.h"

InitHardware hw;
extern MainDisplay& dInstance;
extern RTC& rtc;
CommandProcessor cp;

void Kernel::init() {
  Serial.begin(9600);
  Serial.println("ESPOS v0.1 bootup...");

  rtc.startClock();

  hw.init();
  boot();
}

void Kernel::boot() {
  // Очищаем буфер перед началом загрузки
  dInstance.clearTextBuffer();
  dInstance.setGUIMode(false);

  // Мигаем курсором в течение 10 секунд
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    dInstance.cursorBlink();
  }

  // Добавляем заголовочную строку
  dInstance.addTextToBuffer("Loading ESPOS kernel");
  Serial.println("Loading ESPOS kernel");
  dInstance.displayTextBuffer();

  delay(3000);

  // Процесс загрузки
  for (int i = 0; i < 10; ++i) {
    String bootText = "Loading: Step " + String(i + 1) + "/10";
    Serial.println(bootText);
    dInstance.addTextToBuffer(bootText);
    dInstance.displayTextBuffer();

    delay(100);
  }

  // Очищаем дисплей после окончания загрузки
  dInstance.getDisplay().fillScreen(ST77XX_BLACK);
  dInstance.clearTextBuffer();

  delay(500);
}

void Kernel::kernel() {
  dInstance.addTextToBuffer("ESPOS v0.1 loaded.");
  dInstance.addTextToBuffer("Awaiting command...");

  dInstance.displayTextBuffer();
  dInstance.setInputMode(true);

  while (true) {
    /*if (!dInstance.isGUIMode()) {

    }*/

    dInstance.updateCursor();
    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n');
      cp.process(input);
    }
  }

}
