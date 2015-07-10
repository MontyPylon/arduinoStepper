int steppin = 2;
int dirpin = 3;
int MS1 = 5;
int MS2 = 4;
int EN = 6;
int speedStep = 128000;

int oneRev = 4800; // 4,800 steps per revolution with 1/8th steps
int currentStep = 0; // Where the stepper motor is right now
int directionStep = 0;  // 0 is down, 1 is up
double angle = 0; // angle of the LiDAR sensor
bool switchDirection = false;

int startByte = 0;
int takeStepByte = 0;
bool start = false;
bool takeStep = false;

void setup()
{
  Serial.begin(9600);
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  //digitalWrite(dirpin, LOW);
  digitalWrite(EN, LOW);
  
  // This places the Easy Driver into 1/8th steps
  digitalWrite(dirpin, HIGH);
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  
  delay(1000);
}

void loop()
{
  if(!start) {
    startListener();
    // Will not continue until start gets the number 1 from the python program
  } else {
    takeStepListener();
    //Will not continue until we can a takeStep command (#3) from python program
    if(takeStep) {
      //Serial.println("Will now move a step");
      moveStep();
      takeStep = false;
      // Finished taking our step and returning the angle
      // which is signified by the number 4
      Serial.println("F");
    }
  }
  
  // TODO: Toggle an LED so we can verify the Arduino hasn't crashed
}

void startListener() {
  if(Serial.available() > 0) {
//    Serial.println("Inside start listener");
    startByte = Serial.read() - '0';
    if(startByte == 5) {
      //continue
      Serial.println("T");
      start = true;
      // Received the start command, and will now execute the main loop
    } 
  }
}

void takeStepListener() {
  if(Serial.available() > 0) {
    
    takeStepByte = Serial.read() - '0';
    
    if(takeStepByte == 3) {
      //continue
      //Serial.println("Take a step");
      takeStep = true;
    } else {
      return; 
    }
  } 
}

void moveStep() {
  
  if(currentStep < 1200 && directionStep == 0) {
    currentStep += 1;
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(speedStep); 
    
    if(currentStep == 1200) {
      directionStep = 1;
      switchDirection = true;
      digitalWrite(dirpin, LOW);
    }
    
  } else if(currentStep > 0 && directionStep == 1) {
    currentStep -= 1;
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(speedStep); 
    
    if(currentStep == 0) {
      directionStep = 0; 
      switchDirection = true;
      digitalWrite(dirpin, HIGH);
    }
    
  }
  
  angle = ((double) currentStep / (double) oneRev) * 360;
  Serial.print("AA");
  Serial.println(angle);
  
  if(switchDirection) {
    //delay(1000);
    switchDirection = false; 
  }
}
