#include <Servo.h>

Servo base, shoulder, arm, wrist, gripper;

int bPos = 0, sPos = 0, aPos = 0, wPos = 0, gPos = 0;

char currentServo = 'b';  // default selection

void moveServo(Servo &s, int &pos, int target) {
  if (pos < target) {
    for (int i = pos; i <= target; i++) {
      s.write(i);
      delay(10);
    }
  } else {
    for (int i = pos; i >= target; i--) {
      s.write(i);
      delay(10);
    }
  }
  pos = target;
}

void setup() {
  Serial.begin(9600);

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

  Serial.println("Control: b/s/a/w/g to select servo, + or - to move");
}

void loop() {

  if (Serial.available()) {
    char cmd = Serial.read();

    // Select servo
    if (cmd == 'b' || cmd == 's' || cmd == 'a' || cmd == 'w' || cmd == 'g') {
      currentServo = cmd;
      Serial.print("Selected: ");
      Serial.println(currentServo);
    }

    // Increase angle
    if (cmd == '+') {
      if (currentServo == 'b' && bPos < 180) moveServo(base, bPos, bPos + 5);
      if (currentServo == 's' && sPos < 180) moveServo(shoulder, sPos, sPos + 5);
      if (currentServo == 'a' && aPos < 180) moveServo(arm, aPos, aPos + 5);
      if (currentServo == 'w' && wPos < 180) moveServo(wrist, wPos, wPos + 5);
      if (currentServo == 'g' && gPos < 180) moveServo(gripper, gPos, gPos + 5);
    }

    // Decrease angle
    if (cmd == '-') {
      if (currentServo == 'b' && bPos > 0) moveServo(base, bPos, bPos - 5);
      if (currentServo == 's' && sPos > 0) moveServo(shoulder, sPos, sPos - 5);
      if (currentServo == 'a' && aPos > 0) moveServo(arm, aPos, aPos - 5);
      if (currentServo == 'w' && wPos > 0) moveServo(wrist, wPos, wPos - 5);
      if (currentServo == 'g' && gPos > 0) moveServo(gripper, gPos, gPos - 5);
    }
  }
}