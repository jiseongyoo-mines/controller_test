#include <ros/ros.h>
// #include <joint_trajectory_controller/hardware_interface_adapter.h>
#include "controller_test/cPWM.h"
#include "controller_test/GPIOConst.h"
#include "controller_test/GPIOManager.h"
#include <iostream>
#include <unistd.h>

//  Motor0 running test; dirA = Pin8_9, dirB = Pin8_14, enable = Pin8_28, PWM = Pin8_13
#define MOTOR_0_PWM "P8_13"
#define MOTOR_0_STBY "P8_8"
#define MOTOR_0_DIRA "P8_9"
#define MOTOR_0_DIRB "P8_14"
#define MOTOR_0_ENABLE "P8_28"


struct JointState { double joint1;};
using namespace std;

int main(int argc, char **argv)
{
  // Test option, m:Motor, p:PWM, g:GPIO
  char option;
  bool quite = false;
  string aux;
  int pin;
  GPIO::GPIOManager* gp=NULL;
  cPWM::cPWM* a;
  
  while(!quite){
    cout << "select test option (m:Motor, p:PWM, g:GPIO, q:Quite): ";
    cin >> option;
    
    switch (option){
      case 'm':
        cout << "Hello Motor0 test" << endl;

        gp = GPIO::GPIOManager::getInstance();
        // Motor standby set
        pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_0_STBY);
        gp->setDirection(pin, GPIO::OUTPUT);
        gp->setValue(pin, GPIO::HIGH);
        cout << "MOTOR0 Standby : High" << endl;
        // Motor direction set
        pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_0_DIRA);
        gp->setDirection(pin, GPIO::OUTPUT);
        gp->setValue(pin, GPIO::LOW);
        cout << "MOTOR0 DirA : High" << endl;
        pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_0_DIRB);
        gp->setDirection(pin, GPIO::OUTPUT);
        gp->setValue(pin, GPIO::HIGH);
        cout << "MOTOR0 DirB : Low" << endl;
        
        // Motor enable set
        pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_0_ENABLE);
        gp->setDirection(pin, GPIO::OUTPUT);
        gp->setValue(pin, GPIO::HIGH);
        cout << "MOTOR0 Enable : High" << endl;
        
        // Motor PWM set
        aux = MOTOR_0_PWM;

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
        
        break;
        
      case 'g':
        //  GPIO test
        cout << "Hello GPIO test" << endl;
        cout << "Put GPIO pin ";
        cin >> aux;
        
        gp = GPIO::GPIOManager::getInstance();
        pin = GPIO::GPIOConst::getInstance()->getGpioByKey(aux.c_str());
        gp->setDirection(pin, GPIO::OUTPUT);
        
        cout << aux << " High" << endl;
        gp->setValue(pin, GPIO::HIGH);
        sleep(2);
        cout << aux << " Low" << endl;
        gp->setValue(pin, GPIO::LOW);
        sleep(2);
        
        gp->~GPIOManager();
        cout <<"Test ends"<<endl;
        break;
      
      case 'p':
        //  PWM test
        cout << "Hello PWM Test" << endl;
        cout << "Put PWM pin ";
        cin >> aux;
        
        a = new cPWM::cPWM(aux);

        a->Period(1000000000);	// 200000ns = 200us = 0.2ms = 5000hz
        a->Duty_cycle(500000000);	// 50% duty cycle
        a->Polarity(1);
        
        cout << aux << " PWM enable" << endl;
        a->Enable();
        usleep(10000000);
        cout << aux << " PWM disable" << endl;
        a->Disable();
        
        delete a;
        cout <<"Test ends"<< endl;
        break;
        
      case 'q':
        cout <<"Quite the test"<<endl;
        quite = true;
        break;
        
      default:
        cout <<"Wrong test option"<<endl;
        break;
	  }
	}
	    
  return 0;
}
