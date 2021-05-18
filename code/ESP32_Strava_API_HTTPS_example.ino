#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>  
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "time.h"

// NTP server to request epoch time
const char* ntpServer = "pool.ntp.org";

// Variable to save current epoch time
unsigned long epochTime; 

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void setup() {
  Serial.begin(115200);
  delay(3000); //3 seconds
  WiFi.mode(WIFI_STA);
  WiFi.begin("SSID", "password");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Trying to connect to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  configTime(0, 0, ntpServer);
}



void loop() {  
  Serial.print(RecentRuns());

  epochTime = getTime();
  Serial.println("Epoch Time: ");
  Serial.println(epochTime);
  delay(900000); //wait 15 minutes
}

const int RecentRuns() { //check if connected to wifi, get recent run count from strava api, wait 15 minutes
  if ((WiFi.status() == WL_CONNECTED)) {  

    WiFiClientSecure client;

    HTTPClient https;
    
    if (https.begin("https://www.strava.com/api/v3/athletes/[ATHLETE NUMBER]/stats?access_token=[ACCESS TOKEN]")) {  // HTTPS
      int httpCode = https.GET();
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          
          // Serial.println("Show paypload");
          // Serial.println(payload);

          const size_t capacity = 6*JSON_OBJECT_SIZE(5) + 3*JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(11) + 1220;
          
          DynamicJsonDocument doc(capacity);
          DeserializationError error = deserializeJson(doc, payload);
          const int recentruns = doc["recent_run_totals"]["count"]; // extract nested information


          Serial.println(recentruns);
          
          return recentruns;
        }
      } else {
        return 0; //error check httpCode
      }
      https.end();
    } else {
      return 0; //error unable to connect
    }
  }
}
