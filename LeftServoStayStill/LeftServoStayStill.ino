#include <Servo.h> //Include servo library
Servo servoLeft;
Servo servoRight;
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

const int buzzerPin = 4;
const int ledPin1 = 11;
const int ledPin2 = 10;

int counter = 0;

void setup() {
  //Init servos
  Serial.begin(9600);
  attachServos(13,12);

  //Init pin and sound
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  delay(500);
  makeZ();

}

void makeZ(){
  //Start Z sequence
  forward(900);
  turnRight(1400);
  forward(2250);
  turnLeft(1290);
  forward(1600);
  stopRoll(300);
  turnOnCoin(false, 1140);
  stopRoll(0);
  delay(500);
  playMusic();
  delay(500);
  forward(1600);
  turnRight(1400);
  forward(2100);
  turnLeft(1300);
  forward(1400);
  stopRoll(0);
  detachServos();
}
void loop() {
  // put your main code here, to run repeatedly:

}

void forward(int i) {
  servoLeft.writeMicroseconds(1610);
  servoRight.writeMicroseconds(1300);
  delay(i);
}
void backwards(int i) {
  servoLeft.writeMicroseconds(1390);
  servoRight.writeMicroseconds(1700);
  delay(i);
}

void turnRight(int i) {
  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1500);
  delay(i);
}

void turnLeft(int i) {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1300);
  delay(i);
}

void stopRoll(int i) {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(i);
}

void turnOnCoin(bool rev, int i){
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
void detachServos() {
  servoRight.detach();
  servoLeft.detach();
}

void attachServos(int left, int right){
  servoLeft.attach(left);
  servoRight.attach(right);
}


void playMusic() {
  firstSection();
  secondSection();
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 350);  
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);  
  beep(cH, 125);
  beep(eH, 650);
  delay(500);

  secondSection();
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  
  delay(650);
}

void beep(int note, int duration){
  tone(buzzerPin, note, duration);  //Play different LED depending on value of 'counter'
  
  if(counter % 2 == 0){
    digitalWrite(ledPin1, HIGH);
    delay(duration);
    digitalWrite(ledPin1, LOW);
  }
  else{
    digitalWrite(ledPin2, HIGH);
    delay(duration);
    digitalWrite(ledPin2, LOW);
  }
  
  noTone(buzzerPin);  //Stop tone on buzzerPin
  delay(50);
  counter++;  //Increment counter
}

void firstSection(){
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
  delay(500);

  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
  delay(500);
}

void secondSection(){
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 150);
  beep(fSH, 90);
  beep(fH, 90);    
  beep(fSH, 250); 
  delay(325);
  
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 150);  
  beep(cH, 90);  
  beep(b+25, 90);  
  beep(cH, 250);  
  delay(350);
}
