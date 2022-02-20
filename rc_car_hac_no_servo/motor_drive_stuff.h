#ifndef MOTOR_DRIVE_STUFF_H_
#define MOTOR_DRIVE_STUFF_H_

// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 3 //blue
#define BIN1 7 //purple
#define AIN2 4 //green
#define BIN2 8 //white
#define PWMA 5 //yellow
#define PWMB 6 //grsy
#define STBY 9 //brown

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;
// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int motor_speed = 252;//170; //speed of the back wheels. Had to set it high.
int motor_steer = 252; //speed of the front motor

bool going_left = false;
bool going_right = false;
bool going_straight = false;

bool status_motor[4] = {false, false, false, false}; //fwd, back, right, left

void robot_brake()
{
  motor1.brake();
}

void robot_stop(){
  motor1.stopp();
}

void robot_fwd()
{
  motor1.drive(motor_speed);
}

//overload the function so we can call with a duration.

void robot_fwd(int duration)
{
  motor1.drive(motor_speed, duration);
}

void robot_back(){
  motor1.drive(-motor_speed);
}

void robot_back(int duration){
  motor1.drive(-motor_speed, duration);
}

void robot_right(){
  if (!going_right) motor2.drive(motor_steer);
  going_right = true;
  going_left = false;
  going_straight = false;
}

void robot_right(int duration){
  motor2.drive(motor_steer, duration);
  going_right = false;
  going_left = false;
  going_straight = false;
}

void robot_left(int duration){
  motor2.drive(-motor_steer, duration);
  going_right = false;
  going_left = true;
  going_straight = false;
}

void robot_left(){
  if(!going_left) motor2.drive(-motor_steer);
  going_right = false;
  going_left = true;
  going_straight = false;
}

void robot_straight(){
  if(!going_straight) motor2.brake();
  going_right = false;
  going_left = false;
  going_straight = true;
}

void robot_control(int i){ //only gets called if we want to set this to true
  if(!status_motor[i]){ //only instruct motor to move if status is false
                        // otherwise it should already be moving
    status_motor[i] = true;
    switch(i){
        case 0: //fwd
//          Serial.println("going forward");
          robot_fwd();
          break;
        case 1: //back
//          Serial.println("going back");
          robot_back();
          break;
        case 2: //right
          Serial.println("going right");
          robot_right();
          break;
        case 3: //left
          Serial.println("going left");
          robot_left();
          break;
      }
  }

  
}

#endif
