#include <Arduino.h>

void setup() {
  pinMode(2, INPUT);    // PIR
  pinMode(LED_BUILTIN, OUTPUT);  // Arduinon sisäänrakennettu LED
}

void loop() {
  // If movement found
  if (digitalRead(2)) {
    digitalWrite(13, HIGH); // LED on
    delay(5000); // wait
    digitalWrite(13, LOW); // LED off
  }
}