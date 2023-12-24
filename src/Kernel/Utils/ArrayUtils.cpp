#include "ArrayUtils.h"

std::array<int, 2> ArrayUtils::parseTimeArgument(const String& timeString) {
    std::array<int, 2> result = {0, 0};

    int colonIndex = timeString.indexOf(':');

    if (colonIndex != -1) {
        result[0] = timeString.substring(0, colonIndex).toInt();
        result[1] = timeString.substring(colonIndex + 1).toInt();
    }

    return result;
}