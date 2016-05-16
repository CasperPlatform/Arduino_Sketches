#include <Servo.h>

// 90 is ESC Neautral
int value = 90;

Servo ESC;

void setup() {
  
// ESC attached to pin 9 
ESC.attach(10);
  
// start serial at 9600 baud
Serial.begin(9600);   
ESC.write(0);
delay(1000);
ESC.write(90); 

}

void loop() {

 
    ESC.write(value);
    Serial.println(value);
      
  
  
 
  if(Serial.available()){
  char c = Serial.read();   // Parse an Integer from Serial

  
  
  if(c == '1'){
    value = 100;
  }

  if( c == '2'){
    value = 110;
  }

  if(c == '3'){
    value = 120;
  }

    if(c == '4'){
    value = 130;
  }

    if(c == '5'){
    value = 140;
  }

      if(c == '6'){
    value = 150;
  }
      if(c == '7'){
    value = 160;
  }
        if(c == '8'){
    value = 180;
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
