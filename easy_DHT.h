#ifndef EASY_DHT_H
#define EASY_DHT_H

#include "Arduino.h"
#include "stdint.h"

void init_DHT(uint8_t pin, uint8_t type, uint8_t oled_addr);
void write_data();

#endif