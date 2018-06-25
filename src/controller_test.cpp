#include <ros/ros.h>
#include <joint_trajectory_controller/hardware_interface_adapter.h>
#include "controller_test/cPWM.h"
#include <iostream>
#include <unistd.h>

struct JointState { double joint1;};
using namespace std;

int main(int argc, char **argv)
{
  cout << "Hello PWM on pin P9_16!" << endl;

// assuming that the clock and the pinmux is already done
// how to:
//      SLOTS=/sys/devices/bone_capemgr.*/slots
//      echo am33xx_pwm     > $SLOTS
//      echo bone_pwm_P9_16 > $SLOTS 

  string aux = "pwm_test_P9_16.9";

  cPWM::cPWM* a;
  a = new cPWM::cPWM(aux);

  a->Period_ns(200000);
  a->Duty_ns(  100000);
  a->Polarity(1);
  a->Run();
  usleep(10000000);	//pausa de 10s=10,000,000us
  a->Stop();

  return 0;
}
