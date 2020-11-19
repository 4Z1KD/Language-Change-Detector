String command;

const int HebrewPIN = 2;    // the number of the hebrew pin
const int EnglishPIN = 3;    // the number of the english pin

const int HebrewLED = 4;    // the number of the hebrew led
const int EnglishLED = 13;   // the number of the english

void setup() {
  //set pins mode: LEDs are outputs, buttons are input
  pinMode(HebrewLED, OUTPUT);
  pinMode(EnglishLED, OUTPUT);
  pinMode(HebrewPIN, INPUT_PULLUP);
  pinMode(EnglishPIN, INPUT_PULLUP);

  //Register to interrupts
  attachInterrupt(digitalPinToInterrupt(HebrewPIN), SelectHebrew, FALLING);
  attachInterrupt(digitalPinToInterrupt(EnglishPIN), SelectEnglish, FALLING);

  Serial.begin(9600);
  Serial.setTimeout(100);
}

void loop() {
  while (Serial.available()) {
    // get the new byte:
    command = Serial.readStringUntil(';');
    if (command == "eng")
    {
      digitalWrite(HebrewLED, HIGH);
      digitalWrite(EnglishLED, LOW);
    }
    else if (command == "blink")
    {
      digitalWrite(HebrewLED, LOW);
      digitalWrite(EnglishLED, HIGH);
      delay(500);
      digitalWrite(EnglishLED, LOW);
      delay(500);
    }
    else if (command == "heb")
    {
      digitalWrite(HebrewLED, LOW);
      digitalWrite(EnglishLED, HIGH);
    }
    else if (command == "handshake")
    {
      Serial.println("ok");
    }
  }
}
void SelectHebrew()
{
  static unsigned long last_ToggleModeInterrupt_time = 0;
  unsigned long toggleModeInterrupt_time = millis();
  // If interrupts come faster than 100ms, assume it's a bounce and ignore
  if (toggleModeInterrupt_time - last_ToggleModeInterrupt_time > 500)
  {
    Serial.println("he-IL");
  }
  last_ToggleModeInterrupt_time = toggleModeInterrupt_time;
}
void SelectEnglish()
{
  static unsigned long last_ToggleModeInterrupt_time = 0;
  unsigned long toggleModeInterrupt_time = millis();
  // If interrupts come faster than 100ms, assume it's a bounce and ignore
  if (toggleModeInterrupt_time - last_ToggleModeInterrupt_time > 500)
  {
    Serial.println("en-US");
  }
  last_ToggleModeInterrupt_time = toggleModeInterrupt_time;
}
