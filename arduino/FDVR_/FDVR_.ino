// Bicep reads on analog pin 1, tripep reads on analog pin 0
//

int bicepPin = A1;
int tricepPin = A0;  

int lastTime = 0;
float armAngle = 0.0;
float armVelocity = 0.0;
const float amp = 1.0;
const float g = -9.81;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(19200);
}

// the loop routine runs over and over again forever:
void loop() {
  // just read in the EMG values from the myoware sensors
  int bicepValue = analogRead(bicepPin);
  int tricepValue = analogRead(tricepPin);

  // this is just debug code to change the auto-range on the
  //     arduino ide serial monitor...
  if ((millis() % 500) < 15)
  {
    Serial.println(0);
    Serial.println(1000);
    armVelocity += 1.0;
  }
  

  //so you know how much of a second passed for force calculations
  float deltaTime = (millis() - lastTime) / 1000;
  lastTime = millis();
  if (deltaTime < 0) {
    deltaTime = 0;
  }
  
  //this roughly simulates the effect of the real muscles on the virtual arm
  armVelocity += bicepValue - tricepValue * amp * deltaTime;
  
  
  //the cosine calculates the force gravity exerts on a pivot
  //    at a particular angle. 
  armVelocity += cos(armAngle) * g * deltaTime;
  armAngle += armVelocity * deltaTime;


  //stops for the arm, most of our elbows can't do 360's 
  /*
  if (armAngle <= 0) {
    armAngle = 0;
    if (armVelocity < 0) {
      armVelocity = 0;
    }
  }
  if (armAngle >= 1){
    armAngle = 1;
    armVelocity = 0;
  }*/
  
  //scale it up to look nice, and print!
  Serial.println(armAngle * 1000);

 
  delay(2);
}
