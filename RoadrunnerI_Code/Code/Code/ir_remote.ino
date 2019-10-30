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
#define carSpeed 140  

// Remote initiations 
#include <IRremote.h>
#define S 16712445  // STOP
#define UNKNOWN_S 4294967295  // STOP
#define RECV_PIN  13
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long val;
bool flag = LOW;


int Echo = A4;
int Trig = A5;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
  pinMode(SignalA, INPUT);
  pinMode(SignalB, INPUT);
  stop();
  irrecv.enableIRIn();
  delay(250);
}

void loop() {
  //stop(); //this is to make sure that the car is not moving while it is checking for obsticles 
  int D = Distance_test();
  //Serial.println(D);
  while (D<20){
    if (D<8){
//      back();
      delay(300);
    }
    stop();
    delay(250);
    D = Distance_test(); 
  }
 
// put your main code here, to run repeatedly:

if (irrecv.decode(&results)){ 
    val = results.value;
    Serial.println(val);
    irrecv.resume();
    switch(val){
      case S: 
      case UNKNOWN_S: flag = !flag; break;
      default: break;
    }
}
if(flag){
linetrack();
//Serial.println("test1");
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

void linetrack(){
  if ((SignalA == HIGH) && (SignalB == HIGH)){
    hardRight();
    Serial.print("Stop");
    return;
  }
  else {
    if ((SignalA == LOW) && (SignalB == HIGH)) { // if color not detected -- (Signal B received from color detect arduino) 
      if(LT_M && !LT_L && !LT_R){
        //while(LT_M && !LT_L && !LT_R){
          forward();
        //}
      }
      else if(LT_R && !LT_M && !LT_L) { 
        //while(LT_R && !LT_M && !LT_L){
          right();
        //} 
      }                            
      else if(LT_L && !LT_M && !LT_R) {
       // while(LT_L && !LT_M && !LT_R){
          left();  
        //}
      }
      else if(!LT_L && !LT_M && !LT_R){
        sweep();
        
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
  analogWrite(ENA, 210);
  analogWrite(ENB, 210);
}
 
void right(){
  digitalWrite(RightMotorA, LOW);
  digitalWrite(RightMotorB, HIGH);
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(LeftMotorB, LOW); 
  analogWrite(ENA, 210);
  analogWrite(ENB, 210);
} 

 
void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
   delay(1000);
} 

void hardRight () {
  forward();
  delay(1000);
 right();
  delay(1000);
  stop();
}

void hardLeft () {
  forward();
  delay(1000);
  left();
  delay(1000);
  return;
}


void sweep(){
  left();

  
}
