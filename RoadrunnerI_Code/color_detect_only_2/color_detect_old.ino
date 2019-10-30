#define S0 51
#define S1 49
#define S2 47
#define S3 45
#define sensorOut 53

#define SignalA 11
#define SignalB 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(SignalA, OUTPUT);
  pinMode(SignalB, OUTPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
detect();
}

  
void detect(){
  
  // Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;


// Stores the red green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  redFrequency = pulseIn(sensorOut, LOW);
  redColor = map(redFrequency, 70, 120, 255,0);
  Serial.print("R= ");//printing name
  Serial.print(redColor);//printing RED color frequency
 Serial.print("  ");
  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  greenFrequency = pulseIn(sensorOut, LOW); 
  greenColor = map(greenFrequency, 100, 199, 255, 0);
 Serial.print("G= ");//printing name
  Serial.print(greenColor);//printing RED color frequency
  Serial.print("  ");

  
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency, 38, 84, 255, 0);
 Serial.print("B= ");//printing name
  Serial.print(blueColor);//printing RED color frequency
 Serial.println();


// void colordetect (redColor, blueCo lor, greenColor) { // MAKE FREQ AND COLOR DETECT ONE FUNCTION???

 if((redColor - greenColor) > 80){
  // T intersection detected
  // send signal A & B high
  digitalWrite(SignalA, HIGH);
  digitalWrite(SignalB, HIGH);
 Serial.print("red");
 Serial.println();
  
 }
 else if((greenColor - redColor) > 199)  {
  // + intersection detected
  // send signal A and B low to line tracking arduino
  digitalWrite(SignalA, LOW);
  digitalWrite(SignalB, LOW);
 Serial.print("green");
 Serial.println();
 }
 else{
  //send signal A low signal B high to line tracking arduino
  digitalWrite(SignalA, LOW);
  digitalWrite(SignalB, HIGH);
  Serial.print("nothing");
  Serial.println();
  return;
}
}
