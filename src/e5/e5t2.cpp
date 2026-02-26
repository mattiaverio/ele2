#include <Arduino.h>
#include <AccelStepper.h>
#include <IRremote.hpp>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define IR_PIN 7

// Whyyy this order of IN pins :D
AccelStepper stepper(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4);

// Define step counts
float currentSpeed = 500.0;
const float speedStep = 100.0;
const int stepsPerRev = 2048; 

// Variables for button down movement
unsigned long lastIRTime = 0; 
const int irTimeout = 250;
bool isMovingManually = false;

void setup() {
  Serial.begin(9600);
  stepper.setMaxSpeed(6000.0); // Higher than this stops the motor
  stepper.setAcceleration(500.0);
  
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK); //
  Serial.println("Setup ready");
}

void loop() {
  if (IrReceiver.decode()) {
    // Check if repeated button press
    uint16_t command = IrReceiver.decodedIRData.command;
    bool isRepeat = IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT;

    // Refresh timer for repeat
    if (isRepeat && isMovingManually) {
        lastIRTime = millis();
    } 
    else {
      // Decision for decoded command
        switch (command) {
            case 0x44: // |<< 
                Serial.println("|<<");
                stepper.setSpeed(-currentSpeed);
                isMovingManually = true;
                lastIRTime = millis();
                break;
            
            case 0x43: // >>|
                Serial.println(">>|");
                stepper.setSpeed(currentSpeed);
                isMovingManually = true;
                lastIRTime = millis();
                break;

            case 0x9: // Up
                currentSpeed = min(currentSpeed + speedStep, 1000.0);
                Serial.print("Speed: "); Serial.println(currentSpeed);
                break;

            case 0x7: // Down
                currentSpeed = max(currentSpeed - speedStep, 100.0);
                Serial.print("Speed: "); Serial.println(currentSpeed);
                break;

            case 0x40: // >| 
                Serial.println("Demo");
                
                // Full rotation
                stepper.move(stepsPerRev);
                while (stepper.distanceToGo() != 0) stepper.run();
                
                delay(500); 
                
                // Full rotation back
                stepper.move(-stepsPerRev);
                while (stepper.distanceToGo() != 0) stepper.run();
            
                Serial.println("Demo complete.");
                break;
        }
    }
    IrReceiver.resume(); //
  }

  // Stop moving if released
  if (isMovingManually && (millis() - lastIRTime > irTimeout)) {
    Serial.println("Released and stop");
    stepper.setSpeed(0);
    isMovingManually = false;
  }

  // Run motor
  if (stepper.speed() != 0) {
    stepper.runSpeed();
  } else {
    stepper.run();
  }
}