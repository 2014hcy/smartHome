# __smartHome__ - A _smart detection system_ on _ESP32_ and _ESP32-C3_ Board.

__It's__ can __displaying temp, humi and current time__ on the __OLED!__ If you __closing__ to the __*UltraSonic Sensor*__, it's can __control__ the __light on.__

## Requirement

1. __ESP32__ or __ESP32-C3__ Board.
2. An __I2C OLED(*SSD1306*)__.
3. A __light(*HW-269*)__.
4. A __DHT11 sensor__.
5. A __red LED__.
6. A __UltraSonic sensor(*HC-SR04*)__.
7. A __computer__ have __*Arduino IDE*__.

## Wiring

LED GND -> 270Ω resistance to the Ground, VCC -> 13.
Other all VCC -> 3.3V, GND -> GND.

OLED_SSD1306: SCL -> 22, SDA -> 21.
HW-269: S -> 27.
DHT11: DATA -> 141.
HC-SR04: Trig -> 25, Echo -> 26.

## Instructions

__"TIMEZONE"__ is for __select time zone__. It's can be __"ZH"(Beijing China)__, __"UK"(United Kingdom)__, __"US"(United States)__.
