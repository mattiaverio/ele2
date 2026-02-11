// Used following resource as a starting point for this task
// https://docs.sunfounder.com/projects/newton-lab-kit/en/latest/cproject/ar_74hc595_4dig.html

#include <Arduino.h>
#include <DHT.h>

// Shift Register pins
#define DATA_PIN 12
#define LATCH_PIN 13
#define CLOCK_PIN 11 

// Display control pins
const int digitPins[4] = { 2, 3, 4, 5 }; 

// DHT11
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Segment mapping for numbers
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

// Special chars
const byte CHAR_C = 0b00111001;
const byte DOT    = 0b10000000;

// Variables
unsigned long previousMillis = 0; 
int currentTemp = 0;
bool showTemp = false;

// Display given digit
void shiftOutDigit(byte data) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, data);
  digitalWrite(LATCH_PIN, HIGH);
}

void displayLeet() {
  int d[4];
  d[0] = 1;
  d[1] = 3;
  d[2] = 3;
  d[3] = 7;

  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], LOW);
    shiftOutDigit(digitCodes[d[i]]);
    delay(5);
    digitalWrite(digitPins[i], HIGH);
  }
}

void displayNumber(int num) {
  // Num is already converted
  // 23,5 -> 235
  
  // Digit 1
  digitalWrite(digitPins[0], LOW);
  shiftOutDigit(digitCodes[(num / 100) % 10]);
  delay(5);
  digitalWrite(digitPins[0], HIGH);

  // Digit 2
  digitalWrite(digitPins[1], LOW);
  // Add dot using OR operation
  shiftOutDigit(digitCodes[(num / 10) % 10] | DOT);
  delay(5);
  digitalWrite(digitPins[1], HIGH);

  // Digit 3
  digitalWrite(digitPins[2], LOW);
  shiftOutDigit(digitCodes[num % 10]);
  delay(5);
  digitalWrite(digitPins[2], HIGH);

  // Digit 4: always C :D
  digitalWrite(digitPins[3], LOW);
  shiftOutDigit(CHAR_C);
  delay(5);
  digitalWrite(digitPins[3], HIGH);
}

void setup() {
  Serial.begin(9600);
  
  // Init pins

  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH);
  }

  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  // Read DHT11
  if (currentMillis - previousMillis >= 2000) {
    previousMillis = currentMillis;
    
    float t = dht.readTemperature();
    
    if (isnan(t)) {
      currentTemp = 0; // No reading
    } else {
      // Convert to integer "without decimal dot"
      currentTemp = (int)(t * 10);
    }

    // swap between temp and leet
    showTemp = !showTemp;
  }

  // Refreh display non stop
  if (showTemp) {
    displayNumber(currentTemp);
  } else {
    displayLeet();
  }
}