/***********************************************************************
 * Exp2_DriveForward -- RedBot Experiment 2
 * 
 * Drive forward and stop.
 * 
 * Hardware setup:
 * The Power switch must be on, the motors must be connected, and the board must be receiving power 
 * from the battery. The motor switch must also be switched to RUN.
 *
 * 23 Sept 2013 N. Seidle/M. Hord
 * 04 Oct 2014 B. Huang
 ***********************************************************************/
#include <Arduino.h>
#include <RedBot.h>  // This line "includes" the RedBot library into your sketch.
// Provides special objects, methods, and functions for the RedBot.

// Constant Identifiers
int rangePin = A0;    // range sensor
int lightPin = A1;    // light sensor
int rangeValue = 0;   // variables to store the values coming from sensors
int lightValue = 0;

RedBotMotors motors; // Instantiate the motor control object. This only needs

// startup, we want to write to the serial monitor if motors are disabled.
void setup()
{
  Serial.begin(9600);  
}

void loop()
{
   delay(100);
   rangeValue = analogRead(rangePin);
   lightValue = analogRead(lightPin);
   // These numbers were determined by experiment.  It is possible that we could get 
   // out of range values, but looking at the voltage definitions and the range of 
   // sensing, these seem to pass a sanity check. Our goal is a large number when 
   // something is close and an even distribution from about 0 to 255. because we use
   // 125 - rangeValue if the ceiling is high we get a negative number which is not 
   // a big deal, although it may mean it always moves faster when obstacle is close.
   rangeValue = 125 - rangeValue;
   rangeValue = rangeValue*2;
   Serial.print("Range: ");
   Serial.println(rangeValue, DEC);
      
   lightValue = lightValue/4;
   Serial.print("Light: ");
   Serial.println(lightValue, DEC);
   
   int motorSpeed = max(lightValue, rangeValue);
   if (motorSpeed > 50) {
       motors.drive(motorSpeed);
   } else {
       motors.stop();
   }
}


