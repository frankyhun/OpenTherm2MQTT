#include "logger.h"
#include <PubSubClient.h>
#include "config.h"

// Declare externally defined client in main.ino
extern PubSubClient client;

// Log info messages to Serial and MQTT
void logInfo(const String& message) {
  Serial.println("INFO: " + message);
  client.publish(logInfoTopic, message.c_str(), false);
}

// Log error messages to Serial and MQTT
void logError(const String& message) {
  Serial.println("ERROR: " + message);
  client.publish(logErrorTopic, message.c_str(), true); // Retain the last message for debugging
}

// Log target settings to MQTT
void logTarget(bool heatingOn, bool hotWaterOn, bool enableCooling, float heatingSetpoint) {
  char payload[128];
  snprintf(payload, sizeof(payload),
           "{\"heatingOn\":\"%s\",\"hotWaterOn\":\"%s\",\"enableCooling\":\"%s\",\"heatingSetpoint\":%.2f}",
           heatingOn ? "ON" : "OFF",
           hotWaterOn ? "ON" : "OFF",
           enableCooling ? "ON" : "OFF",
           heatingSetpoint);

  client.publish(logTargetTopic, payload, false);
}
