/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>
LIDARLite myLidarLite;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
//double dt =0.13;
double dt = 0.87;
double Angle = 0;
unsigned long Time;
unsigned long oldTime = 0;
unsigned long tOld;
unsigned long dT;
String post="";
float secondsPerDegree = 0;
int lastMotorPos = -1;
byte byteArray[2]= {0,0};
boolean Complete = false;
int j=0;


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




void setup() {
  Serial.begin(115200);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myLidarLite.begin();
 myservo.write(100);
}

void loop() { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Time = millis();
    if (Complete == true) {
    dT = (Time - tOld);
    
    if((Time - oldTime) < 2350){

    calculate_speed( Angle, dT );
      
    myservo.write(180);
    Serial.print(Angle);
    Serial.print(",");
    Serial.println(myLidarLite.distance()); 
    if(Angle > 360){
      Angle = 360;
      
    }
    
    tOld=Time;
    Angle = Angle + dt;
    
    }else{
      Serial.println('c');
      oldTime = Time;
      Angle=0;
      Complete = false;
      myservo.write(100);
    } 
    }
}

void serialEvent() {
  while (Serial.available()) {
      byte inByte = (byte)Serial.read();

    byteArray[j] = inByte;
    j++;

    if(byteArray[0] == 0x4C  && byteArray[1] == 0x49){
           // Got CRLF
       Complete = true;  
       oldTime = Time;
       j=0;
       byteArray[0] =0;
       byteArray[1] =0;
    }else if(byteArray[0] == 0x4C  && byteArray[1] == 0x46){
           // Got CRLF
       Complete = false; 
        j=0;
       byteArray[0] =0;
       byteArray[1] =0;
    }else if(byteArray[0] == 0x4C  && byteArray[1] == 0x42){
           // Got CRLF
       Complete = false; 
        j=0;
       byteArray[0] =0;
       byteArray[1] =0;
    }else if(byteArray[0] == 0x4C  && byteArray[1] == 0x73){
           // Got CRLF
       Complete = false; 
        j=0;
       byteArray[0] =0;
       byteArray[1] =0;
    }
    
  }
}
