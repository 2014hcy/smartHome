#include "Arduino.h"
#include "stdint.h"
#include "DHT.h"
#include "oled.h"
#include "easy_DHT.h"

DHT* dht = NULL;

void init_DHT(uint8_t pin, uint8_t type, uint8_t oled_addr) {
  init_OLED(oled_addr);

  dht = new DHT(pin, type);
  dht->begin();
}

void write_data() {
  delay(2000);

  float temp = dht->readTemperature();
  float humi = dht->readHumidity();

  if (isnan(humi) || isnan(temp)) {
    Serial.println("DHT error!");
    writeln("DHT error!");
    displaying();
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp, 1);
  Serial.print("°C | ");
  Serial.print("Humi: ");
  Serial.print(humi, 1);
  Serial.println("%");

  clear();

  write("Temp: ");
  write(String(temp, 1));
  writeln(" C");

  write("Humi: ");
  write(String(humi, 1));
  writeln(" %");

  displaying();
}