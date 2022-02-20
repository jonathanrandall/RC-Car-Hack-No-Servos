#ifndef SERVO_STUFF_H_
#define SERVO_STUFF_H_


#include "sonar_stuff.h"



const unsigned long WAIT_TO_READ_SONAR = 16;  //move servo every 105 ms.
//int currentReadPosition;

unsigned long usCm;
unsigned long usPm;
                       
boolean HEAD_DEBUG = true;


class Robot_Servo 
{
  public:
  Robot_Servo(){}
  bool dir = true;
//  void move_servo();
  void read_sonar(NewPing* s1);

  
  int iterations = 1;
  float distances[3] = {MAX_DISTANCE, MAX_DISTANCE, MAX_DISTANCE};


  const int NUM_SONARS = 3;

  
//  int offset;

//  boolean headDirectionClockwise = false;
//  int currentHeadPosition = 1;
  int currentReadPosition=0;
  
};



void Robot_Servo::read_sonar(NewPing* s1) {
  usCm = millis();
  if(usCm > usPm + WAIT_TO_READ_SONAR) {
    usPm = usCm;
//    currentReadPosition = 1;
    if(currentReadPosition>=NUM_SONARS) currentReadPosition = 0;
    duration = s1[currentReadPosition].ping_median(iterations);
    distance = (duration / 2) * soundcm;
    if (distance > MAX_DISTANCE) distance = MAX_DISTANCE;
    if (distance == 0) distance = MAX_DISTANCE;
    distances[currentReadPosition] = distance;
    
    if(HEAD_DEBUG || true) {
      if(dir) Serial.println("going forward");
      else Serial.println("Back");
      Serial.print(currentReadPosition);
      Serial.print(" - ");
      Serial.println(distances[currentReadPosition]);
    }
    currentReadPosition++;
  }
}


//Servo frontservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position
unsigned long run_servo_p;
unsigned long run_servo_r = 2000;

//
//void start_servo() {
//  frontservo.attach(F_SERVO_PIN);  // attaches the servo on pin 9 to the servo object
//}
//
//void run_servo() {
//
//  frontservo.write(96);
//  if(false){
//  for (pos = 50; pos <= 150; pos += 5) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    frontservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(10);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 150; pos >= 50; pos -= 5) { // goes from 180 degrees to 0 degrees
//    frontservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(10);                       // waits 15ms for the servo to reach the position
//  }}
//}


#endif
