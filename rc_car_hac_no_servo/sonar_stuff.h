#ifndef SONAR_STUFF_H_
#define SONAR_STUFF_H_

#include <NewPing.h>

#include <millisDelay.h>

millisDelay check_sonar;

#define MAX_DISTANCE 100 //time = 57*200 + 6000 = 17.4ms
//front
#define RF_TRIGGER_PIN  26//orange right front
#define RF_ECHO_PIN 26
#define F_TRIGGER_PIN  28//purple
#define F_ECHO_PIN 28
#define LF_TRIGGER_PIN 32 //blue left front
#define LF_ECHO_PIN 32

#define RB_TRIGGER_PIN 46 //yellow
#define RB_ECHO_PIN 46
#define B_TRIGGER_PIN  48//grean
#define B_ECHO_PIN 48
#define LB_TRIGGER_PIN 50 //white
#define LB_ECHO_PIN 50

NewPing sonar_rf(RF_TRIGGER_PIN,RF_ECHO_PIN,MAX_DISTANCE);
NewPing sonar_f(F_TRIGGER_PIN,F_ECHO_PIN,MAX_DISTANCE);
NewPing sonar_lf(LF_TRIGGER_PIN,LF_ECHO_PIN,MAX_DISTANCE);
NewPing sonar_rb(RB_TRIGGER_PIN,RB_ECHO_PIN,MAX_DISTANCE);
NewPing sonar_b(B_TRIGGER_PIN,B_ECHO_PIN,MAX_DISTANCE);
NewPing sonar_lb(LB_TRIGGER_PIN,LB_ECHO_PIN,MAX_DISTANCE);

const int numfront = 3;
const int numback = 3;

NewPing front_sonars[numfront] = {sonar_rf, sonar_f, sonar_lf};
NewPing back_sonars[numback] = {sonar_rb, sonar_b, sonar_lb};

float duration; // Stores HC-SR04 pulse duration value
float distance; // Stores calculated distance in cm
//int iterations = 3;

float soundsp = 343;
float soundcm = soundsp/10000; //cm/ms

bool reading_data = false;

const unsigned long WAIT_TO_GET_NEXT_READING = 90; 
unsigned long sonarCm;
unsigned long sonarPm;


float get_dist(NewPing s1){
  reading_data = true;

  int its = 3;
  float duration = s1.ping_median(its);

  reading_data = false;

  return (duration / 2) * soundcm;
}

#endif
