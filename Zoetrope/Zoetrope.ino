const int CONTROL1 = 2;
const int CONTROL2 = 3;
const int ENABLE = 9;
const int DIRECTION_SWITCH = 4;
const int POWER_SWITCH = 5;
const int POT = A0;

int powerSwitchState = 0;
int prevPowerSwitchState = 0;
int directionSwitchState = 0;
int prevDirectionSwitchState = 0;

boolean motorOn = false;
int motorSpeed = 0;
boolean motorDirection = false;

void setup() {
  pinMode(CONTROL1, OUTPUT);  
  pinMode(CONTROL2, OUTPUT);  
  pinMode(ENABLE, OUTPUT);  
  pinMode(DIRECTION_SWITCH, INPUT);  
  pinMode(POWER_SWITCH, INPUT);
  
  digitalWrite(ENABLE, LOW);
  
  Serial.begin(9600);
}

void loop() {
  
  //Read sensors
  powerSwitchState = digitalRead(POWER_SWITCH);
  delay(1);
  directionSwitchState = digitalRead(DIRECTION_SWITCH);
  motorSpeed = analogRead(POT) / 4;
  //Serial.println(motorSpeed);
  
  //Read direction switch
  if(directionSwitchState == HIGH 
      && directionSwitchState != prevDirectionSwitchState) {
    motorDirection = !motorDirection;
    //Serial.println("Reversing motor");
  }

  //Read power switch
  if(powerSwitchState == HIGH 
      && powerSwitchState != prevPowerSwitchState) {
    motorOn = !motorOn;
    //Serial.println("Changing motor power state");
  }
  
  //Set H-bridge direction
  if(motorDirection) {
    digitalWrite(CONTROL1, HIGH);
    digitalWrite(CONTROL2, LOW);
  }
  else {
    digitalWrite(CONTROL1, LOW);
    digitalWrite(CONTROL2, HIGH);
  }
  
  //Set power
  if(motorOn) {
    analogWrite(ENABLE, motorSpeed);
    Serial.print("Motor on ");
    Serial.println(motorSpeed);
  }
  else {
    analogWrite(ENABLE, 0);
    Serial.println("Motor off");
  }
  
  //Preserve state for next time
  prevPowerSwitchState = powerSwitchState;
  prevDirectionSwitchState = directionSwitchState;
  
}


