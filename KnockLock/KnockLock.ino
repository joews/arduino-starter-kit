#include <Servo.h>

//TODO
// Debounce piezo knocks
// Complex knock patterns
// Build a box!

Servo servo;
const int PIEZO = A0;
const int SWITCH = 2;
const int LED_Y = 11;
const int LED_G = 12;
const int LED_R = 13;

int knockVal;
int switchVal;

//Knock intensities
const int QUIET = 30;
const int LOUD = 100;

boolean locked = false;
int numKnocks = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(9); 
  
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(SWITCH, INPUT);
  
  unlock();
}

void loop() {
  if(!locked) {
    switchVal = digitalRead(SWITCH);

    if(switchVal == HIGH) {
      locked = true;
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_R, HIGH);
      servo.write(90);
      Serial.println("Locked");
      delay(1000);
    }
  }

  if(locked) {
    knockVal = analogRead(PIEZO);
    if(numKnocks < 3 && knockVal > 0) {
      if(checkForKnock(knockVal)) {
	numKnocks ++;
      }

      Serial.print(3 - numKnocks);
      Serial.println(" knocks to go");

    }

    if(numKnocks >= 3) {
      unlock();
    }
  }

}

void unlock() {
  numKnocks = 0;
  locked = false;
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);
  servo.write(0);
  Serial.println("Unlocked");
}

void lock() {
  locked = true;
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, LOW);
  servo.write(90);
  Serial.println("Locked");
}

boolean onKnock() {
  digitalWrite(LED_Y, HIGH);
  delay(50);
  digitalWrite(LED_Y, LOW);
}

boolean checkForKnock(int value) {
  boolean valid = false;
  if(value >= QUIET &&  value <= LOUD) {
    onKnock();
    valid = true;
    Serial.print("Valid knock: ");
  } 
  else {
    Serial.print("Invalid knock: ");
  }
  Serial.println(value);

  return valid;

}
