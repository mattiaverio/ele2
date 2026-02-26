// https://www.circuitbasics.com/arduino-ir-remote-receiver-tutorial/
// Used this outdated tutorial as a starting point to avoid easy route...

#include <Arduino.h>
#include <IRremote.hpp>

const int RECV_PIN = 7;

void setup(){
    Serial.begin(9600);
    // Enable IRremote receiving
    IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
    Serial.println("Waiting for IR");
}

void loop(){

    // Read receiver message
    if (IrReceiver.decode()) {
        // For reading hex codes for mapping
        //Serial.println(IrReceiver.decodedIRData.command, HEX);
        uint16_t command = IrReceiver.decodedIRData.command;

        // Switch to print out identified buttons
        switch(command){
          case 0x45:
          Serial.println("Power");
          break;
          case 0x46:
          Serial.println("VOL+");
          break;
          case 0x47:
          Serial.println("FUNC/STOP");
          break;
          case 0x44:
          Serial.println("|<<");
          break;
          case 0x43:
          Serial.println(">>|");
          break ;  
          case 0x40:
          Serial.println(">|");
          break ;               
          case 0x7:
          Serial.println("Down");
          break ;  
          case 0x9:
          Serial.println("Up");
          break ;  
          case 0x15:
          Serial.println("VOL-");
          break ;  
          case 0x19:
          Serial.println("EQ");
          break ;  
          case 0xD:
          Serial.println("ST/REPT");
          break ;
          case 0x16:
          Serial.println("0");
          break ;
          case 0xC:
          Serial.println("1");
          break ;
          case 0x18:
          Serial.println("2");
          break ;
          case 0x5E:
          Serial.println("3");
          break ;
          case 0x8:
          Serial.println("4");
          break ;
          case 0x1C:
          Serial.println("5");
          break ;
          case 0x5A:
          Serial.println("6");
          break ;
          case 0x42:
          Serial.println("7");
          break ;
          case 0x52:
          Serial.println("8");
          break ;
          case 0x4A:
          Serial.println("9");
          break ;      
        }

        delay(300);
        IrReceiver.resume();
  }
}