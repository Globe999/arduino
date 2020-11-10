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
bool objArr[arrSize];

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
  // doTurn(angle2go);

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

    objArr[i] = (distArr[i] < 100) ? true : false;
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
    if (!objArr[i])
    {
      continue;
    }
    int j = i;
    while (objArr[j]){
      j++;
    }
    objSize[arrIndex][0] = j - i;
    //Median angle
    objSize[arrIndex][1] = angles[int(i+(j-i)/2)];
    arrIndex++;
    i = j;

    // Serial.println(objArr[i]);
  }
  int smallIndex = 0;
  for (int i = 0; i < arrSize; i++)
  {
    if(objSize[smallIndex] > objSize[i]) smallIndex = i;
  }
  //Return angle of smallest object
  return objSize[smallIndex][1];
}

void turret(int degreeVal)
{
  servoTurret.write(degreeVal);
}

void doTurn(int angle){
  float constant = 1100/90; //How many ms it takes for each degree turn
  int inverted  = (angle < 90) ? true : false; //True if we turn to the left

  if (inverted) {
    float ms = (angle - 90) * constant;
    maneuver(50, -50, ms);
  } else {
    float ms = (90-angle) * constant;
    maneuver(-50, 50, ms);
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
