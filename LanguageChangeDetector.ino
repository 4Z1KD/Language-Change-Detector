String command;

const int HebrewPIN = 2;    // Hebrew button pin #
const int EnglishPIN = 3;    // English button pin #

const int HebrewLED = 4;    // Hebrew LED pin #
const int EnglishLED = 13;   // English LED pin #

const int blinkDelay = 500; //delay between LED on/off state
const int bounceThreshold = 250; //the threshold time in ms of the button bounce prevent logics

bool isBlink = false; //a flag for blink state (if true, the Hebrew LED will blink)


void setup() {
  //set pins mode: LEDs are outputs, buttons are input
  pinMode(HebrewLED, OUTPUT);
  pinMode(EnglishLED, OUTPUT);
  pinMode(HebrewPIN, INPUT_PULLUP);
  pinMode(EnglishPIN, INPUT_PULLUP);

  //Register to interrupts
  attachInterrupt(digitalPinToInterrupt(HebrewPIN), SelectHebrew, FALLING);
  attachInterrupt(digitalPinToInterrupt(EnglishPIN), SelectEnglish, FALLING);

  Serial.begin(9600); //open a serial port
  Serial.setTimeout(100); //set timeout
}

void loop() {
  //check if a command is waiting, if it is, read it and trim the '/r'
  while (Serial.available()) {
    command = Serial.readStringUntil(';');
    command.trim();
  }

  //if it is 'eng' -> cancel blink, and set the language LED states
  if (command == "eng")
  {
    isBlink = false;
    digitalWrite(HebrewLED, LOW);
    digitalWrite(EnglishLED, HIGH);
  }
  //if it is 'eng' -> cancel blink, and set the language LED states
  else if (command == "heb")
  {
    isBlink = false;
    digitalWrite(HebrewLED, HIGH);
    digitalWrite(EnglishLED, LOW);
  }
  //if it is 'blink' -> set blink flag to true
  else if (command == "blink")
  {
    isBlink = true;
  }
  //if it is 'handshake' -> return 'ok'
  else if (command == "handshake")
  {
    Serial.println("ok");
  }

  //if blink state is on -> turn eng LED off, and call blinkLED
  if (isBlink)
  {
    digitalWrite(EnglishLED, LOW);
    blinkLED(HebrewLED);
  }

  //reset command
  command = "";
}


void SelectHebrew()
{
  static unsigned long last_ToggleModeInterrupt_time = 0;
  unsigned long toggleModeInterrupt_time = millis();
  // If interrupts come faster than 500ms, assume it's a bounce and ignore
  if (toggleModeInterrupt_time - last_ToggleModeInterrupt_time > bounceThreshold)
  {
    command = "";
    Serial.println("he-IL");
  }
  last_ToggleModeInterrupt_time = toggleModeInterrupt_time;
}
void SelectEnglish()
{
  static unsigned long last_ToggleModeInterrupt_time = 0;
  unsigned long toggleModeInterrupt_time = millis();
  // If interrupts come faster than 500ms, assume it's a bounce and ignore
  if (toggleModeInterrupt_time - last_ToggleModeInterrupt_time > bounceThreshold)
  {
    command = "";
    Serial.println("en-US");
  }
  last_ToggleModeInterrupt_time = toggleModeInterrupt_time;
}

void blinkLED(int led) {
  static byte heartState = 1;
  static unsigned long previousBeat = millis();
  unsigned long currentMillis = millis();
  if (currentMillis - previousBeat >= blinkDelay) {
    previousBeat = currentMillis;
    heartState ^= 1;
    digitalWrite(led, heartState);
  }
}
