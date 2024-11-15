// 5 way switch directions
const int pushPin = A0;
const int rightPin = A1;
const int leftPin = A2;
const int upPin = A3;
const int downPin = A4;

// output pins
const int awakePin = D8;
const int singlePressPin = D7;
const int rightOutput = D6;
const int leftOutput = D5;
const int upOutput = D4;
const int downOutput = D3;

// status vars
bool isAwake = false;
unsigned long buttonPressTime = 0;
const unsigned long longPressDuration = 1000; // 1 second to awake the nano

void setup() {
  // setup pins as input pullup
  pinMode(pushPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);

  // setup output pins
  pinMode(awakePin, OUTPUT);
  pinMode(singlePressPin, OUTPUT);
  pinMode(rightOutput, OUTPUT);
  pinMode(leftOutput, OUTPUT);
  pinMode(upOutput, OUTPUT);
  pinMode(downOutput, OUTPUT);

  // set all outputs to LOW
  digitalWrite(awakePin, LOW);
  digitalWrite(singlePressPin, LOW);
  digitalWrite(rightOutput, LOW);
  digitalWrite(leftOutput, LOW);
  digitalWrite(upOutput, LOW);
  digitalWrite(downOutput, LOW);
}

void loop() {
  // get up bb  (checks if the central button is being pressed for the given time)
  handlePushButton();

  // only checks if it's awake duh
  if (isAwake) {
    if (digitalRead(rightPin) == LOW) {
      triggerOutput(rightOutput);
    }
    if (digitalRead(leftPin) == LOW) {
      triggerOutput(leftOutput);
    }
    if (digitalRead(upPin) == LOW) {
      triggerOutput(upOutput);
    }
    if (digitalRead(downPin) == LOW) {
      triggerOutput(downOutput);
    }
  }
}

// handles the central button (A0)
void handlePushButton() {
  if (digitalRead(pushPin) == LOW) {
    if (buttonPressTime == 0) {
      buttonPressTime = millis(); // start counting
    }

    // if pressed long enough
    if (millis() - buttonPressTime >= longPressDuration) {
      if (isAwake) {
        // if awake then sleep
        isAwake = false;
        digitalWrite(awakePin, LOW); 
      } else {
        // if aslep then wake up
        isAwake = true;
        digitalWrite(awakePin, HIGH);
      }
      delay(300); // Debounce semplice
    }
  } else {
    // if pressed long enough
    if (buttonPressTime > 0 && millis() - buttonPressTime < longPressDuration) {
      if (isAwake) {
        // if awake, output in A0 pin
        triggerOutput(singlePressPin);
      }
    }
    buttonPressTime = 0; // timer reset
  }
}

// handles each direction
void triggerOutput(int pin) {
  digitalWrite(pin, HIGH);
  delay(200); // keep output for 200ms
  digitalWrite(pin, LOW);
}
