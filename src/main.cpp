#include <Arduino.h>

#include "Kernel/Kernel.h"

Kernel kernel;

void setup() {
  kernel.init();
  kernel.kernel();
}

void loop() {

}