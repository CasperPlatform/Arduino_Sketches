
#include <CustomStepper.h>
CustomStepper stepper(8, 9, 10, 11);
boolean rotatedeg = false;
int degree = 360;

void setup()
{
    Serial.begin(9600);
  stepper.setRPM(12);
  stepper.setSPR(4075.7728395);
  stepper.isDone();
}

void loop()
{
   
   
//  if(stepper.isDone()){
//    rotatedeg = false;
//  }


   char c;
   c = Serial.read();

   if(c == 'y'){
    rotatedeg = false;
   }

   if(c == '1'){
    rotatedeg = false;
    degree = 90;
   }

     if(c == '2'){
    rotatedeg = false;
    degree = 180;
   }

      if(c == '3'){
    rotatedeg = false;
    degree = 360;
   }
   
         if(c == '4'){
    rotatedeg = false;
    degree = 5;
   }
   
         if(c == '5'){
    rotatedeg = false;
    degree = 10;
   }
   
      if(c == '6'){
    rotatedeg = false;
    degree = 15;
   }

         if(c == '7'){
    rotatedeg = false;
    degree = 25;
   }
  
  if (rotatedeg == false)
  {
    stepper.setDirection(CW);
    stepper.rotateDegrees(degree);
    rotatedeg = true;
  }
  stepper.run();
}
