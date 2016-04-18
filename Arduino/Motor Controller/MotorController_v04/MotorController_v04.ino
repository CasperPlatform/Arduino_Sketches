#include <Smartcar.h>

// Declare the car Object
Car car;

// Variable to check if entire message is read
boolean Complete = false;  // whether the string is complete

// Default Speed and Angle
int speed=0;
int angle=0;

// Message stored in byteArray
byte byteArray[6];

// Message size counter
int j=0;

void setup() {
  car.begin(); //initialize the car using the encoders and the gyro
  Serial.begin(9600); // Initialize the Serial connection

}
void loop() {
  
   // If Message is complete check command for instructions
  if (Complete) {


    if(byteArray[1] == 0x46)
    {
      speed = byteArray[3];
    }
    else if(byteArray[1] == 0x42)
    {
      speed = -byteArray[1];
    }
    else if(byteArray[1] == 0x49){
      speed = 0;
    }
    if(byteArray[2] == 0x52)
    {
      angle = byteArray[4];
    }
    else if(byteArray[2] == 0x4c)
    {
      
      angle = -byteArray[4];
    }   
    else if(byteArray[2] == 0x49){
      angle = 0;   
    }

    // Carry out Instructions
    car.setSpeed(speed);
    car.setAngle(angle);

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
