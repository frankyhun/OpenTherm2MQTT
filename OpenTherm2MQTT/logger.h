#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

// Function declarations for logging
void logInfo(const String& message);
void logError(const String& message);
void logTarget(bool heatingOn, bool hotWaterOn, bool enableCooling, float heatingSetpoint);

#endif
