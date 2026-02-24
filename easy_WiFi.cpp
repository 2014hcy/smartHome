#include "Arduino.h"
#include "WiFi.h"
#include "easy_WiFi.h"
#include "time.h"
#include "oled.h"

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const char* ntpServer3 = "cn.pool.ntp.org";

struct TimeZoneConfig {
  const char* posix_tz;
  const char* display_name;
  const char* time_format;
};

const TimeZoneConfig TZ_CHINA = {
  "CST-8",
  "China",
  "%Y-%m-%d %H:%M %a"
};

const TimeZoneConfig TZ_UK = {
  "GMT0BST,M3.5.0/1,M10.5.0/2",
  "UK",
  "%Y-%m-%d %H:%M %a"
};

const TimeZoneConfig TZ_US = {
  "EST5EDT,M3.2.0,M11.1.0",
  "USA",
  "%Y-%m-%d %H:%M %a"
};

TimeZoneConfig current_tz;

int counter = 0;

void printLocalTime(bool doDisplay) {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    write("Get time failed!");
    if (doDisplay) displaying();
    return;
  }

  char output[50];

  strftime(output, sizeof(output), current_tz.time_format, &timeinfo);
  writeln(output);
  
  if (doDisplay) displaying();
}

void led(int pin) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pin, HIGH);
    delay(50);
    digitalWrite(pin, LOW);
    delay(50);
  }
  digitalWrite(pin, HIGH);
}

void led2(int pin) {
  digitalWrite(pin, LOW);
  delay(1000);
  digitalWrite(pin, HIGH);
  delay(1000);
}

void connect(const char* ssid, const char* password, uint8_t oled_addr) {
  init_OLED(oled_addr);
  pinMode(13, OUTPUT);

  WiFi.begin(ssid, password);
  write("WiFi Connecting...");
  displaying();
  
  led(13);
  delay(1700);
    
  while (WiFi.status() != WL_CONNECTED) {
    clear();
    write("WiFi Connecting...");
    displaying();
    led(13);
    delay(1700);
  }
  
  clear();
  writeln("WiFi Connect!");  
  displaying();
  
  led(13);
  delay(700);
  clear();
}

void init_time(Country country) {
  switch(country) {
    case ZH:
      current_tz = TZ_CHINA;
      break;
    case UK:
      current_tz = TZ_UK;
      break;
    case US:
      current_tz = TZ_US;
      break;
    default:
      current_tz = TZ_CHINA;
  }

  write("Config ");
  write(current_tz.display_name);
  writeln(" time...");
  displaying();
  delay(1000);
  
  configTzTime(current_tz.posix_tz, ntpServer1, ntpServer2, ntpServer3);

  struct tm timeinfo;
  clear();
  writeln("Sync NTP time");
	write("of ");
  write(current_tz.display_name);
	writeln("...");
  displaying();

  led2(13);
  clear();

  int retry_count = 0;
  while (true) {
    led2(13);

    if(getLocalTime(&timeinfo)) {
      clear();
      write("Time Sync ");
      writeln(current_tz.display_name);
			writeln("finish!");
      displaying();
      led(13);
      delay(1500);
      clear();

      printLocalTime();
      break;
    }
    
    retry_count++;
    if (retry_count > 30) {
      clear();
      writeln("NTP Failed!");
      writeln(current_tz.display_name);
      displaying();
      led(13);
      delay(3000);
      break;
    }
  }
}

void write_time() {
  clear();
  printLocalTime();
  delay(1000);
}

