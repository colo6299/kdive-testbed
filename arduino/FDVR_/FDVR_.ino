// Bicep reads on analog pin 1, tripep reads on analog pin 0
//

int bicepPin = A1;
int tricepPin = A0;  

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
  if ((millis() % 500) < 15)
  {
    Serial.println(0);
    Serial.println(1000);
  }


  
  // test code to see ratios of sensors and identify possible interference
  Serial.println(bicepValue);
  Serial.println(tricepValue);
  delay(1);
}
