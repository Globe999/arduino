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

void setup()
{
  Serial.begin(9600);
  Serial.println("This is a test");

  servoLeft.attach(servoLeftPin);   // Attach left signal to pin 13
  servoRight.attach(servoRightPin); // Attach right signal to pin 12
  servoTurret.attach(servoTurretPin);

  for (int i = 0; i <= arrSize; i++)
  {
    angles[i] = i + 20;
  }

  turret(0); //Set turret to 90
  delay(1000);
  scan();
  delay(1000);
  int angle2go = evalData();
  Serial.print("Angle to go: ");
  Serial.println(angle2go);
  delay(1000);
  test(angle2go);
  delay(1000);
  // while (ping(pingPin) > 10) {
  //   maneuver(200, 200, 1);
  // }
}

void loop()
{
  // put your main code here, to run repeatedly:
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

void scan()
{
  for (int i = 0; i < arrSize; i++)
  {
    turret(angles[i]);
    delay(5);
    distArr[i] = ping(pingPin);
    delay(50);
  }
  turret(90);
}

//Evaluates distances to analyze objects
int evalData()
{
  int objSize[arrSize][2];
  int arrIndex = 0;
  for (int i = 0; i < arrSize; i++)
  {
    if (distArr[i] > 120)
    {
      continue;
    }
    int j = i;
    while (distArr[j] <= 120)
    {
      j++;
    }
    objSize[arrIndex][0] = j - i;
    Serial.print("Size: ");
    Serial.println(objSize[arrIndex][0]);
    //Median angle
    objSize[arrIndex][1] = angles[i + ((j - i) / 2)];
    Serial.print("Angle: ");
    Serial.println(objSize[arrIndex][1]);
    arrIndex++;
    //Skip to next section
    i = j + 1;
  }
  int smallest = objSize[0][0];
  int angle = objSize[0][1];
  for (int i = 0; i < arrIndex; i++)
  {
    if (smallest > objSize[i][0])
    {
      smallest = objSize[i][0];
      angle = objSize[i][1];
    }
  }
  return angle;
}

void turret(int degreeVal)
{
  servoTurret.write(degreeVal);
}

void test(int angle)
{
  float constant = 1100 / 90;                 //How many ms it takes for each degree turn
  if (angle < 90) 
  {
    servoLeft.writeMicroseconds(1550);
    servoRight.writeMicroseconds(1550);
  } else
  {
    servoLeft.writeMicroseconds(1450);
    servoRight.writeMicroseconds(1450);
  }
}

long ping(int pin)
{
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

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / (29 * 2);
}
