#include <Arduino.h>
#include <LiquidCrystal.h>

// LCD setup: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Classic alphabet test
// https://www.youtube.com/watch?v=wADiXgCHnak
String scroll = "The Quick Brown Fox Jumps Over A Lazy Dog        "; 
int lcdWidth = 16;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("E5 T3");
  delay(2000);
}

void loop() {
  // Scroll
  for (int i = 0; i < scroll.length() + lcdWidth; i++) {
    lcd.setCursor(0, 1); // Cursor for lower row
    
    // Create 16 char string
    String lcdDisplay = "";
    for (int j = 0; j < lcdWidth; j++) {
      int charIndex = i + j - lcdWidth;
      
      if (charIndex >= 0 && charIndex < scroll.length()) {
        lcdDisplay += scroll[charIndex];
      } else {
        lcdDisplay += " "; // Fill with whitespace
      }
    }
    
    lcd.print(lcdDisplay);
    delay(500); // Too fast makes the display unreadable
  }
}