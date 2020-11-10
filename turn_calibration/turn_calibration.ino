#include <Servo.h>

Servo servoLeft;
Servo servoRight;

const int servoLeftPin = 13;
const int servoRightPin = 12;

void setup()
{
    Serial.begin(9600);

    servoLeft.attach(servoLeftPin);   // Attach left signal to pin 13
    servoRight.attach(servoRightPin); // Attach right signal to pin 12


    maneuver(50, -50, 1050);
    maneuver(0,0,-1);
}

void loop()
{
}

void maneuver(int speedLeft, int speedRight, int ms)
{
    speedLeft = constrain(speedLeft, -110, 110); //Old servo on right, can max be 110 to have straight path
    speedRight = constrain(speedRight, -200, 200);
    servoLeft.writeMicroseconds(1500 + speedLeft);
    servoRight.writeMicroseconds(1500 - speedRight);
    if (ms == -1)
    {
        servoLeft.detach();
        servoRight.detach();
    }
    delay(ms);
}