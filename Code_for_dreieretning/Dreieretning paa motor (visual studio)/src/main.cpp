#include <Arduino.h>

  // constants so it can't change:
const int Relay=8;
const int Relay1=10;
const int onLightcw=7;
const int onLightccw=6;
const int readyToStart=5;
const int ButtonPin=2; 
const int ButtonPin1=3;

  // The variables can change
int RelayState=0; //Relay State memory
int RelayState1=0;
int ButtonState; //Button State memory
int ButtonOld=1; //Previous State of Button Memory
int Button1State;
int Button1Old=1;
int dt(50); //delay for correcting debounce
int spinDownDelay=5000; //delay for Motor spin down time

void setup() {
  // Setting inputs and outputs to the pins:
pinMode(Relay, OUTPUT); // set arduino pin to output mode
pinMode(Relay1, OUTPUT);// set arduino pin to output mode
pinMode(onLightccw,OUTPUT);
pinMode(onLightcw, OUTPUT);
pinMode(readyToStart, OUTPUT);
pinMode(ButtonPin, INPUT_PULLUP); // set arduino pin to input mode
pinMode(ButtonPin1, INPUT_PULLUP);// set arduino pin to input mode
}

void loop() { //CW
ButtonState=digitalRead(ButtonPin); //read ButtonState
Button1State=digitalRead(ButtonPin1);//read ButtonState
if (ButtonOld==0 && ButtonState==1 && RelayState1==0){ //Check logic states of both relays and intelock
  if (RelayState==0){ //If statment for requierment for start of Relay
    digitalWrite(Relay, HIGH); //Write Relaypin HIGH 
    digitalWrite(onLightcw, HIGH); //light for motor spinning cw
    digitalWrite(Relay1, LOW); //interlock
    digitalWrite(readyToStart, LOW);
    RelayState=1; //Memory latch for Relay
  }
  else{ //else function for Writing low to both Relay
    digitalWrite(Relay, LOW); 
    digitalWrite(Relay1, LOW);
    delay(spinDownDelay);  //delay for spindown of motor
    digitalWrite(onLightcw, LOW);
    digitalWrite(readyToStart, HIGH); //readyToStart light
    RelayState=0;
    RelayState1=0;
  }
}//CCW
else if (Button1Old==0 && Button1State==1 && RelayState==0){ //Check logic states of both relays and intelock
  if (RelayState1==0){ //If statment for requierment for start of Relay1
    digitalWrite(Relay1, HIGH);
    digitalWrite(onLightccw, HIGH); //light for spinning ccw
    digitalWrite(readyToStart, LOW);
    digitalWrite(Relay, LOW);
    RelayState1=1;
    
  }
  else{
    digitalWrite(Relay1, LOW);
    digitalWrite(Relay, LOW);
    delay(spinDownDelay);  //delay for motor spinning down
    digitalWrite(onLightccw, LOW);
    digitalWrite(readyToStart, HIGH); //light for ready for star
    RelayState1=0;
    RelayState=0;
  }
}
ButtonOld=ButtonState; //To make Buttonold remember the old posistion
Button1Old=Button1State;
delay(dt); //debounce correcting
}
