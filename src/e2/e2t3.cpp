#include <Arduino.h>

// --- PINNIT ---
const int buzzerPin = 8;
const int btnC = 2; // C
const int btnD = 3; // D
const int btnE = 4; // E
const int btnF = 5; // F
const int btnMelody = 6;

// button notes
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349

// Nokia tunea notes
#define NOTE_E5  659
#define NOTE_D5  587
#define NOTE_FS4 370
#define NOTE_GS4 415
#define NOTE_CS5 554
#define NOTE_B4  494
#define NOTE_A4  440
#define NOTE_CS4 277

// Nokia Tune
// from https://github.com/robsoncouto/arduino-songs/blob/master/nokia/nokia.ino
int melody[] = {
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4,
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4,
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2
};
int melodyLength = sizeof(melody) / sizeof(melody[0]) / 2;

// Nokia tune funktion
void playNokiaTune() {
  for (int i = 0; i < melodyLength; i++) {
    int note = melody[i * 2];
    int duration = melody[i * 2 + 1];

    int noteDuration = 1000 / duration;
    
    tone(buzzerPin, note, noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(buzzerPin);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  // button pullups
  pinMode(btnC, INPUT_PULLUP);
  pinMode(btnD, INPUT_PULLUP);
  pinMode(btnE, INPUT_PULLUP);
  pinMode(btnF, INPUT_PULLUP);
  pinMode(btnMelody, INPUT_PULLUP);
}

void loop() {
  // read buttons and play tunes
  if (digitalRead(btnC) == LOW) {
    tone(buzzerPin, NOTE_C4);
  }
  else if (digitalRead(btnD) == LOW) {
    tone(buzzerPin, NOTE_D4);
  }
  else if (digitalRead(btnE) == LOW) {
    tone(buzzerPin, NOTE_E4);
  }
  else if (digitalRead(btnF) == LOW) {
    tone(buzzerPin, NOTE_F4);
  }
  else if (digitalRead(btnMelody) == LOW) {
    playNokiaTune();
  }
  else {
    noTone(buzzerPin);
  }
}