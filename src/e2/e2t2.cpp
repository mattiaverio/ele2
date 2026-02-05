#include <Arduino.h>

const int pinRed = 9;
const int pinGreen = 10;
const int pinBlue = 11;

// (16MHz / 1024 = 15625 tick per second)
const int timerTicks = 15625; 
volatile int colorIndex = 0; 


// interrupt
ISR(TIMER1_COMPA_vect) {
  
  // add timer for next
  OCR1A += timerTicks; 

  // switch color
  colorIndex++;
  if (colorIndex > 5) {
    colorIndex = 0;
  }

  // color switcher
  switch (colorIndex) {
    case 0: // Red
      digitalWrite(pinRed, HIGH); digitalWrite(pinGreen, LOW);  digitalWrite(pinBlue, LOW);
      break;
    case 1: // Green
      digitalWrite(pinRed, LOW);  digitalWrite(pinGreen, HIGH); digitalWrite(pinBlue, LOW);
      break;
    case 2: // Blue
      digitalWrite(pinRed, LOW);  digitalWrite(pinGreen, LOW);  digitalWrite(pinBlue, HIGH);
      break;
    case 3: // Yellow
      digitalWrite(pinRed, HIGH); digitalWrite(pinGreen, HIGH); digitalWrite(pinBlue, LOW);
      break;
    case 4: // Magenta
      digitalWrite(pinRed, HIGH); digitalWrite(pinGreen, LOW);  digitalWrite(pinBlue, HIGH);
      break;
    case 5: // Cyan
      digitalWrite(pinRed, LOW);  digitalWrite(pinGreen, HIGH); digitalWrite(pinBlue, HIGH);
      break;
  }
}

void setup() {
  pinMode(pinRed,   OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue,  OUTPUT);

  // timer init
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  // Prescaler 1024
  TCCR1B |= B00000101; 
  OCR1A = timerTicks; // first interrupt
  TIMSK1 |= B00000010; // timer comparator
}

void loop() {

}