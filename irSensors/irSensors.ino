void setup() {
//  tone(4, 3000, 1000);
  delay(1000);

  pinMode(10, INPUT); pinMode(9, OUTPUT);
  pinMode(3, INPUT); pinMode(2, OUTPUT);
  pinMode(8, OUTPUT); pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int irLeft = irDetect(9, 10, 38000);
  int irRight = irDetect(2, 3, 38000);

  digitalWrite(8, !irLeft);
  digitalWrite(7, !irRight);
  
  Serial.println();
  Serial.print(irLeft);
  Serial.print(irRight);
}

int irDetect(int irLedPin, int irReceiverPin, long freq) {
  tone(irLedPin, freq, 8);
  delay(1);
  int ir = digitalRead(irReceiverPin);
  delay(1);
  return ir;
}
