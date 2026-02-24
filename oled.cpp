#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "./oled.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void init_OLED(uint8_t I2C_ADDR) {
  Wire.begin();
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, I2C_ADDR)) {
    Serial.println("OLED failed!");
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
}

void write(String Text) {
  display.print(Text);
}

void writeln(String Text) {
  display.println(Text);
}

void drawLine(int x0, int y0, int x1, int y1) {
  display.drawLine(x0, y0, x1, y1, WHITE);
}

void displaying() {
  display.display();
}

void clear() {
  display.clearDisplay();
  display.setCursor(0, 0);
}
