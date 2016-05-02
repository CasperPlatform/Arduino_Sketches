/*
  CASPER.h - Library for Controlling the CASP.ER SmartCar
  Created by Andreas J Fransson, April 30, 2016.
  Released into the public domain.
*/
#ifndef CASPER_h
#define CASPER_h

#include "Arduino.h"
#include <Wire.h>
#include <Servo.h>

class CASPER
{
  public:
    CASPER(int SteeringPin, int EnginePin);
    void setSpeed(int speed);
    void setAngle(int degrees);
    void start();
  private:
    int _SteeringPin;
    int _EnginePin;
};

#endif
