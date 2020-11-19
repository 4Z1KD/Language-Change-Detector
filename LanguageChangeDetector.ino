char inChar;
char status;

const int HebrewPIN = 2;    // the number of the hebrew pin
const int EnglishPIN = 3;    // the number of the english pin

const int HebrewLED = 4;    // the number of the hebrew led
const int EnglishLED = 13;   // the number of the english

void setup() {
  pinMode(HebrewLED, OUTPUT);
  pinMode(EnglishLED, OUTPUT);
  pinMode(HebrewPIN, INPUT_PULLUP);
  pinMode(EnglishPIN, INPUT_PULLUP);
  
  //Register to interrupts
  attachInterrupt(digitalPinToInterrupt(HebrewPIN), SelectHebrew, FALLING);
  attachInterrupt(digitalPinToInterrupt(EnglishPIN), SelectEnglish, FALLING);
  
  //set the interrupt msk
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT2); //Interrupt on pin10
  PCMSK0 |= (1 << PCINT3); //Interrupt on pin11
  
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
      digitalWrite(HebrewLED, HIGH);
      digitalWrite(EnglishLED, LOW);
      break;
    case 'j':
      digitalWrite(HebrewLED, LOW);
      digitalWrite(EnglishLED, HIGH);
      delay(500);
      digitalWrite(EnglishLED, LOW);
      delay(500);
      break;
    case 'h':
      digitalWrite(HebrewLED, LOW);
      digitalWrite(EnglishLED, HIGH);
      break;
    default:
      break;
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
