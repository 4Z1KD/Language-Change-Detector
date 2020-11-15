char inChar;
char status;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    // get the new byte:
    inChar = (char)Serial.read();
    if (inChar == 'e' || inChar == 'h' || inChar == 'j' )
    {
      status = inChar;
    }
    else if (inChar == 'z')
    {
      Serial.println("ok");
    }
  }

  switch (status)
  {
    case 'e':
      digitalWrite(2, HIGH);
      digitalWrite(13, LOW);
      break;
    case 'j':
      digitalWrite(2, LOW);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      break;
    case 'h':
      digitalWrite(2, LOW);
      digitalWrite(13, HIGH);
      break;
    default:
      break;
  }

}
