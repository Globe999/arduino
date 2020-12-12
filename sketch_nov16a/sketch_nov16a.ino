#include <Servo.h>

Servo servoLeft;
Servo servoRight;
Servo servoTurret;

const int servoLeftPin = 13;
const int servoRightPin = 12;
const int servoTurretPin = 11;
const int pingPin = 10;
unsigned int duration, centimeters;
int pos = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);
  servoTurret.attach(servoTurretPin);

  //maneuver(200, 200, 2);

  //Nu scannar du bara 90 grader, kör 180 för att få halvcirkeln
  while (pos < 90 and pos >= 0)
  {
    int firstAngle, secondAngle;

    //Sät position först, scanna sen
    servoTurret.write(pos);
    int cm = distance();
    //Om vi inte hittar ett object, continue -> den går till nästa loop
    if (cm > 20)
    {
      pos += 1;
      continue;
    }
    else
    {
      //Vi har hittat ett objekt, kolla nästa position
      int startPos = pos;
      int startCm = cm;
      //Om nästa mätning är mindre än 5cm från den första, räkna det som samma objekt
      while (abs(cm - startCm < 5))
      {
        pos++;
        servoTurret.write(pos);
        int cm = distance();
      }
      int size = startPos-pos;
    }
  }

  pos = 35;
  servoTurret.write(pos);
}
void loop()
{
  // put your main code here, to run repeatedly:
}

void maneuver(int speedLeft, int speedRight, int msTime)
{
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
  if (msTime == -1)                                // if msTime = -1
  {
    servoLeft.detach(); // Stop servo signals
    servoRight.detach();
  }
  delay(msTime); // Delay for msTime
}

void findObject()
{
}

int distance()
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  centimeters = duration / 29 / 2;
  delay(200);
  return centimeters;
}
