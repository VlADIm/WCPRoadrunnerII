//Line Tracking IO define
#define LT_R !digitalRead(2)
#define LT_M !digitalRead(3)
#define LT_L !digitalRead(4)
 
#define ENA 10
#define ENB 5
#define RightMotorA 9
#define RightMotorB 8
#define LeftMotorA 6
#define LeftMotorB 7
#define SignalA digitalRead(11)
#define SignalB digitalRead(12)
#define carSpeed 180  



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
  pinMode(SignalA, INPUT);
  pinMode(SignalB, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
linetrack();
}

void linetrack(){
  if ((SignalA == LOW) && (SignalB == HIGH)) { // if color not detected -- (Signal B received from color detect arduino) 
    if(LT_M && !LT_L && !LT_R){
      while(LT_M && !LT_L && !LT_R){
        forward();
      }
    }
    else if(LT_R && !LT_M && !LT_L) { 
      while(LT_R && !LT_M && !LT_L){
        right();
      } 
    }                            
    else if(LT_L && !LT_M && !LT_R) {
      while(LT_L && !LT_M && !LT_R){
        left();  
      }
    }
  }

  
  if ((SignalA == HIGH) && (SignalB == HIGH)){
    hardRight();
  }

  if ((SignalA == LOW)&& (SignalB == LOW)){
    hardLeft();
  }

  if ((SignalA == HIGH) && (SignalB == LOW)){
    return;
  }
}


  // motor functions

void forward(){
  digitalWrite(RightMotorA, HIGH);
  digitalWrite(RightMotorB, LOW);
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(LeftMotorB, LOW);
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
}
 
void left(){
  digitalWrite(RightMotorA, HIGH);
  digitalWrite(RightMotorB, LOW);
  digitalWrite(LeftMotorA, LOW);
  digitalWrite(LeftMotorB, HIGH);
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
}
 
void right(){
  digitalWrite(RightMotorA, LOW);
  digitalWrite(RightMotorB, HIGH);
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(LeftMotorB, LOW); 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
} 
 
void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
} 

void hardRight () {
  right();
  delay(1500);
  return;
}

void hardLeft () {
  left();
  delay(1500);
  return;
}
