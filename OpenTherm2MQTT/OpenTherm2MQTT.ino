#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <opentherm.h>

#include "config.h"
#include "logger.h"
#include "wifi_manager.h"
#include "mqtt_manager.h"

OpenTherm ot(inPin, outPin);
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastRssiPublish = 0;

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
  ot.begin();
}

void loop() {

  // remember when we began the loop
  loop_begin_time = millis();

  // check wifi, reconnect if dropped, reboot if reconnect fails
  checkWiFi();
  
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  if (ot.isReady()) {
    logTarget(heatingOn, hotWaterOn, enableCooling, heatingSetpoint);
    unsigned long response = ot.setBoilerStatus(heatingOn, hotWaterOn, enableCooling);
    OpenThermResponseStatus responseStatus = ot.getLastResponseStatus();
    handleOpenThermResponse(response, responseStatus);
  }

  // Publish WiFi RSSI every 5 minute
  if (millis() - lastRssiPublish >= rssiPublishInterval) {
    publishWiFiRSSI();
    lastRssiPublish = millis();
  }

  // OpenTherm boilers expect to communicate every 1 sec, otherwise they may get in error state
  // Calculate the time taken by the operations so far
  unsigned long elapsed_time = millis() - loop_begin_time;
  // Ensure the total loop time is 800 ms
  // If `elapsed_time` is already greater than 800 ms, we skip the delay and move to the next loop iteration
  if (elapsed_time <= 800) {
      delay(800 - elapsed_time);
  }
}

  // Handle OpenTherm response
void handleOpenThermResponse(unsigned long response, OpenThermResponseStatus responseStatus) {
  if (responseStatus == OpenThermResponseStatus::SUCCESS) {
    char payload[256];
    snprintf(
      payload, sizeof(payload), "{\"heating\":\"%s\",\"hotwater\":\"%s\",\"flame\":\"%s\",\"modulation\":%.2f,\"pressure\":%.2f,\"temperature\":%.2f,\"return_temperature\":%.2f}",
      ot.isCentralHeatingActive(response) ? "ON" : "OFF", 
      ot.isHotWaterActive(response) ? "ON" : "OFF",
      ot.isFlameOn(response) ? "ON" : "OFF",
      ot.getModulation(),
      ot.getPressure(),
      ot.getBoilerTemperature(),
      ot.getReturnTemperature()
    );
    client.publish(statusTopic, payload, false);
  } else if (responseStatus == OpenThermResponseStatus::NONE) {
    logError("Error: OpenTherm is not initialized");
  } else if (responseStatus == OpenThermResponseStatus::INVALID) {
    logError("Invalid response " + String(response, HEX));
  } else if (responseStatus == OpenThermResponseStatus::TIMEOUT) {
    logError("Response timeout");
  }
}
