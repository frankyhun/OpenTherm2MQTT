#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "mqtt_manager.h"
#include "config.h"
#include "wifi_manager.h"

extern PubSubClient client;

void reconnectMQTT() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("MQTT connected.");
      client.subscribe(heatingControlTopic);
      client.subscribe(hotWaterControlTopic);
      client.subscribe(heatingSetpointTopic);
    } else {
      Serial.println("MQTT connection failed, rc=" + String(client.state()));
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  message.trim();

  String topicStr = String(topic);
  Serial.println("MQTT message received: " + message + " ; topic: " + topicStr);
}

// Function to publish WiFi RSSI separately
void publishWiFiRSSI() {
  long rssi = WiFi.RSSI();
  Serial.println("wifi rssi: " + String(rssi));

  char payload[128];  // Reduce buffer size to save memory
  snprintf(payload, sizeof(payload), "{\"rssi\":%ld, \"ip\":\"%s\"}",
           rssi,
           WiFi.localIP().toString().c_str());

  client.publish(wifiRssiTopic, payload, false);
}
