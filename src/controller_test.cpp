#include <ros/ros.h>
// #include <joint_trajectory_controller/hardware_interface_adapter.h>
#include "controller_test/cPWM.h"
#include "controller_test/GPIOConst.h"
#include "controller_test/GPIOManager.h"
#include <iostream>
#include <unistd.h>

struct JointState { double joint1;};
using namespace std;

int main(int argc, char **argv)
{
/*
  cout << "Hello GPIO test" << endl;

  GPIO::GPIOManager* gp = GPIO::GPIOManager::getInstance();
  int pin = GPIO::GPIOConst::getInstance()->getGpioByKey("P8_10");
 
  gp->setDirection(pin, GPIO::OUTPUT);
 
  while(true){
      gp->setValue(pin, GPIO::HIGH);
      sleep(5);
      gp->setValue(pin, GPIO::LOW);
      sleep(5);
  }
 
  gp->~GPIOManager();
*/

// assuming that the clock and the pinmux is already done
// how to:
//      SLOTS=/sys/devices/bone_capemgr.*/slots
//      echo am33xx_pwm     > $SLOTS
//      echo bone_pwm_P9_16 > $SLOTS 

// PWM test

  string aux;
  while( aux != "Q" && aux !="q")
  {
    cout << "Hello PWM Test Code" << endl;
    cout << "Put PWM pin ";
    cin << aux;
    

    cPWM::cPWM* a;
    a = new cPWM::cPWM(aux);

    a->Period(1000000000);	// 200000ns = 200us = 0.2ms = 5000hz
    a->Duty_cycle(500000000);	// 50% duty cycle
    a->Polarity(1);
    a->Enable();
  //  usleep(10000000);	//pause de 10s=10,000,000us

    cout << aux << " PWM enabled for 5s" << endl;
    usleep(5000000);     //pause de 10s=10,000,000us
    
    a->Disable();
    
    delete a;
	}
	
  return 0;
}
