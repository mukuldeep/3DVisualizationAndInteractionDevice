
#include <Stepper.h>

const int stepsPerRevolution = 200;  //number of steps per revolution

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
}
void rotate_by_angle(int angle){
  int steps=(stepsPerRevolution*angle)/360;
  myStepper.step(steps);
}
void loop() {
  // step one revolution  in one direction:
//  Serial.println("clockwise");
//  myStepper.step(40);
  rotate_by_angle(45);
  delay(100);
    //rotate_by_angle(-60);
  //delay(500);

  // step one revolution in the other direction:
//  Serial.println("counterclockwise");
//  myStepper.step(40);
//  delay(500);
}
