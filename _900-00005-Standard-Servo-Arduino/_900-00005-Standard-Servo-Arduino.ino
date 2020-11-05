#include <Servo.h>    // Use Servo library, included with IDE

Servo myServo;        // Create Servo object to control the servo 

void setup() { 
  myServo.attach(11);  // Servo is connected to digital pin 9 
} 

void loop() { 
//  myServo.write(180);   // Rotate servo counter clockwise
  delay(2000);          // Wait 2 seconds
  myServo.write(0);     // Rotate servo clockwise
  delay(2000);
  myServo.write(180);
  delay(2000);
  myServo.write(86);
}
