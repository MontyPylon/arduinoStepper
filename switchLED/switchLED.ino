int switchPin = 5;
int switchPin2 = 6;
int ledPin = 7;
int ledPin2 = 8;

int switchState = 0;
int switchState2 = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);  
  
  // initialize the switch pin as an input:
  pinMode(switchPin, INPUT);
  pinMode(switchPin, INPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(switchPin);
  switchState2 = digitalRead(switchPin2);

  test();
}

void test() {
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (switchState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
  
  if (switchState2 == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin2, HIGH);  
  } else {
    // turn LED off:
    digitalWrite(ledPin2, LOW); 
  }
  
}
