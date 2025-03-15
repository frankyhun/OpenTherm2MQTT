#include <ESP8266WiFi.h>
#include "wifi_manager.h"
#include "config.h"

void connectToWiFi() {
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 30) {
    delay(1000); 
    Serial.print(".");
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
  } else {
    Serial.println("Failed to connect to WiFi.");
  }
}

void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Attempting to reconnect...");
    connectToWiFi();
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Failed to reconnect. Rebooting...");
      delay(10 * 1000);
      ESP.restart();
    }
  }
}
