
#include <CustomStepper.h>
#include <Wire.h>
#include <LIDARLite.h>

// 4 pin Stepper setup
CustomStepper stepper(8, 9, 10, 11);
// Lidar setup
LIDARLite myLidarLite;

long dT;
long tNew, tOld; 
float secondsPerDegree = 0;
int lastMotorPos = -1;
int lastSpeed = 0;

// Boolean for checking if a comand is done
boolean rotatedeg = false;

// Number of degrees stepper will turn per cycle set to 1 as default
int degree = 1;

// Number of degrees to turn, CMD will set this to CMD values.
int turn = 0;
int angle = 0;
int reading = 0;

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
   
   if(c == '3'){
    rotatedeg = false;
    turn = 360;
   }


   
    tNew = millis();
    dT = (tNew - tOld);

    calculate_speed( angle, dT );

    
  if (stepper.isDone() && rotatedeg == false && turn > 0)
  {    

    // Take a reading with the Lidar and store it in a 16bit unsigned integer
    reading = myLidarLite.distance();
    
        Serial.print(angle);
        Serial.print(",");
        Serial.print(reading);
        Serial.print(",");
        Serial.print(secondsPerDegree);
        Serial.print(",");
        Serial.print(dT);
        Serial.println();
    

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
   }

    tOld=tNew;
  stepper.run();
}

void calculate_speed( int p_position, int p_interval )
{
  int degreesTraveled;
  if ( p_position > lastMotorPos )
  {
   degreesTraveled = p_position - lastMotorPos; 
  }
  else
  {
    degreesTraveled = p_position - lastMotorPos + 360;
  }
  lastMotorPos = p_position;
  float secsPerDeg = ( p_interval / 1000.0/*milliseconds*/ ) / degreesTraveled;
  secondsPerDegree = ( 0.9 * secondsPerDegree ) + ( 0.1 * secsPerDeg );
}
