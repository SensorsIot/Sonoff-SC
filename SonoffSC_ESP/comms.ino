/*

  COMMUNICATIONS MODULE

  Copyright (C) 2016 by Xose Pérez <xose dot perez at gmail dot com>

*/
#include "SerialLink.h"

SerialLink link(Serial, false);

const PROGMEM char at_push[] = "AT+PUSH";
const PROGMEM char at_every[] = "AT+EVERY";
const PROGMEM char at_temp[] = "AT+TEMP";
const PROGMEM char at_hum[] = "AT+HUM";
const PROGMEM char at_dust[] = "AT+DUST";
const PROGMEM char at_noise[] = "AT+NOISE";
const PROGMEM char at_light[] = "AT+LIGHT";
const PROGMEM char at_clap[] = "AT+CLAP";
const PROGMEM char at_code[] = "AT+CODE";
const PROGMEM char at_thld[] = "AT+THLD";

// -----------------------------------------------------------------------------
// VALUES
// -----------------------------------------------------------------------------

float temperature;
int humidity;
int light;
float dust;
int noise;

float getTemperature() {
  return temperature;
}
float getHumidity() {
  return humidity;
}
float getLight() {
  return light;
}
float getDust() {
  return dust;
}
float getNoise() {
  return noise;
}

// -----------------------------------------------------------------------------
// COMMUNICATIONS
// -----------------------------------------------------------------------------

bool commsGet(char * key) {
  Serial.println(key);
  return false;
}

bool commsSet(char * key, int value) {

  Serial.println(key);
  Serial.println(value);
  if (strcmp_P(key, at_code) == 0) {
    mqttSend(MQTT_CLAP_TOPIC, value);
    return true;
  }

  if (strcmp_P(key, at_temp) == 0) {
    temperature = (float) value / 10;
    mqttSend(MQTT_TEMPERATURE_TOPIC, temperature);
    return true;
  }

  if (strcmp_P(key, at_hum) == 0) {
    humidity = value;
    mqttSend(MQTT_HUMIDITY_TOPIC, humidity);
    return true;
  }

  if (strcmp_P(key, at_light) == 0) {
    light = value;
    mqttSend(MQTT_LIGHT_TOPIC, light);
    return true;
  }

  if (strcmp_P(key, at_dust) == 0) {
    dust = (float) value / 100;
    mqttSend(MQTT_DUST_TOPIC, dust);
    return true;
  }

  if (strcmp_P(key, at_noise) == 0) {
    noise = value;
    mqttSend(MQTT_NOISE_TOPIC, noise);
    return true;
  }

  return false;

}

void commConfigure() {
  while (link.send_P(at_every, updateInterval, 1) == 0)delay(1000);
  link.send_P(at_clap, SENSOR_CLAP_ENABLED == 1 ? 1 : 0);
  while (link.send_P(at_push, 1, 1) == 0)delay(1000);
}

void commsSetup() {

  link.onGet(commsGet);
  link.onSet(commsSet);
}

void commsLoop() {
  link.handle();
}
