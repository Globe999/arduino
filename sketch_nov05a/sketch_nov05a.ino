#include <Servo.h>

Servo servoLeft;
Servo servoRight;
Servo servoTurret;

const int servoLeftPin = 13;
const int servoRightPin = 12;
const int servoTurretPin = 11;
const int pingPin = 10;
const int arrSize = 140;

int angles[arrSize];
int distArr[arrSize];

void setup() {
  Serial.begin(9600);
  Serial.println("This is a test");

  servoLeft.attach(servoLeftPin);                  // Attach left signal to pin 13
  servoRight.attach(servoRightPin);                // Attach right signal to pin 12
  servoTurret.attach(servoTurretPin);

  for (int i = 0; i <= arrSize; i++) {
    angles[i] = i + 20;
  }

  turret(90);                                       //Set turret to 90
  delay(500);
  scan();
  evalData();
}

void loop() {
  // put your main code here, to run repeatedly:

}



void maneuver(int speedLeft, int speedRight, int ms)
{
  speedLeft = constrain(speedLeft, -110, 110); //Old servo on right, can max be 110 to have straight path
  speedRight = constrain(speedRight, -200, 200);
  servoLeft.writeMicroseconds(1500 + speedLeft);
  servoRight.writeMicroseconds(1500 - speedRight);
  if (ms == -1) {
    servoLeft.detach();
    servoRight.detach();
  }
  delay(ms);
}

void scan() {
  for (int i = 0; i < arrSize; i++) {
    turret(angles[i]);
    distArr[i] = ping(pingPin);
    delay(50);
  }
  turret(90);
}

//Evaluates distances to analyze objects
void evalData() {
  int arrFound[arrSize];
  int iStart, iEnd;
  for (int i = 0; i < arrSize - 1; i++) {
    //check if it's less than 5cm difference, treat as same object.
    if ((distArr[i] < distArr[i-1]-5) || distArr[i] > distArr[i-1]+5) continue;
    if (!iStart) {
      //shorter distance to object!
      if (distArr[i] < distArr[i - 1]) {
        iStart = i
                 //closer object found, start recording
                 //arrFound[];
      }
    }
  }
}

void turret(int degreeVal) {
  servoTurret.write(degreeVal);
}

long ping(int pin) {
  long duration, cm;

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);

  pinMode(pin, INPUT);
  duration = pulseIn(pin, HIGH);

  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.println(" cm");
  return cm;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / (29 * 2);
}
