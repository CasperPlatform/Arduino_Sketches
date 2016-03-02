#include <Smartcar.h>

Car car;

boolean commandComplete = false;  // whether the string is complete
int speed;
int angle;

void setup() {
  car.begin(); //initialize the car using the encoders and the gyro
  Serial.begin(9600);
  
}

void loop() {

  if (commandComplete) {

    car.setSpeed(speed);
    car.setAngle(angle);
      


    commandComplete = false;
  }
 
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  int i = 0;
  while (Serial.available()) {
    i++;
    byte bytearray[7] = (byte)Serial.read();
    Serial.println();
    


    if (bytearray[i] == '\n') {
      commandComplete = true;
    }
  }
}
