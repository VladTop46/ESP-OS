// CommandProcessor.h
#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <Arduino.h>

class CommandProcessor {
public:
    static void process(const String &command);
};

#endif
