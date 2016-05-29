#include <Smartcar.h>
#include <Servo.h>

String readString;
Servo servo1, servo2;

void setup() {
    
    servo1.attach(9);
    servo2.attach(10);
    Serial.begin(9600);
    servo1.write(90);
    servo2.write(90);
    Serial.println("servo-test-22-dual-input");
    while(!Serial){
      
      }
}

void loop() {

    while (Serial.available()) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
      Serial.write(c);
      delay(2);  //slow looping to allow buffer to fill with next character
      }

      if (readString.length() >0) {
      Serial.println(readString);  //so you can see the captured string 
      int n = readString.toInt();  //convert readString into a number
      servo1.write(n);
      servo2.write(n);
      
      readString=""; //empty for next input
    } 
  }
