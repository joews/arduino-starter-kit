int switchState = 0;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {

  if(switchState == LOW) {
    digitalWrite(3, HIGH); //Green
    digitalWrite(4, LOW);  //Red 1
    digitalWrite(5, LOW);  //Red 2
  }
  else {
    digitalWrite(3, LOW);
    
    digitalWrite(4, HIGH);  //Red 1
    digitalWrite(5, LOW);  //Red 2
    delay(200);
    
    digitalWrite(4, LOW);  //Red 1
    digitalWrite(5, HIGH);  //Red 2
    delay(200);
  }
}


