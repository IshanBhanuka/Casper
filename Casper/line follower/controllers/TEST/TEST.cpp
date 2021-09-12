// File:          TEST.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#define TIMESTEP 64
#define MAX_SPEED -6.2
#include <iostream>
using namespace std;
// All the webots classes are defined in the "webots" namespace
using namespace webots;

int driver(double num[]){
   if(num[0]>350 && num[1]>350 ){
      return 4;
   }
   else if(num[0]>350 && num[1]<350){
       return 2;
   }
   else if (num[1]>350 && num[0]<350){
       return 3;
   }
   else{
       return 4;
   }




}

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  Motor *Rmotor = robot->getMotor("MotorR");
  Motor *Lmotor = robot->getMotor("MotorL");
  
  Rmotor->setPosition(INFINITY);
  Lmotor->setPosition(INFINITY);
  
  Rmotor->setVelocity(0.0);
  Lmotor->setVelocity(0.0);
  
  
  //DistanceSensor *front= robot->getDistanceSensor("FrontSensor");
  DistanceSensor *right= robot->getDistanceSensor("RightSensor");
  DistanceSensor *left = robot->getDistanceSensor("LeftSensor");
  
  //front->enable(TIMESTEP);
  right->enable(TIMESTEP);
  left->enable(TIMESTEP);
  
  int speedR=-10;
  int speedL=-10;

  // get the time step of the current world.
  //int timeStep = (int)robot->getBasicTimeStep();

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(TIMESTEP) != -1) {
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    //  double val = ds->getValue();
    Rmotor->setVelocity(MAX_SPEED);
    Lmotor->setVelocity(MAX_SPEED);
    
    double val_R=right->getValue();
    double val_L=left->getValue();
  //  double val_F=front->getValue();
    
    double error=val_R-val_L;
    double kp=0.006;
    double arr[3]={val_L,val_R};
    cout<<"turn right";   
    int decision=driver(arr);
    if (decision==2){
            cout<<"turn right";
            speedR=-9.0;
            speedL=9.0;
            }
    if (decision==3){
           // print("turn left");
            speedR=9.0;
            speedL=-9.0;
            }
    if (decision==4){
           // print("go straight")
           speedR=10.0 ;
           speedL=10.0 ;
           }
    //if (decision==1){
           // print("go straight")
           //speedR=0.0 ;
           //speedL=0.0 ;
           //}
    Rmotor->setVelocity(speedR);
    Lmotor->setVelocity(speedL);
    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    //  motor->setPosition(10.0);
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
