#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// 60 / 120 / 90

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90); 
}

void loop() {
 delay(1000);
 myservo.write(120);
 delay(1000); 
 myservo.write(60);     
}
