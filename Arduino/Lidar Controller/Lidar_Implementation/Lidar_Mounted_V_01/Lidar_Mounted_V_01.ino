
#include <CustomStepper.h>
#include <Wire.h>
#include <LIDARLite.h>

CustomStepper stepper(8, 9, 10, 11);
LIDARLite myLidarLite;

boolean rotatedeg = false;
int degree = 1;
int turn = 0;
int angle = 0;
boolean direc = false;

void setup()
{
  Serial.begin(115200);
  myLidarLite.begin();
  stepper.setRPM(12);
  stepper.setSPR(4075.7728395);
  stepper.isDone();
  stepper.setDirection(CCW);
}

void loop()
{
   
//   
  if(stepper.isDone()){
    rotatedeg = false;
  }

 


   char c;
   c = Serial.read();

  if(c == 'x'){
    angle = 0;
    Serial.println("angle cleared"); 
  }


   if(c == 'c'){
    stepper.setDirection(CCW);
    Serial.println("now turning Counter Clockwise");
    angle = 360;
    direc = false;
   }

   if(c == 'v'){
    stepper.setDirection(CW);
        Serial.println("now turning Clockwise");
     angle = 0;
     direc = true;
   }
   

   if(c == '1'){
    rotatedeg = false;
    turn = 90;
   }

     if(c == '2'){
    rotatedeg = false;
    turn = 180;
   }

      if(c == '3'){
    rotatedeg = false;
    turn = 360;
   }
   
         if(c == '4'){
    rotatedeg = false;
    turn = 5;
   }
   
         if(c == '5'){
    rotatedeg = false;
    turn = 10;
   }
   
      if(c == '6'){
    rotatedeg = false;
    turn = 15;
   }

         if(c == '7'){
    rotatedeg = false;
    turn = 25;
   }
  
  if (stepper.isDone() && rotatedeg == false && turn > 0)
  {    
    Serial.print(angle);
    Serial.print(" ");
    Serial.println(myLidarLite.distance());
    stepper.rotateDegrees(degree);
    rotatedeg = true;

    turn--;
    if(direc == false){
      angle--;  
    }else if(direc == true){
      angle++;
    }
 
    if(turn == 0){
      Serial.println('q');
    }
    
  }
  stepper.run();
}
