//helper dot h files.

#include "Robot_Servo.h"
#include "gyro_stuff.h"
#include "pixel_stuff.h"
#include "remote_stuff.h"
#include "motor_drive_stuff.h"

float MIN_DIST_SIDE = 60.0;
float MIN_DIST_FRONT= 70.0;

//NewPing front[3] = {NewPing left, NewPing middle, NewPing right};

float min_dist;
int min_index;
bool ispink;


bool autonomous = true; //true, not using remote.
bool moving_fwd = true;
bool moving_back = false;

unsigned long manual_drive_p;
unsigned long manual_drive_r = 100; //how often it checks the remote signal when under manual drive.
unsigned long auto_drive_p;
unsigned long auto_drive_r = 61 ; //time between checking surroundings for objects. We need at least 4 readings.
unsigned long is_shocked_p;
unsigned long is_shocked_r = 1000; //minimum time between shocks from the gyro
unsigned long change_speed_p;
unsigned long change_speed_r = 800;
int shock_cnt;

unsigned long change_light_p;
unsigned long change_light_r = 2000; //led changes colour every 1000ms or 1s.
bool read_sigs;

Robot_Servo frontservo;  //srevo objects defined in Robot_Servo.h
Robot_Servo backservo;

//Sonar s1(26,28);

void manual_drive(){ //left or right on remote while in auto drive will set to manual drive
  if(!status_motor[0]&&!status_motor[1]){
    robot_brake();

  }
  //if not pressed either left or right straighten out robot
  if(!digitalRead(sigs[2])&&!digitalRead(sigs[3])){
    robot_straight();
  }

  for (int i = 0; i<NUMSIGS; i++){

    read_sigs = digitalRead(sigs[i]);

    //confrim read
    for(int j =1; j<3; j++) read_sigs = read_sigs || digitalRead(sigs[i]); //a few read sigs to improve accuracy
    
    delay(2);
    if(digitalRead(sigs[i])||read_sigs){ //if forward is pressed on the remote call robot_control(0).
      robot_control(i); 
      }
     else {
      status_motor[i] = false; //set motor status to false
    }
  }
}

void update_robot_pos(Robot_Servo sensorss){
  float front_dist = sensorss.distances[1];
  min_dist = MAX_DISTANCE;
  min_index = 0;
  if (sensorss.distances[0] > sensorss.distances[2]) min_index = 2;
  min_dist = sensorss.distances[min_index];
  
    if (min_dist < 14.0 || front_dist < 60.0) {
      strip.fill(strip.gamma32(strip.ColorHSV(pink)));//red indicates shock
      strip.show();
      robot_straight();
      robot_brake();
      if(moving_fwd){
        moving_back = true;
        moving_fwd = false;
        robot_back();
      } else {
          moving_back = false;
          moving_fwd = true;
          robot_fwd();
      }
    } else {
      if ((min_dist < MIN_DIST_SIDE) || (front_dist < MIN_DIST_FRONT)){
        if (min_index == 0) robot_left();
        if (min_index ==2) robot_right();
      } else {
          robot_straight();
      }   
    } 
    

}

void setup() {
  Serial.begin (9600);
  // put your setup code here, to run once:
  shock_cnt = 0;
  start_gyro();
  start_pixel();
  start_remote();
  backservo.dir = false;

  is_shocked_p - millis();
  change_light_p = millis();
  run_servo_p = millis();
  manual_drive_p = millis();
  auto_drive_p = millis();
  change_speed_p = millis();
  usPm = millis();
  delay(3000);
  if (moving_fwd) robot_fwd();
  if (moving_back) robot_back();
  delay(50);
}


void loop() {

  if (is_shocked){ //change direction if robot is not moving.
//    Serial.println("is shocked");
     if ((millis() - is_shocked_p >= is_shocked_r)){

       if ((millis() - is_shocked_p >= 1.6*is_shocked_r)){shock_cnt=0;} //reset the shock because it's been to long since the last one.
       shock_cnt++;
       strip.fill(strip.gamma32(strip.ColorHSV(red)));//red indicates shock
       strip.show();
       is_shocked_p = millis(); //reset the timer.
       if (shock_cnt>1){
//         motor_speed = 252;
         shock_cnt = 0;         
         if (moving_fwd || moving_back) {
                          moving_fwd = !moving_fwd; 
                          moving_back = !moving_back;
                          robot_straight();
                          if (moving_fwd) robot_fwd(); else robot_back();
                          }
       }
     }
     is_shocked = false;
  }


  if (millis() - change_light_p >= change_light_r){ //changes the light colour
    change_light_p = millis();
    bl_gr = !bl_gr;
    
    if(!ispink) flash_colours(); else ispink = false;
    
    if (moving_fwd) strip.setPixelColor(2,strip.gamma32(strip.ColorHSV(orange)));
    else strip.setPixelColor(2,strip.gamma32(strip.ColorHSV(purple)));
    strip.show();
  }

  if ((millis() - manual_drive_p >= manual_drive_r) &!autonomous){ //only carried out if in manual drive
    manual_drive_p = millis();
    manual_drive();
  }

  if (autonomous){    
    if(moving_fwd){
//      frontservo.move_servo();
      frontservo.read_sonar(front_sonars);
    }
    if(moving_back){
//      backservo.move_servo();
      backservo.read_sonar(back_sonars);
    }

    if ((millis() - auto_drive_p >= auto_drive_r)){
      auto_drive_p = millis();
      if (moving_fwd)  update_robot_pos(frontservo); else update_robot_pos(backservo);
      if (digitalRead(sigs[2])||digitalRead(sigs[3])){
        autonomous = false; //left or right set to manual drive
      }
    }
  }

  
//  delay(2);

}
