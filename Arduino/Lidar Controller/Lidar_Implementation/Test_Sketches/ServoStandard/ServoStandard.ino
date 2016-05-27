/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
double dt =0;
unsigned long Time;
unsigned long oldTime;
String post="";

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Time = millis();
    if(Time < 2560){
    myservo.write(180);
    dt++; 
    Serial.println(360/dt);
    }else{
      myservo.write(100);
    }
    

    
   
}
