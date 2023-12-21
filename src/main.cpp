#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>

#include "Kernel/Kernel.h"
#include "Kernel/Hardware/Display/ST7735/MainDisplay.h"
#include "Kernel/CommandProcessor/CommandProcessor.h"

extern MainDisplay& dInstance;
Kernel kernel;
CommandProcessor cp;


void setup() {
  kernel.init();
  kernel.kernel();
}

void loop() {
  dInstance.updateCursor();
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    cp.process(input);
  }
}