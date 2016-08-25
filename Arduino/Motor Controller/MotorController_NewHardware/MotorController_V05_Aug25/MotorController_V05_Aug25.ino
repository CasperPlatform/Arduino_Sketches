#include <Servo.h>
#include "Timer.h"


// Variable to check if entire message is read
boolean Complete = false;  // whether the string is complete

// 90 is ESC Neautral
int Speed = 90;
int Angle = 100;
unsigned long lastCommand;
unsigned long timer;


// Message stored in byteArray
byte byteArray[6];

// Message size counter
int j=0;


Servo ESC;
Servo steering;

void setup() {
// start serial at 9600 baud
Serial.begin(9600);   
// ESC attached to pin 10 
ESC.attach(10);
// Servo  attached to pin 10 
steering.attach(9);

steering.write(100);
ESC.write(90);

}

void loop() {

   timer = millis();
  
    // If the car dosent recive a command for 1 seconds stop
   if(!Complete && (timer - lastCommand) > 1000){
    Speed = 90;
    Angle = 100;
    // Carry out Instructions
    ESC.write(Speed);
    steering.write(Angle);
   }

 
      // If Message is complete check command for instructions
  if (Complete) {

    // Speed reversed for calibration issues
    if(byteArray[1] == 0x46)
    {
      Speed =  90 + (int)(((double)(byteArray[3]))/90.0*10.0);
      if(Speed > 100){
        Speed = 100;
      }
      else if(Speed < 90)
      {
        Speed = 90;
      }

    }
    else if(byteArray[1] == 0x42)
    {
      Speed = 90 - (int)(((double)(byteArray[3]))/90.0*20.0);
      if(Speed < 70){
        Speed = 70;
      }
      else if(Speed > 90)
      {
        Speed = 90;
      }
    }
    else if(byteArray[1] == 0x49){
      Speed = 90;
    }

    // Steering
    if(byteArray[2] == 0x52)
    {
      Angle = 100 + (int)(((double)(byteArray[4]))/90.0*35.0);
      if(Angle > 135){
        Angle = 135;
      }
      else if(Angle < 100)
      {
        Angle = 100;
      }
    }
    else if(byteArray[2] == 0x4c)
    {
      
      Angle = 100 - (int)(((double)(byteArray[4]))/90.0*40.0);
      if(Angle < 60){
        Angle = 60;
      }
      else if(Angle > 100)
      {
        Angle = 100;
      }
    }   
    else if(byteArray[2] == 0x49){
      Angle = 100;   
    }

    
    steering.write(Angle);
    ESC.write(Speed);
    // Carry out Instructions
    lastCommand = millis();
    // Reset for new Message
    Complete = false;
    j=0;
  
    // Empty old message to make space for new
    for(int i = 0; i < 5; i++){
    byteArray[i] = 0;
    }
  }


}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
   
     byte CR;
     byte LF;
  while (Serial.available()) {
    // get the new byte:
    byte inByte = (byte)Serial.read();

    // Store message byte in Array
    byteArray[j] = inByte;
    //Serial.write(byteArray[j]);
    
      // Increment in wait for new byte
      j++;
      
    // Look for CRLF message complete
    if (inByte == 0x0d){
      CR = 0x0d;
    }
    if (inByte == 0x0a){
      LF = 0x0a;
    }
    
    if(inByte == 0x04 && CR == 0x0d && LF == 0x0a)
    {
      
       // Got CRLF
       Complete = true;
     }

  }
}

