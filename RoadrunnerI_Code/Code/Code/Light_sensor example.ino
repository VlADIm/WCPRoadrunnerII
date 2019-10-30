/*
Author: Danny van den Brande, Arduinosensors.nl. Bluecore Tech
in this example i show you how to use the KY-033 as a white line tracer.
 */
int WhiteLed = 2; 
int Sensor = A5; 
int sensorValue = 0; 

void setup () {
  pinMode (WhiteLed, OUTPUT);
  Serial.begin (9600);
}
void loop () {
  sensorValue = analogRead (Sensor);
  if (sensorValue < 50&& sensorValue < 500) 
  {
  digitalWrite (WhiteLed, HIGH);
  Serial.println (sensorValue, DEC);
  }
  else (sensorValue > 500&& sensorValue > 1023);
  { 
  digitalWrite (WhiteLed, LOW);
  Serial.println (sensorValue, DEC);
  }
}
