#include <Servo.h>

// 90 is ESC Neautral
int value = 90;

Servo ESC;

void setup() {
  
// ESC attached to pin 9 
ESC.attach(10);
  
// start serial at 9600 baud
Serial.begin(9600);   
ESC.write(90); 

}

void loop() {

 
    ESC.write(value);
    Serial.println(value);
      
  
  
 
  if(Serial.available()){
  char c = Serial.read();   // Parse an Integer from Serial

  
  
  if(c == '1'){
    value = 80;
  }

  if( c == '2'){
    value = 70;
  }

  if(c == '3'){
    value = 60;
  }

    if(c == '4'){
    value = 50;
  }

    if(c == '5'){
    value = 40;
  }

      if(c == '6'){
    value = 30;
  }
      if(c == '7'){
    value = 20;
  }
        if(c == '8'){
    value = 10;
  }


        if(c == 'a'){
    value = 0;
  }

        if(c == 'd'){
    value = 180;
  }

    if(c == 's'){
    value = 90;
  }

 if(c == 'f'){
    value = 180;
  }
  
  }
 
    

}
