#include <Servo.h>
Servo servoLeft;
Servo servoRight;
const int topLeft = 110;
const int topRight = 200;

const int wLeftPin = 5;
const int wRightPin = 7;
const int ledPin1 = 9; //Left indicator
const int ledPin2 = 3; //Right indicator
byte wLeftOld;
byte wRightOld;
byte counter;
const int maxCounter = 4;

void setup() {
  pinMode(wLeftPin, INPUT);
  pinMode(wRightPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);
  attachServos(13, 12);
  wLeftOld = 0;
  wRightOld = 1;
  counter  = 0;
}

void loop() {
  byte wLeft = digitalRead(wLeftPin);
  byte wRight = digitalRead(wRightPin);
  //If one whisker hits but not other one, do stuff
  if (wLeft != wRight) {
    //If it hit the opposite whisker, add to counter
    if ((wLeft != wLeftOld) && (wRight != wRightOld)) {
      counter++;
      wLeftOld = wLeft;
      wRightOld = wRight;
      if (counter >= maxCounter) {
        //Simulates a hit on both whiskers -> make 180 turn
        stopRoll(0);
        blinkLed();
        wLeft = 0;
        wRight = 0;
        counter = 0;
      }
    } else {
      counter = 0;
    }
  }

  if ((wLeft == 0) && (wRight == 0)) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    stopRoll(0);
    backwards(1500);
    stopRoll(0);
    turnLeft(2200);
  } else if (wLeft == 0) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    stopRoll(0);
    backwards(1000);
    stopRoll(20);
    turnRight(600);
  } else if (wRight == 0) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    stopRoll(0);
    backwards(1000);
    stopRoll(20);
    turnLeft(600);
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    forward(20);
  }
}


void forward(int i) {
  //
  servoLeft.writeMicroseconds(1500 + topLeft);
  servoRight.writeMicroseconds(1500 - topRight);
  delay(i);
}

void backwards(int i) {
  //Always expect to start from standstill
  //Acc for 0.5 seconds, with 25 iterations
  float leftAcc = topLeft / 25;
  float rightAcc = topRight / 25;
  int leftSpeed = 1500;
  int rightSpeed = 1500;

  for (int j = 0; j <= 25; j++) {
    leftSpeed -= (leftAcc + j);
    rightSpeed += (rightAcc + j);
    servoLeft.writeMicroseconds(leftSpeed);
    servoRight.writeMicroseconds(rightSpeed);
    delay(20);
  }
  delay(i - 500);
}

void stopRoll(int i) {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(i);
}

void turnOnCoin(bool rev, int i) {
  //Turn left by default
  if (!rev) {
    servoLeft.writeMicroseconds(1390);
    servoRight.writeMicroseconds(1300);
  } else {
    servoLeft.writeMicroseconds(1610);
    servoRight.writeMicroseconds(1700);
  }
  delay(i);
}
void turnRight(int i) {
  servoLeft.writeMicroseconds(1610);
  servoRight.writeMicroseconds(1500);
  delay(i);
}

void turnLeft(int i) {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1300);
  delay(i);
}
void detachServos() {
  servoRight.detach();
  servoLeft.detach();
}

void attachServos(int left, int right) {
  servoLeft.attach(left);
  servoRight.attach(right);
}

void blinkLed() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    delay(200);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    delay(200);
  }
}
