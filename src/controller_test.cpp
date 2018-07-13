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
  //  Motor running test; dirA = Pin8_9, dirB = Pin8_14, enable = Pin8_28, PWM = Pin8_13
  
  cout << "Hello GPIO test" << endl;

  GPIO::GPIOManager* gp = GPIO::GPIOManager::getInstance();
  int pin = GPIO::GPIOConst::getInstance()->getGpioByKey("P8_9");
 
  gp->setDirection(pin, GPIO::OUTPUT);
  cout << "P8_9 : High" << endl;
  gp->setValue(pin, GPIO::HIGH);
      
  pin = GPIO::GPIOConst::getInstance()->getGpioByKey("P8_28");
 
  gp->setDirection(pin, GPIO::OUTPUT);
  cout << "P8_28 : High" << endl;
  gp->setValue(pin, GPIO::HIGH);
  
  string aux = "P8_9";

  cPWM::cPWM* a;
  a = new cPWM::cPWM(aux);

  a->Period(1000000000);	// 200000ns = 200us = 0.2ms = 5000hz
  a->Duty_cycle(500000000);	// 50% duty cycle
  a->Polarity(1);
  
  cout << aux << " PWM enable" << endl;
  a->Enable();
  usleep(60000000);
  cout << aux << " PWM disable" << endl;
  a->Disable();
  
  delete a;
  
  //  GPIO test
  /*
  cout << "Hello GPIO test" << endl;

  GPIO::GPIOManager* gp = GPIO::GPIOManager::getInstance();
  int pin = GPIO::GPIOConst::getInstance()->getGpioByKey("P8_10");
 
  gp->setDirection(pin, GPIO::OUTPUT);
 
  while(true){
      cout << "P8_10 High" << endl;
      gp->setValue(pin, GPIO::HIGH);
      sleep(2);
      cout << "P8_10 Low" << endl;
      gp->setValue(pin, GPIO::LOW);
      sleep(2);
  }
 
  gp->~GPIOManager();
  */

  //  PWM test
  
  /*
  cout << "Hello PWM Test Code" << endl;
  string aux;
  while(true)
  {
    cout << "Put PWM pin ";
    cin >> aux;
    
    if ( aux == "Q" || aux =="q")
      break;
    else
    {
      cPWM::cPWM* a;
      a = new cPWM::cPWM(aux);

      a->Period(1000000000);	// 200000ns = 200us = 0.2ms = 5000hz
      a->Duty_cycle(500000000);	// 50% duty cycle
      a->Polarity(1);
      
    //  usleep(10000000);	//pause de 10s=10,000,000us

      cout << aux << " PWM enable" << endl;
      a->Enable();
      usleep(10000000);
      cout << aux << " PWM disable" << endl;
      a->Disable();
      
      delete a;
    }
	}
	cout <<"Test ends"<< endl;
	*/
  return 0;
}
