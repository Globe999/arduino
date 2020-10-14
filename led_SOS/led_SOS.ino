
void setup() {
  Serial.begin(9600);
  //Init pin 13 & 12 as output)
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  exec_sos();
}
void loop() {
  //Nothing here
}
void exec_sos() {
  //Excec sos func 3 times with different delays
  for (int i = 0; i < 3; i++) {
    sos(300);
    delay(500);
    sos(900);
    delay(500);
    sos(300);
    delay(1000);
  }
}

//ms takes delay in milliseconds
void sos(int ms) {
  for (int i = 0; i < 3; i++) {
    on(13);
    on(12);
    delay(ms);
    off(13);
    off(12);
    delay(ms);
  }
}

void on(int pin) {
  digitalWrite(pin, HIGH);
}

void off(int pin) {
  digitalWrite(pin, LOW);
}
