#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  // put your setup code here, to run once:
  tone(4, 3000, 100);
  delay(1000);

  Serial.begin(9600);
  servoLeft.attach(13);
  servoRight.attach(12);
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(6000);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void loop() {
  
}
