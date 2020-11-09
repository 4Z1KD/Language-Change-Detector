char inChar;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (inChar == 'e')
  {
    digitalWrite(2, HIGH);
    digitalWrite(13, LOW);
  }
  else if (inChar == 'h')
  {
    digitalWrite(2, LOW);
    digitalWrite(13, HIGH);
  }
  else if (inChar == 'z')
  {
    Serial.println("ok");
  }
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    inChar = (char)Serial.read();
  }
}
