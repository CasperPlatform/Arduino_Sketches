#include <AccelStepper.h>
#include <Wire.h>
#include <LIDARLite.h>

AccelStepper Stepper1(1,3,4); //use pin 12 and 13 for dir and step, 1 is the "external driver" mode (A4988)


LIDARLite myLidarLite;
float angle= 0 ;
float Step = 0.4; 
void setup() {
  Serial.begin(115200);
  myLidarLite.begin();
  Stepper1.setMaxSpeed(1600); //set max speed the motor will turn (steps/second)
  Stepper1.setAcceleration(13000); //set acceleration (steps/second^2)
}

void loop() {
  if(angle > 360){
    angle = 0;
  }
  
  if(Stepper1.distanceToGo()==0){ //check if motor has already finished his last move
    Stepper1.move(10000000); //set next movement to 1600 steps (if dir is -1 it will move -1600 -> opposite direction)
    
  }
  Serial.print(angle);
  Serial.print(" ");
  Serial.println(myLidarLite.distance());
  Stepper1.run(); //run the stepper. this has to be done over and over again to continously move the stepper
  angle = angle + Step;
}
