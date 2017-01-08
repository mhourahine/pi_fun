int sensorPin = A0;    // select the input pin for the soil sensor
int switchPin = 7;     // digital pin to turn soil sensor on / off
int ledPin = 13;       // select the pin for the LED
int currentValue = 0;
int previousValue = 0;  // variable to store the value coming from the sensor
int variance = 10; 
int MAX = 1023;  //highest value read by moisture sensor, maximum resistance in air)
int threshold = 930;  //from experimentation, reading when soil seems dry

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, OUTPUT);
  Serial.begin(9600);
}

int readSensor() {
  //turn on moisture sensor
  digitalWrite(switchPin, HIGH);
  delay(1000);
  
  // read the value from the moisture sensor:
  int val = analogRead(sensorPin);

  //turn off sensor  
  digitalWrite(switchPin,LOW);

  return val;
}

void loop() {
  currentValue = readSensor();
  Serial.println(currentValue);
  
  // turn the ledPin on if moisture level is less than threshold
  if (currentValue > threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  //delay 30s
  delay(30000);
}
