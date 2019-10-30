#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define S0 51
#define S1 49
#define S2 47
#define S3 45
#define sensorOut 53

#define SignalA 11
#define SignalB 12

#define ENC_A A1
#define ENC_B A2
int aLastState;
int aState;
int enc_counter = 0;
bool turn;


int COUNT=0; //count integer for 0-9 increment
LiquidCrystal_I2C lcd(0x27,20,4);

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
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  aLastState = digitalRead(ENC_A);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
detect();
encoder();
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
/*  Serial.print("R= ");//printing name
  Serial.print(redColor);//printing RED color frequency
 Serial.print("  ");
*/  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  greenFrequency = pulseIn(sensorOut, LOW); 
  greenColor = map(greenFrequency, 100, 199, 255, 0);
/*  Serial.print("G= ");//printing name
  Serial.print(greenColor);//printing RED color frequency
  Serial.print("  ");
*/
  
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency, 38, 84, 255, 0);
/* Serial.print("B= ");//printing name
  Serial.print(blueColor);//printing RED color frequency
 Serial.println();
*/

// void colordetect (redColor, blueCo lor, greenColor) { // MAKE FREQ AND COLOR DETECT ONE FUNCTION???

 if((redColor - blueColor) > 199){
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

void encoder()
{ aState = digitalRead(ENC_A); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (turn = 0);
   {
     if (aState != aLastState){     
       // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
       if (digitalRead(ENC_B) != aState) { 
         enc_counter ++;
       } 
       else {
         enc_counter ++;
       }
      }
   
   else if (turn = 1){
    enc_counter = enc_counter;
   }
   }
    aLastState = aState; 
    float DISP = ((1)*enc_counter)/259.7;
    Serial.println(DISP);
    lcd.setCursor(0,0);
    lcd.print("Distance =");
    lcd.setCursor(12,0);
    lcd.print(DISP);
    }
