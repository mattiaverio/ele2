#include <Arduino.h>
#include <DHT.h>

// Define pins
#define DHTPIN 9          
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);

  // read measurements using Adafruit library
  float h = dht.readHumidity();
  float t = dht.readTemperature();


  // if no readings
  if (isnan(h) || isnan(t)) {
    Serial.println("No measurement");
    return;
  }

  // print measurements and wait 2000
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("% | Temp: ");
  Serial.print(t);
  Serial.println("C");
}