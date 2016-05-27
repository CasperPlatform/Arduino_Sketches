
#include <CustomStepper.h>
#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;
CustomStepper stepper(8, 9, 10, 11);
int angle = 0;
boolean finished = true;
boolean dire = true;
void setup()
{
Serial.begin(115200);
  stepper.setRPM(12);
  stepper.setSPR(4075.7728395);
  myLidarLite.begin();
  stepper.setDirection(CW);
}

void loop()
{


Serial.println("1");

stepper.isDone();
  
  if(stepper.isDone()){
    finished = true;
  }
  
  if (finished == true)
  {
//    angle++;
//    
//    if(angle == 360){
//      angle = 0;
//      
//      if(dire == true){
//      stepper.setDirection(CCW);
//      dire = false;
//      }else{
//      stepper.setDirection(CW);
//      dire = true;
//      }
//    }
    
    stepper.rotateDegrees(15.0);
//    Serial.print("Angle: ");
//    Serial.print(angle);
//    Serial.print("Range: ");
    Serial.println(myLidarLite.distance());
    finished = false;
    
  }
  
  stepper.run();
 
}

