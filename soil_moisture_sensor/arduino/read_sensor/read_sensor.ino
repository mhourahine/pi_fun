int sensorPin = A0;    // select the input pin for the soil sensor
int ledPin = 13;      // select the pin for the LED
int currentValue = 0;
int previousValue = 0;  // variable to store the value coming from the sensor
float variance = 10.0; 
float MAX = 1023.0;
float MIN = 740.0;
float threshold = 920;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  // read the value from the moisture sensor:
  currentValue = analogRead(sensorPin);  

  
  //if changed, output sensor value to serial port for monitoring
  if (abs(currentValue-previousValue) > variance) {
    previousValue = currentValue;
    Serial.println(currentValue);  
  }
  
  // turn the ledPin on if moisture level is less than threshold
  if (currentValue > threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
         
}
