#include <Servo.h>

Servo servoRight;
Servo servoLeft;
Servo servoHead;

int speedRight=1485;
int speedLeft=1500;

int pinServoR=0;
int pinServoL=0;
int pinServoH=0;
int pingPin=0;

void setup() {
  Serial.begin(9600);
  servoRight.attach(pinServoR);
  servoLeft.attach(pinServoL);
  servoHead.attach(pinServoH);

}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void stop(){
  servoRight.writeMicroseconds(1485);
  servoLeft.writeMicroseconds(1500);
}

void straightFwd(int speed){
  servoRight.writeMicroseconds(1485 + speed);
  servoLeft.writeMicroseconds(1500 - speed);
}

void straightBwd(int speed){
  servoRight.writeMicroseconds(1485 - speed);
  servoLeft.writeMicroseconds(1500 + speed);
}

void ping(){
  long duration, cm;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  
  Serial.print(cm);
  Serial.println(" cm");

  delay(100);
}

long microsecondsToCentimeters(long microseconds){
  return microseconds/(29*2);
}
