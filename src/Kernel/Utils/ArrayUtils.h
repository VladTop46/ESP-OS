// ArrayUtils.h
#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <Arduino.h>

#include <array>

class ArrayUtils {
public:
    std::array<int, 2> parseTimeArgument(const String& timeString);

private:

};

#endif
