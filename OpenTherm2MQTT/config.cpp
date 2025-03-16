#include "config.h"

// WiFi Credentials
const char* ssid = "TODO";
const char* password = "TODO";

// MQTT Server
const char* mqtt_server = "TODO";
const int mqtt_port = 1883;
const char* mqtt_user = "TODO";
const char* mqtt_password = "TODO";

// MQTT Topics
const char* statusTopic = "boiler/status";
const char* logTargetTopic = "boiler/target";
const char* wifiRssiTopic = "boiler/wifi";
const char* logInfoTopic = "boiler/log/info";
const char* logErrorTopic = "boiler/log/error";
const char* heatingControlTopic = "boiler/control/heating";
const char* hotWaterControlTopic = "boiler/control/hotwater";
const char* heatingSetpointTopic = "boiler/control/heating_setpoint";

// OpenTherm Pins
const int inPin = 4;
const int outPin = 5;

// Timer Intervals
const unsigned long rssiPublishInterval = 5 * 60 * 1000; // 5 minute
