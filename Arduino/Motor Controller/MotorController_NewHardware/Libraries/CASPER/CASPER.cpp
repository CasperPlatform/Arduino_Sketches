/*
  CASPER.cpp - Library for Controlling the CASP.ER SmartCar
  Created by Andreas J Fransson, April 30, 2016.
  Released into the public domain.
*/

#include "Arduino.h"
#include "CASPER.h"

const int IDLE = 90;


CASPER::CASPER(int SteeringPin,int EnginePin)
{
    Servo Steering;
    Servo Engine;
    attach(SteeringPin);
    attach(EnginePin);

}
void CASPER::start()
{
   Engine.write(IDLE);
   Steering.write(IDLE);
}

void CASPER::setSpeed(int speed)
{
 Engine.write(speed);
}

void CASPER::setAngle(int degrees)
{
 Steering.write(degrees);
}
