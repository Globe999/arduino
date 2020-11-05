#include <Servo.h>
Servo servoLeft;
Servo servoRight;
int rightMultiplier = 1;
int leftMultiplier = 1;

const int ledPin1 = 7; //Right indicator
const int ledPin2 = 8; //Left indicator

void setup() {
  pinMode(10, INPUT); pinMode(9, OUTPUT);
  pinMode(3, INPUT); pinMode(2, OUTPUT);
  pinMode(ledPin2, OUTPUT); pinMode(ledPin1, OUTPUT);
  Serial.begin(9600);
  attachServos(13, 12);
  delay(1000);
  //Init moving
  manouver(200, 200, 20);
}

void loop() {
  if (volts(A4) > 1) {
    blinkLed();
    manouver(0,0,-1);
  }
  
  int irLeft = irDetect(9, 10, 38000);
  int irRight = irDetect(2, 3, 38000);
  int speedLeft, speedRight;

  if (irLeft) {
    digitalWrite(ledPin2, LOW);
    if (irRight) {
      digitalWrite(ledPin1, LOW);
      rightMultiplier++;
      leftMultiplier = 1;
    } else {
      digitalWrite(ledPin1, HIGH);
      leftMultiplier++;
      rightMultiplier = 1;
    }
  } else {
    digitalWrite(ledPin2, HIGH);
    leftMultiplier++;
    rightMultiplier = 1;
  }
  Serial.println();
  Serial.print("LEFT: ");
  Serial.print(int(leftMultiplier/10));
  Serial.print(" RIGHT: ");
  Serial.print(int(rightMultiplier/10));
  Serial.println();
  //If object straight ahead, turn left
  if (irLeft == 0) {
    speedLeft = (200 - (100 + leftMultiplier*5));
    speedRight = 200;
    Serial.println("OBJECT DETECTED AHEAD");

  } else if (irRight == 0) {
    speedLeft = (200 - (100 + leftMultiplier * 5));
    speedRight = 200;
    Serial.println("Wall to the right detected, turn left.");

  } else if (irRight == 1) {
    Serial.println("No wall to the right detected, turn right");
    //Not detecting wall, turn slightly to the right
    speedLeft = 200;
    speedRight = (200 - (100 + rightMultiplier *5));

  } else {
    speedLeft = 200, speedRight = 200;
  }
  manouver(speedLeft, speedRight, 20);
}

void manouver(int speedLeft, int speedRight, int ms) {
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


void stopRoll(int i) {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
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

int irDetect(int irLedPin, int irReceiverPin, long freq) {
  tone(irLedPin, freq, 8);
  delay(1);
  int ir = digitalRead(irReceiverPin);
  delay(1);
  return ir;
}

float volts(int adPin) {
  return float(analogRead(adPin)*5/1024);
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
