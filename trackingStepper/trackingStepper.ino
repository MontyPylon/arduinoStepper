int dirpin = 2;
int steppin = 3;
int speed = 4000;

void setup() 
{
pinMode(dirpin, OUTPUT);
pinMode(steppin, OUTPUT);
}
void loop()
{

  int i;

  //digitalWrite(dirpin, LOW);     // Set the direction.
  //delay(100);


  for (i = 0; i<1600; i++)       // Iterate for 4000 microsteps.
  {
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(speed);    // This delay time is close to top speed for this
  }                              // particular motor. Any faster the motor stalls.
  delay(2000);
}
