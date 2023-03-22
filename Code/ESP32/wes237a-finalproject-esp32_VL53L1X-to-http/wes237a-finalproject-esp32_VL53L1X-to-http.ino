
// WES237A Final Project - ESP32: VL53L1X to http POST
// David Rodriguez
// March 2023


#include <WiFi.h>
#include <HTTPClient.h>
#include "SparkFun_VL53L1X.h"

const char* ssid = "ssid";
const char* password = "password";

// AWS Public DNS Domain name containing ToF http URL path
const char* serverName = "http://ec2-35-90-59-237.us-west-2.compute.amazonaws.com:1880/tof";

unsigned long lastTime = 0;
unsigned long timerDelay = 1000; // 1 sec. timer delay
String ToF;

SFEVL53L1X distanceSensor;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("WES237A Final Project - ESP32 VL53L1X Sensor Node");

  if (distanceSensor.begin() != 0) // begin returns 0 from successful init{
    Serial.println("Sensor failed to begin. Please check wiring and restart.");
    while (1)
      ;
  }
  Serial.println("Distance Sensor Online");

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Send an HTTP POST request after every timer delay
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
    
      // Initiate connection to AWS Server
      http.begin(client, serverName);
      
      distanceSensor.startRanging(); // Write configuration bytes to initiate measurement
      while (!distanceSensor.checkForDataReady()) {
        delay(1);
      }

      int distance = distanceSensor.getDistance(); // Get the sensor measurement result
      distanceSensor.clearInterrupt();
      distanceSensor.stopRanging();
    
      Serial.print("Distance(mm): ");
      Serial.print(distance);

      ToF = String(distance);
      
      // HTTP POST request with Content type: text/plain
      http.addHeader("Content-Type", "text/plain");
      int httpResponseCode = http.POST(ToF);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free up ESP32 Resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
