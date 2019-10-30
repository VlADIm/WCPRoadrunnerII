#include <PID_v1.h>

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
#define carSpeed 100
 
#define Kp 1
#define Ki .04
#define Kd .01    

double Input, Output, Speed;
int L,R;
PID myPID(&Input, &Output, 0, Kp, Ki, Kd, DIRECT);


void setup() {
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
  pinMode(SignalA, INPUT);
  pinMode(SignalB, INPUT);
    //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-2,2);
}

void loop() {

linetrack();

}

void linetrack(){
  //If over white, scan left until finds line
  while(!LT_L && !LT_M && !LT_R){
    sweep();
  }
  
  //Map Sensors to X-Axis
  PIDinput();
  //Run PID 
  myPID.Compute();

  //Use PID Output to Define Left/ Right Motor Speeds
  if(Output>.99){
    L=0;R=180;
  }
  if(Output<.99&&Output>.4){
    L = 50; R=150;
  }
  if(Output<.4&&Output>-.4){
    L = carSpeed; R=carSpeed;
  }
  if(Output<-.4 && Output>-.99){
    L=150;R=50;
  }
  if(Output<-.99){
    L=180;R=0;
  }

  //Move the Robot
  drive(L,R);


void forward(){
  digitalWrite(RightMotorA, HIGH);
  digitalWrite(RightMotorB, LOW);
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(LeftMotorB, LOW);
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
}
 
double left(int Speed){
  digitalWrite(RightMotorA, HIGH);
  digitalWrite(RightMotorB, LOW);
  digitalWrite(LeftMotorA, LOW);
  digitalWrite(LeftMotorB, HIGH);
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
}
 
double right(int Speed){
  digitalWrite(RightMotorA, LOW);
  digitalWrite(RightMotorB, HIGH);
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(LeftMotorB, LOW); 
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
} 

double drive(int L, int R){
  digitalWrite(RightMotorA, HIGH);
  digitalWrite(RightMotorB, LOW);
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(LeftMotorB, LOW);
  analogWrite(ENA, R);
  analogWrite(ENB, L);
}




void sweep(){
  left(210);
}

void PIDinput(){
  if(!LT_L && !LT_M && LT_R){
    Input = 1;
  }
  else if(!LT_L && LT_M && LT_R) { 
    Input = .5;
  }                            
  else if(LT_L && LT_M && !LT_R) {
    Input = -.5; 
  }
  else if(LT_L && !LT_M && !LT_R) {
    Input = -1;  
  }
  else if(!LT_L && LT_M && !LT_R) {
    Input = 0;  
  }
  else{
    Input = 0;
  }  
}
