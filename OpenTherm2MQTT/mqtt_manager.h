#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

void reconnectMQTT();
void mqttCallback(char* topic, byte* payload, unsigned int length);
void publishWiFiRSSI();

#endif
