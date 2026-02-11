#include <Arduino.h>

// Shift Register pins
#define DATA_PIN 12
#define LATCH_PIN 13
#define CLOCK_PIN 11

// Pin 3 for button interrupt, other for display
const int digitPins[4] = { 2, 10, 4, 5 }; 
const int buttonPin = 3;

// Must be volatile to be accessible with interrupts
volatile byte fallingEdges = 0; 

const byte digitCodes[10] = {
  0b00111111,  // 0
  0b00000110,  // 1
  0b01011011,  // 2
  0b01001111,  // 3
  0b01100110,  // 4
  0b01101101,  // 5
  0b01111101,  // 6
  0b00000111,  // 7
  0b01111111,  // 8
  0b01101111   // 9
};

// interrupt function
void countEdges() {
  fallingEdges++; // Kasvatetaan laskuria aina kun reuna havaitaan
}

// Display given digit
void shiftOutDigit(byte data) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, data);
  digitalWrite(LATCH_PIN, HIGH);
}

//  Funktion to display number
void displayNumber(byte number) {
  int d[4];
  d[0] = (number / 1000) % 10;
  d[1] = (number / 100) % 10;
  d[2] = (number / 10) % 10;
  d[3] = number % 10;

  // Display number for 1 second
  unsigned long displayStart = millis();
  while(millis() - displayStart < 1000) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(digitPins[i], LOW);
      shiftOutDigit(digitCodes[d[i]]);
      delay(5);
      digitalWrite(digitPins[i], HIGH);
    }
  }
}

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH);
  }

  // Attach interrupt to button
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), countEdges, FALLING);
}

void loop() {
  delay(5000);
  displayNumber(fallingEdges);
  fallingEdges = 0;
}