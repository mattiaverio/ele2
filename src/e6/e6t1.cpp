#include <Arduino.h>

#define ENABLE 10 
#define IN1 9
#define IN2 8
#define POT A0

void setup() {
  pinMode(ENABLE, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(9600);
  Serial.println("Setup ready");
}

void loop() {
  int potValue = analogRead(POT); // 0 - 1023
  int motorSpeed = 0;

  // Dead zone (480 - 544)
  if (potValue >= 480 && potValue <= 544) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENABLE, 0);
  } 
  // Forwards
  else if (potValue > 544) {
    motorSpeed = map(potValue, 545, 1023, 0, 255);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENABLE, motorSpeed);
  } 
  // Backwards
  else if (potValue < 480) {
    motorSpeed = map(potValue, 479, 0, 0, 255);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENABLE, motorSpeed);
  }

  Serial.print("Pot: "); Serial.print(potValue);
  Serial.print(" | Speed: "); Serial.println(motorSpeed);
  delay(50);
}