#include <Arduino.h>

#ifndef KERNEL_H
#define KERNEL_H

class Kernel {
public:
  void init();
  void boot();
  void kernel();
private:
  // Any private member variables or functions needed
};

#endif
