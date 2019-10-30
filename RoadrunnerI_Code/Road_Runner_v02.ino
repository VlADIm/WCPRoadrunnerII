//Line Tracking IO define
#define LT_R !digitalRead(2)
#define LT_M !digitalRead(3)
#define LT_L !digitalRead(4)
 
#define ENA 10
#define ENB 5
#define RightMotorA 9
#define LeftMotorA 8
#define RightMotorB 6
#define LeftMotorB 7

 
#define carSpeed 150
void colordetect(){

  
}

void forward(){
  digitalWrite(RightMotorA, HIGH);
  digitalWrite(LeftMotorA, LOW);
  digitalWrite(RightMotorB, HIGH);
  digitalWrite(LeftMotorB, LOW);
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
}
 
void back(){
  digitalWrite(RightMotorA, LOW);
  digitalWrite(LeftMotorA, LOW);
  digitalWrite(RightMotorB, HIGH);
  digitalWrite(LeftMotorB, HIGH);
  Serial.println("go back!");
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
}
 
void left(){
  digitalWrite(RightMotorA, HIGH);
  digitalWrite(LeftMotorA, LOW);
  digitalWrite(RightMotorB, LOW);
  digitalWrite(LeftMotorB, HIGH);
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
}
 
void right(){
  digitalWrite(RightMotorA, LOW);
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(RightMotorB, HIGH);
  digitalWrite(LeftMotorB, LOW); 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
} 
 
void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
} 

void linetrack() {
  if(LT_M && !LT_L && !LT_R){
    Serial.println("go forward!");
    while(LT_M && !LT_L && !LT_R){
      forward();
    }
  }
  else if(LT_R && !LT_M && !LT_L) {
    Serial.println("go right!"); 
    while(LT_R && !LT_M && !LT_L){
      right();
    }                            
  }   
  else if(LT_L && !LT_M && !LT_R) {
    Serial.println("go left!");
    while(LT_L && !LT_M && !LT_R){
      left();
    }  
  }
}
 
void setup(){
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
  Serial.println("LT_R");
//  Serial.println("LT_M");
//  Serial.println("LT_L");
  delay(2000);
}

void loop(){
  if(LT_M && !LT_L && !LT_R){
    Serial.println("go forward!");
    while(LT_M && !LT_L && !LT_R){
      forward();
    }
  }
  else if(LT_R && !LT_M && !LT_L) {
    Serial.println("go right!"); 
    while(LT_R && !LT_M && !LT_L){
      right();
    }                            
  }   
  else if(LT_L && !LT_M && !LT_R) {
    Serial.println("go left!");
    while(LT_L && !LT_M && !LT_R){
      left();
    }  
  }
}
  










 
