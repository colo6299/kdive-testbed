// Bicep reads on analog pin 1, tripep reads on analog pin 0
//

int bicepPin = A1;
int tricepPin = A0;  

int lastTime = 0;
float armAngle = 0.0f;
float armVelocity = 0.0f;
const float g = -9.81;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // just read in the EMG values from the myoware sensors
  int bicepValue = analogRead(bicepPin);
  int tricepValue = analogRead(tricepPin);

  // this is just debug code to fix the auto-range on the
  //     arduino ide serial monitor...

  /*
  if ((millis() % 500) < 15)
  {
    Serial.println(0);
    Serial.println(1000);
  }
  */

  //so you know how much of a second passed for force calculations
  float deltaTime = (millis() - lastTime) / 1000;
  lastTime = millis();
  if (deltaTime < 0) {
    deltaTime = 0;
  }
  
  //the cosine calculates the force gravity exerts on a pivot
  //    at a particular angle. 
  armVelocity = cos(armAngle) * g * deltaTime;
  armAngle -= armVelocity * deltaTime;


  //stops for the arm, most of our elbows can't do 360's
  if (armAngle <= 0) {
    armAngle = 0;
    armVelocity = 0;
  }
  if (armAngle >= 1){
    armAngle = 1;
    armVelocity = 0;
  }

  Serial.println(int(armAngle) * 1000);

 
  delay(1);
}
