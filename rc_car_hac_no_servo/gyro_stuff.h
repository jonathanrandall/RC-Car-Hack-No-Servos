#ifndef GYRO_STUFF_H_
#define GYRO_STUFF_H_

#include <BMI160Gen.h>

const int bmi160_i2c_addr = 0x69;
//const int bmi160_select_pin = 10;
const int bmi160_interrupt_pin = 2;
volatile bool is_shocked = false;

void bmi160_intr(void)
{
  is_shocked = true;
//  Serial.println("interrupt");
}


void start_gyro(){
  //  BMI160.begin(BMI160GenClass::SPI_MODE, bmi160_select_pin, bmi160_interrupt_pin);
  BMI160.begin(BMI160GenClass::I2C_MODE, bmi160_i2c_addr, bmi160_interrupt_pin);
  BMI160.attachInterrupt(bmi160_intr);
  BMI160.setIntZeroMotionEnabled(true);
  BMI160.setIntShockEnabled(true);
}

// bool getIntFreefallEnabled();
//        void setIntFreefallEnabled(bool enabled);
//        bool getIntShockEnabled();
//        void setIntShockEnabled(bool enabled);
//        bool getIntStepEnabled();
//        void setIntStepEnabled(bool enabled);
//        bool getIntMotionEnabled();
//        void setIntMotionEnabled(bool enabled);
//        bool getIntZeroMotionEnabled();
//        void setIntZeroMotionEnabled(bool enabled);
//        bool getIntTapEnabled();
//        void setIntTapEnabled(bool enabled);
//        bool getIntDoubleTapEnabled();
//        void setIntDoubleTapEnabled(bool enabled);

#endif
