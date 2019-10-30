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
#define carSpeed 130  


bool state = LOW;
char getstr;


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
  analogWrite(ENA, 190);
  analogWrite(ENB, 190);
}
 
void right(){
  digitalWrite(RightMotorA, LOW);
  digitalWrite(RightMotorB, HIGH);
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(LeftMotorB, LOW); 
  analogWrite(ENA, 190);
  analogWrite(ENB, 190);
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
  delay(725);
  stop();
}

void hardLeft () {
  forward();
  delay(1100);
  left();
  delay(725);
  return;
}


void sweep(){
  left();
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
Serial.println("test1");
}

void linetrack(){
  if ((SignalA == HIGH) && (SignalB == HIGH)){
    stop();
    bluetooth_T();   
}
  else {
    if ((SignalA == LOW) && (SignalB == HIGH)) { // if color not detected -- (Signal B received from color detect arduino) 
      if(LT_M && !LT_L && !LT_R){
          forward();
      }
      else if(LT_R && !LT_M && !LT_L) { 
          right(); 
      }                            
      else if(LT_L && !LT_M && !LT_R) {
          left();  
      }
      else if(!LT_L && !LT_M && !LT_R){
        sweep();
        
      }
      
    }
  
    
    if ((SignalA == HIGH) && (SignalB == HIGH)){
      hardRight();
   }
  
    if ((SignalA == LOW)&& (SignalB == LOW)){
      stop();
      bluetooth_plus();
    }
  
    if ((SignalA == HIGH) && (SignalB == LOW)){
      return;
    }
  }

}
