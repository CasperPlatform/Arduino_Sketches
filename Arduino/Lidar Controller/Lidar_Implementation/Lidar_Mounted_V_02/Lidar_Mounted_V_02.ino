
#include <CustomStepper.h>
#include <Wire.h>
#include <LIDARLite.h>

// 4 pin Stepper setup
CustomStepper stepper(8, 9, 10, 11);
// Lidar setup
LIDARLite myLidarLite;

// Values to send
uint16_t angle = 0;
uint16_t reading = 0;
byte range_int[2];
byte angle_int[2];

// Boolean for checking if a comand is done
boolean rotatedeg = false;

// Number of degrees stepper will turn per cycle set to 1 as default
int degree = 1;

// Number of degrees to turn, CMD will set this to CMD values.
int turn = 0;

// Directional boolan
boolean direc = false;

void setup()
{
  Serial.begin(115200);
  myLidarLite.begin();
  stepper.setRPM(12);
  stepper.setSPR(4075.7728395);
  stepper.isDone();
  stepper.setDirection(CW);
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
  }


   if(c == 'c'){
    stepper.setDirection(CCW);
    angle = 360;
    direc = false;
   }

   if(c == 'v'){
    stepper.setDirection(CW);
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

    // Take a reading with the Lidar and store it in a 16bit unsigned integer
    reading = myLidarLite.distance();

     // Send flag 'L' 
     Serial.write(0x4c);
     // Send flag 'A'
     Serial.write(0x41);

    // Send Angle as 2 bytes
    angle_int[0] = ((angle >> 8) & 0xFF);
    angle_int[1] = angle & 0xFF;
    Serial.write(angle_int[0]);
    Serial.write(angle_int[1]);
   
    // Send flag 'R'
    Serial.write(0x52);
    
    // Send Range as 2 bytes
    range_int[0] = ((reading >> 8) & 0xFF);
    range_int[1] = reading & 0xFF;
    Serial.write(range_int[0]);
    Serial.write(range_int[1]);

    // Send end CRLF + EoT
    Serial.write(0x0d);
    Serial.write(0x0a);
    Serial.write(0x04);

    // Set number of degrees to turn in next cycle (default 1)
    stepper.rotateDegrees(degree);
    
    // Set rotateable
    rotatedeg = true;
    
    // Decrement degrees to go
    turn--;
    
    // Depending on direction either increment or decrement 'angle'
    if(direc == false){
      angle--;  
    }else if(direc == true){
      angle++;
    }

    // on finished CMD return 
    if(turn == 0){
      Serial.write(0x51);
    }
    
  }
  stepper.run();
}
