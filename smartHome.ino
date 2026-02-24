#include "oled.h"
#include "easy_WiFi.h"
#include "easy_DHT.h"
#include "Ultralib.h"
#include "DHT.h"

#define DHTPIN      14
#define DHTTYPE     DHT11
#define TRIG_PIN    25
#define ECHO_PIN    26
#define LED_PIN     27
#define OLED_ADDR   0x3C
#define TIMEZONE    ZH

Ultra ultra(TRIG_PIN, ECHO_PIN);

float temperature = 0;
float humidity = 0;
float distance = 0;
String currentTime = "";

TaskHandle_t Task1_Handle = NULL;
TaskHandle_t Task2_Handle = NULL;
TaskHandle_t Task3_Handle = NULL;

void Task_DHT(void *pvParameters) {
  DHT dht(DHTPIN, DHTTYPE);
  dht.begin();
  
  while(1) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    
    if (!isnan(t) && !isnan(h)) {
      temperature = t;
      humidity = h;
    }
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}


void Task_Ultrasonic(void *pvParameters) {
  while(1) {
    distance = ultra.read();
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void Task_Display(void *pvParameters) {
  connect("1206", "13867627688", OLED_ADDR);
  
  init_time(TIMEZONE);
  
  while(1) {
    clear();
    
    printLocalTime(false);

    writeln("");
    drawLine(0, 12, 127, 12);

    write("Temp: ");
    write(String(temperature, 1));
    writeln(" C");
    write("Humi: ");
    write(String(humidity, 1));
    writeln(" %");
    
    displaying();
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  xTaskCreatePinnedToCore(
    Task_DHT, "DHT", 4096, NULL, 1, &Task1_Handle, 0);
  xTaskCreatePinnedToCore(
    Task_Ultrasonic, "Ultra", 4096, NULL, 1, &Task2_Handle, 0);
  xTaskCreatePinnedToCore(
    Task_Display, "Display", 8192, NULL, 2, &Task3_Handle, 1);
}

void loop() {
  if (distance <= 30 && distance > 0) {
    analogWrite(LED_PIN, 10);
  } else {
    analogWrite(LED_PIN, 0);
  }
  
  vTaskDelay(100 / portTICK_PERIOD_MS);
}
