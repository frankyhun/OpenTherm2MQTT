// This file contains all configuration settings like WiFi credentials, MQTT server settings, and other constants.

#ifndef CONFIG_H
#define CONFIG_H

// WiFi Credentials
extern const char* ssid;
extern const char* password;

// MQTT Server
extern const char* mqtt_server;
extern const int mqtt_port;
extern const char* mqtt_user;
extern const char* mqtt_password;

// MQTT Topics
extern const char* statusTopic;
extern const char* logTargetTopic;
extern const char* wifiRssiTopic;
extern const char* logInfoTopic;
extern const char* logErrorTopic;
extern const char* heatingControlTopic;
extern const char* hotWaterControlTopic;
extern const char* heatingSetpointTopic;

// OpenTherm Pins
extern const int inPin;
extern const int outPin;

// Timer Intervals
extern const unsigned long rssiPublishInterval;

#endif
