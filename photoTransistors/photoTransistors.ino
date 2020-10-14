#include <Servo.h>

Servo servoLeft;
Servo servoRight;

void setup() {
  // put your setup code here, to run once:
  tone(4, 3000, 1000);
  delay(1000);
  Serial.begin(9600);

  servoRight.attach(13);
  servoLeft.attach(12);
}

void loop() {
  // put your main code here, to run repeatedly:
  float tLeft = float(rcTime(8));
  float tRight = float(rcTime(6));
  float ndShade;
  ndShade = tRight/(tLeft+tRight)-0.5;
  checkPath(ndShade);
}

void checkPath(float ndShade){
  int speedLeft, speedRight;
  if (ndShade > 0.0) {
    speedLeft = int(200.0 - (ndShade*1000.0));
    speedLeft = constrain(speedLeft, -200, 200);
    speedRight = 200;
  } else {
    speedRight = int(200.0 + (ndShade*1000.0));
    speedRight = constrain(speedRight, -200, 200);
    speedLeft = 200;
  }
  manouver(speedLeft, speedRight, 20);
}

long rcTime(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(1);
  pinMode(pin,INPUT);
  digitalWrite(pin, LOW);
  long time = micros();
  while(digitalRead(pin));
  time = micros() - time;
  return time;
}


void manouver(int speedLeft, int speedRight, int ms){
  speedLeft = constrain(speedLeft, -110, 110); //Old servo on right, can max be 110 to have straight path
  servoLeft.writeMicroseconds(1500 - speedLeft);
  servoRight.writeMicroseconds(1500 + speedRight);
  if(ms == -1) {
    servoLeft.detach();
    servoRight.detach();
  }
  delay(ms);
}
