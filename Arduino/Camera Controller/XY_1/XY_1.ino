#include <Servo.h>
#include <Timer.h>

// Variable to check if entire message is read
boolean Complete = false;  // whether the string is complete

// 90 is ESC Neautral
int Y = 90;
int X = 90;
unsigned long lastCommand;
unsigned long timer;


// Message stored in byteArray
byte byteArray[8];

// Message size counter
int j=0;


Servo Y_servo;
Servo X_servo;

void setup() {
// start serial at 9600 baud
Serial.begin(9600);   

// ESC attached to pin 10 
X_servo.attach(10);
// Servo  attached to pin 10 
Y_servo.attach(9);

X_servo.write(90);
Y_servo.write(90);

}

void loop() {


 
      // If Message is complete check command for instructions
  if (Complete) {

    // Right X value
    if(byteArray[1] == 0x52)
    {
      X =  90 + (byteArray[2]);
      if(X > 180){
        X = 180;
      }
      else if(X < 90)
      {
        X = 90;
      }

    }// Left X value
    else if(byteArray[1] == 0x4C)
    {
      X = 90 - (byteArray[2]);
      if(X < 0){
        X = 0;
      }
      else if(X > 90)
      {
        X = 90;
      }
    }
    else if(byteArray[1] == 0x49){
      X = 90;
    }

    // Y value up
    if(byteArray[3] == 0x55)
    {
      Y = 90 + (byteArray[4]);
      if(Y > 180){
        Y = 180;
      }
      else if(Y < 90)
      {
        Y = 90;
      }
    } //Y Value Down
    else if(byteArray[3] == 0x44)
    {
      
      Y = 90 - (int)(((double)(byteArray[4]))/90.0*50.0);
      if(Y < 40){
        Y = 40;
      }
      else if(Y > 90)
      {
        Y = 90;
      }
    }   
    else if(byteArray[3] == 0x49){
      Y = 90;   
    }

    
    Y_servo.write(Y);
    X_servo.write(X);
    // Reset for new Message
    Complete = false;
    
    j=0;
  

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

