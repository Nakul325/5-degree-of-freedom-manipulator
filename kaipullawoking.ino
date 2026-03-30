#include <Servo.h>

Servo base, shoulder, arm, wrist, gripper;


void moveServo(Servo &s, int from, int to) {
  if (from < to) {
    for (int pos = from; pos <= to; pos++) {
      s.write(pos);
      delay(20);
    }
  } else {
    for (int pos = from; pos >= to; pos--) {  
      s.write(pos);
      delay(20);
    }
  }
}

void setup() {
  base.attach(3);
  shoulder.attach(5);
  arm.attach(6);
  wrist.attach(9);
  gripper.attach(10);

  // Start all at 0°
  base.write(0);
  shoulder.write(0);
  arm.write(0);
  wrist.write(0);
  gripper.write(0);

  delay(2000);
}

void loop() {

  // PICK Kaipulla
  moveServo(base, 0, 30);
  moveServo(shoulder, 0, 40);
  moveServo(arm, 0, 50);
  moveServo(wrist, 0, 20);

  // Close gripper (grab object)
  moveServo(gripper, 0, 40);
  delay(1000);

  //  LIFT 
  moveServo(arm, 50, 20);
  moveServo(shoulder, 40, 20);

  //  MOVE TO PLACE 
  moveServo(base, 30, 80);

  //  LOWER 
  moveServo(shoulder, 20, 40);
  moveServo(arm, 20, 50);

  //  RELEASE 
  moveServo(gripper, 40, 0);
  delay(1000);

  //  RETURN HOME Kaipulla
  moveServo(base, 80, 0);
  moveServo(shoulder, 40, 0);
  moveServo(arm, 50, 0);
  moveServo(wrist, 20, 0);

  delay(3000);
}