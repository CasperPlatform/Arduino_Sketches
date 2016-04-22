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

    Serial.println("set speed" + speed);

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
  byte tmp;
  byte byteArray[7];
  
  for(int i = 0; i < 7; i++){
    byteArray[i] = 0;
    }
  while (Serial.available()) {

    byte b = Serial.read();
    
    byteArray[i] = b;
    if (b == 0x0d){
      tmp = 0x0d;
    }
    if(b == 0x0a && tmp == 0x0d)
    {
       Serial.println("got CRLF");
       handleMsg(byteArray);
       commandComplete = true;
     }
     
    i++;
  }
  for(int j = 0; j < 7; j++){
    //zSerial.write(byteArray[j]);
    handleMsg(byteArray);
  }

}

void handleMsg(byte arr[])
{
  //  Serial.println("handleMSG");
    Serial.print(">");
    Serial.print(arr[0]);
    Serial.print("<");
    
    if(arr[1] == 0x46)
    {
      Serial.println("F");
      speed = arr[3];
    }
    else if(arr[1] == 0x42)
    {
      Serial.println("B");
      speed = -arr[1];
    }
    if(arr[2] == 82)
    {
      Serial.println("R");
      angle = arr[4];
    }
    else if(arr[2] == 0x4c)
    {
      Serial.println("L");
      angle = -arr[4];
       
      
    }
    
}
