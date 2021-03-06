
#include <AccelStepper.h>

#define HALFSTEP 8

#define motorPin5  8     // IN1 on the ULN2003 driver 2
#define motorPin6  9     // IN2 on the ULN2003 driver 2
#define motorPin7  10    // IN3 on the ULN2003 driver 2
#define motorPin8  11    // IN4 on the ULN2003 driver 2

AccelStepper stepper(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int spd = 1000;    // The current speed in steps/second
int sign = 1;   

void setup() {
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(0);   
  pinMode(13, OUTPUT);
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  digitalWrite(13, LOW);
  // print the string when a newline arrives:
  if (stringComplete) {
  Serial.println(">"+inputString+"<");
   digitalWrite(13, HIGH);
   if (inputString.compareTo("0\n") == 0) {  // forward
      sign = 0;
    }else if(inputString.compareTo("2\n") == 0){
      sign = 1;
    }else if(inputString.compareTo("1\n") == 0){
      sign = -1;
    }
   
    // clear the string:
    inputString = "";
    stringComplete = false;
    stepper.setSpeed(sign * spd);
  }
    stepper.runSpeed();
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
