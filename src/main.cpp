#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>

#include "Kernel/Kernel.h"
#include "Kernel/CommandProcessor/CommandProcessor.h"
#include "Kernel/Hardware/Display/OLED/OLED.h"

Kernel kernel;
CommandProcessor cp;
extern OLED& oledInstance;

void setup() {
  kernel.init();
  kernel.kernel();
}

void loop() {
  oledInstance.updateCursor();
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    cp.process(input);
  }
}