#include <Servo.h>

Servo servoLeft;
Servo servoRight;
Servo servoTurret;

const int servoLeftPin = 13;
const int servoRightPin = 12;
const int servoTurretPin = 11;
const int pingPin = 10;
int i = 0;
int obSize[2] = {};
int pingDegree[140]= {};

void setup() {
  Serial.begin(9600);
  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);
  servoTurret.attach(servoTurretPin);

  servoLeft.writeMicroseconds(1500); // Går framåt från +1500 till 1700
  servoRight.writeMicroseconds(1500); // Går framåt från -1500 till 1300
  turret(20);
  delay(1000);
  scan(160);
  Serial.println(obSize[0]);
  Serial.println(obSize[1]);

}

void loop() {


}

void maneuver(int speedLeft, int speedRight, int duration) {
  servoLeft.writeMicroseconds(1500 + speedLeft);
  servoRight.writeMicroseconds(1500 - speedRight);
  delay(duration);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void turret(int degreeVal) {
  servoTurret.write(degreeVal);
}
void scan(int degree) {
  int j = 0;
  int k = 0;
  i = 180 - degree;
  while (i < degree) {
    if (ping(pingPin) < 50) {
      j++;
      pingDegree[i] = 0;
    } else {
      pingDegree[i] = 1;
      if (0 < j) {
        obSize[k] = j;
        k++;
        j = 0;
      }
    }
    turret(i);
    delay(5);
    Serial.println(ping(pingPin));
    delay(20);
    i++;

  }
  i = 90;


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


  return cm;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / (29 * 2);
}
