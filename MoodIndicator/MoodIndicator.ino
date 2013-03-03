#include <Servo.h>

Servo myServo;

const int SERVO_PIN = 9;
const int POT_PIN = A0;

int potIn;
int servoAngle;

void setup() {
  myServo.attach(9);
}

void loop() {
  potIn = analogRead(POT_PIN);
  servoAngle = map(potIn, 0, 1023, 0, 179);
  myServo.write(servoAngle);
  delay(15);
}
