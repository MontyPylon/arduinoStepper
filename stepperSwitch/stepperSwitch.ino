//PINS
int dirpin = 2;
int steppin = 3;
int switchPin = 5;
int switchPin2 = 6;
int ledPin = 7;
int ledPin2 = 8;

//vars
int speed = 500;
int switchState = 0;
int switchState2 = 0;
int direction = 0;
bool directionSwitched1 = false;
int counter = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  digitalWrite(dirpin, LOW);     // Set the direction.
  
}
void loop()
{
  switchState = digitalRead(switchPin);
  switchState2 = digitalRead(switchPin2);

  //direction = 0;

  motorSwitch();

}

void motorSwitch() {
  
  digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
  digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
  
  while(counter < 500) {
    if (switchState == HIGH && directionSwitched1 == false) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      directionSwitched1 = true;
      switchDirection();
      Serial.println("Switch turned on");
  
    } else if (directionSwitched1 == true && switchState == LOW) {
      // turn LED off:
      digitalWrite(ledPin, LOW);
      directionSwitched1 = false;
      Serial.println("Switch turned off");
    }
    /**
    if (direction == 0) {
      digitalWrite(dirpin, LOW);
    } else if (direction == 1) {
      digitalWrite(dirpin, HIGH);
    }
    **/
    counter++;
  }
  
  counter = 0;
  
  /**
  if (switchState2 == HIGH) {
    // turn LED on:
    digitalWrite(ledPin2, HIGH);
    switchDirection();
  } else {
    // turn LED off:
    digitalWrite(ledPin2, LOW);
  }
  **/

}

void switchDirection() {
  if (direction == 0) {
    direction = 1;
    digitalWrite(dirpin, HIGH);
  } else {
    direction = 0;
    digitalWrite(dirpin, LOW);
  }
}
