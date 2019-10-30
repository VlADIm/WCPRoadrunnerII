#include <PID_v1.h>
#include <Ultrasonic.h>

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
#define carSpeed 140 //120
#define turnSpeed 200
#define leftSpeed 230
#define sweepSpeed 195
 
#define Kp 1
#define Ki .03
#define Kd .01    


bool hasRun = false;
bool state = LOW;
char getstr;

int Echo = A5;
int Trig = A4;
 

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
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);
  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-2,2);
  
}

void loop() {
  int D = Distance_test();
  while (D<20){
    if (D<8){
      delay(300);
    }
    stop();
    delay(250);
    D = Distance_test(); 
  }
  
if (hasRun == false){
  start();
}
if(hasRun == true){
  linetrack();
}
  //}
}

void linetrack(){

  //If over white, scan left until finds line
  
  while(!LT_L && !LT_M && !LT_R){
    sweep();
  }

  if ((SignalA == HIGH) && (SignalB == HIGH)){
  stop();
   bluetooth_T();
  }


    

  //Use PID Output to Define Left/ Right Motor Speeds
  
  if ((SignalA == LOW) && (SignalB == HIGH)) {
    Serial.println("line tracking");

    //Map Sensors to X-Axis
    PIDinput();
    
    //Run PID 
    myPID.Compute();
    
    if(Output>.99){
      L=0;R=210;
    }
    if(Output<.99&&Output>.4){
      L = 30; R=190;
    }
    if(Output<.4&&Output>-.4){
      L = carSpeed; R= carSpeed;
    }
    if(Output<-.4 && Output>-.99){
      L=190;R=30;
    }
    if(Output<-.99){
      L=210;R=0;
    }
  
    //Move the Robot
    drive(L,R);
  }
//  if ((SignalA == HIGH) && (SignalB == HIGH)){
//    hardRight();
//    //stop();
//  }
  
  if ((SignalA == LOW)&& (SignalB == LOW)){
    stop();
     bluetooth_plus();
  }
  
  if ((SignalA == HIGH) && (SignalB == LOW)){
    return;
  }
  
   
}


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

void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
   delay(1000);
} 

void left_turn(){
  digitalWrite(RightMotorA, HIGH);
  digitalWrite(RightMotorB, LOW);
  digitalWrite(LeftMotorA, LOW);
  digitalWrite(LeftMotorB, HIGH);
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, leftSpeed);
}
 
void right_turn(){
  digitalWrite(RightMotorA, LOW);
  digitalWrite(RightMotorB, HIGH);
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(LeftMotorB, LOW); 
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
} 
void hardRight () {
  forward();
  delay(900);
  right_turn();
  delay(900); // previous 725
  stop();
}

void hardLeft () {
  forward();
  delay(900);
  left_turn();
  delay(400);
  return;
}

void sweep(){
  digitalWrite(RightMotorA, HIGH);
  digitalWrite(RightMotorB, LOW);
  digitalWrite(LeftMotorA, LOW);
  digitalWrite(LeftMotorB, HIGH);
  analogWrite(ENA, sweepSpeed);
  analogWrite(ENB, sweepSpeed);
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

void bluetooth_T(){
  getstr = Serial.read();
  Serial.println(getstr);
  if (getstr != NULL){
    switch(getstr){
      case 'R': hardRight(); break;
      case 'F': hardRight(); break;
      case 'L': hardLeft(); break;
      default:  break;
      getstr = NULL;
    }
  }
  else{
      getstr = Serial.read();
      return;
  }
}

void bluetooth_plus(){
  getstr = Serial.read();
  Serial.println(getstr);
  if (getstr != NULL){
    switch(getstr){
      case 'W': hardRight(); break;
      case 'C': forward(); break;
      case 'P': hardLeft(); break;
      default:  break;
      getstr = NULL;
    }
  }
  else{
      getstr = Serial.read();
      return;
  }
}

void start(){
  getstr = Serial.read();
  Serial.println(getstr);
  if (getstr != NULL){
    switch(getstr){
      case 'S':
        hasRun = true; 
        linetrack();
    }
  }
  else{
      getstr = Serial.read();
      return;
  }
  
}

int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       // distance is in cm
  return (int)Fdistance;
} 
