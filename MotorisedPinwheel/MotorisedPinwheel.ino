
const int SWITCH = 12;
const int MOTOR_GATE = 9;

void setup() {
  Serial.begin(9600);
  
  pinMode(SWITCH, INPUT);
  pinMode(MOTOR_GATE, OUTPUT); 
}

void loop() {
  int switchState = digitalRead(SWITCH);
  Serial.println(switchState);
  
  digitalWrite(MOTOR_GATE, switchState);
}
