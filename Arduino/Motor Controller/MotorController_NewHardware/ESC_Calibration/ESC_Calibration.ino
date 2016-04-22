#include <Servo.h>

// 90 is ESC Neautral
int value = 90;

Servo ESC;

void setup() {
  
// ESC attached to pin 9 
ESC.attach(9);
  
// start serial at 9600 baud
Serial.begin(9600);    

}

void loop() {

 
    ESC.write(value);
    Serial.println(value);
      
  
  
 
  if(Serial.available()){
  char c = Serial.read();   // Parse an Integer from Serial

  
  
  if(c == 'a'){
    value = 179;
  }

  if( c == 's'){
    value = 90;
  }

  if(c == 'd'){
    value = 0;
  }
  
  
  }
 
    

}
