#ifndef EASY_WIFI_H
#define EASY_WIFI_H

#include "stdint.h"

enum Country {
  ZH,
  UK,
  US
};

void connect(const char* ssid, const char* password, uint8_t oled_addr);
void init_time(Country country);
void write_time();
void printLocalTime(bool doDisplay = true);

#endif
