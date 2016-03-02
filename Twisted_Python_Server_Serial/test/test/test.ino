#include <Smartcar.h>

Car car;

boolean Complete = false;  // whether the string is complete
int speed=0;
int angle=0;
byte byteArray[5];
int j=0;
String bajs ="";
void setup() {
  car.begin(); //initialize the car using the encoders and the gyro
  Serial.begin(9600);

}
void loop() {
  
  
  if (Complete) {


    if(byteArray[1] == 0x46)
    {
   
      speed = byteArray[3];
    }
    else if(byteArray[1] == 0x42)
    {
     
      speed = -byteArray[1];
    }
    if(byteArray[2] == 0x52)
    {
      
      angle = byteArray[4];
    }
    else if(byteArray[2] == 0x4c)
    {
      
      angle = -byteArray[4];
    }   
    car.setSpeed(speed);
    car.setAngle(angle);
    Complete = false;
    j=0;
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
   
     byte tmp;
  while (Serial.available()) {
    // get the new byte:
    byte inByte = (byte)Serial.read();

    byteArray[j] = inByte;

      j++;
    if (inByte == 0x0d){
      tmp = 0x0d;
    }
    if(inByte == 0x0a && tmp == 0x0d)
    {
   
       Complete = true;
     }


  }
}
