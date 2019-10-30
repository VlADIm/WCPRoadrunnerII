// #define <boarddefs.h> // place define statements here -- what libraries do we need?

#define RightMotorA 9
#define LeftMotorA 7
#define RightMotorB 8
#define LeftMotorB 6
#define ENA 10
#define ENB 5

//#define ENC_A 
//#define ENC_B 

//Ultrasonic Sensor
//#define trig
//#define echo
// Ultrasonic sensor_1(trig,echo) // initializing

// sub-system functions -- in order of priority

void Line_following();



void setup() {
  pinMode(RightMotorA, OUTPUT);
  pinMode(LeftMotorA, OUTPUT);
  pinMode(RightMotorB, OUTPUT);
  pinMode(LeftMotorB, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
//  pinMode(ENC_A, INPUT);
//  pinMode(ENC_B, INPUT); 
}
//
void loop() { 
  forward();
  delay(2000);
  brake();
  delay(2000);
  reverse();
  delay(2000);
  left_turn();
  delay(2000);
  right_turn();
  delay(2000);
}


// TEST TO GET HIGH/LOW VALUES


void init_motors(){
     digitalWrite(LeftMotorA, HIGH);
     digitalWrite(LeftMotorB, HIGH);
     digitalWrite(RightMotorA, HIGH);
     digitalWrite(RightMotorB, HIGH);
     analogWrite(ENA, 200);
     analogWrite(ENB, 200);
}

void leftmotor_reverse(){
     digitalWrite(LeftMotorA, HIGH);
     digitalWrite(LeftMotorB, LOW);
     analogWrite(ENB, 200);
}
void leftmotor_forward(){
     digitalWrite(LeftMotorA, LOW);
     digitalWrite(LeftMotorB, HIGH);
     analogWrite(ENB, 200);
}


void leftmotor_brake(){
     digitalWrite(LeftMotorA, HIGH);
     digitalWrite(LeftMotorB, HIGH);
     analogWrite(ENB, 200);
}


void rightmotor_reverse(){
     digitalWrite(RightMotorA, LOW);
     digitalWrite(RightMotorB, HIGH);
     analogWrite(ENA, 200);
     
}
void rightmotor_forward(){
     digitalWrite(RightMotorA, HIGH);
     digitalWrite(RightMotorB, LOW);
     analogWrite(ENA, 200);
     
}
 void rightmotor_brake(){
     digitalWrite(RightMotorA, HIGH);
     digitalWrite(RightMotorB, HIGH);
     analogWrite(ENA, 200);
}

  // COMBINATIONAL MOTOR FUNCTIONS

void brake(){
  leftmotor_brake();
  rightmotor_brake();
}

void right_turn(){
   leftmotor_forward();
   rightmotor_brake();
}

void left_turn(){
    leftmotor_brake();
    rightmotor_forward();
}

void forward(){ 
    leftmotor_forward();
    rightmotor_forward();   
}

void reverse(){
    leftmotor_reverse();
    rightmotor_reverse();
}


// Functions

void Line_following(){
  
}
