// #define <boarddefs.h> // place define statements here -- what libraries do we need?

#define RightMotorA 6
#define LeftMotorA 5 
#define RightMotorB 4
#define LeftMotorB 3
#define Enable_A 7
#define Enable_B 2

#define ENC_A 
#define ENC_B 

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
  pinMode(Enable_A, OUTPUT);
  pinMode(Enable_B, OUTPUT);
//  pinMode(ENC_A, INPUT);
//  pinMode(ENC_B, INPUT); 
}

void loop() { 
  forward();
  delay(200);
  brake();
  delay(100);
  reverse();
  delay(200);
  left_turn();
  delay(200);
  right_turn();
  delay(200);
}


// TEST TO GET HIGH/LOW VALUES


void init_motors(){
     digitalWrite(LeftMotorA, HIGH);
     digitalWrite(LeftMotorB, HIGH);
     digitalWrite(RightMotorA, HIGH);
     digitalWrite(RightMotorB, HIGH);
}

void leftmotor_reverse(){
     digitalWrite(LeftMotorA, HIGH);
     digitalWrite(LeftMotorB, LOW);
}
void leftmotor_forward(){
     digitalWrite(LeftMotorA, LOW);
     digitalWrite(LeftMotorB, HIGH);
}


void leftmotor_brake(){
     digitalWrite(LeftMotorA, HIGH);
     digitalWrite(LeftMotorB, HIGH);
}


void rightmotor_reverse(){
     digitalWrite(RightMotorA, LOW);
     digitalWrite(RightMotorB, HIGH);
}
void rightmotor_forward(){
     digitalWrite(RightMotorA, HIGH);
     digitalWrite(RightMotorB, LOW);
}
 void rightmotor_brake(){
     digitalWrite(RightMotorA, HIGH);
     digitalWrite(RightMotorB, HIGH);
}

  // COMBINATIONAL MOTOR FUNCTIONS

void brake(){
  leftmotor_brake();
  rightmotor_brake();
}

void right_turn(){
   leftmotor_forward();
   rightmotor_reverse();
}

void left_turn(){
    leftmotor_reverse();
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
