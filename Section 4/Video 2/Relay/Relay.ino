int relayPin1 = 23;
int relayPin2 = 19;

void setup() {
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
}

void loop() {
  digitalWrite(relayPin1, HIGH);
  delay(4000);
  digitalWrite(relayPin2, HIGH);
  delay(4000);
  digitalWrite(relayPin1, LOW);
  delay(4000);
  digitalWrite(relayPin2, LOW);
  delay(4000);
}
