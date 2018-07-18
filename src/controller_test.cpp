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
  // Test option, m:Motor, p:PWM, g:GPIO
  char option;
  bool quite = false;
  string aux;
  int pin;
  
  while(!quite){
    cout << "select test option (m:Motor, p:PWM, g:GPIO, q:Quite): ";
    cin >> option;
    
    switch (option){
      case 'm':
        //  Motor running test; dirA = Pin8_9, dirB = Pin8_14, enable = Pin8_28, PWM = Pin8_13
        /*
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
        */
        cout <<"Motor test is not available yet"<<endl;
        break;
        
      case 'g':
        //  GPIO test
        cout << "Hello GPIO test" << endl;
        cout << "Put GPIO pin ";
        cin >> aux;
        
        GPIO::GPIOManager* gp = GPIO::GPIOManager::getInstance();
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
        
        cPWM::cPWM* a;
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
