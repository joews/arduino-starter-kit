const int RESTART = 11;

unsigned long lastUpdated = 0;
int nextLed = 2;

int switchState = HIGH;
int lastSwitchState = HIGH;

int interval = 1000;

void clearLeds() {
  for(int i = 2; i < 8; ++i) {
    digitalWrite(i, LOW);  
  } 
}

void setup() {
  
  Serial.begin(9600);
  
  for(int i = 2; i < 8; ++i) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW); 
  } 
  
  switchState = digitalRead(RESTART);
}

void loop() {
  
  unsigned long now = millis();
  
  switchState = digitalRead(RESTART);
  Serial.println(switchState);
  
  if(switchState != lastSwitchState) {
    clearLeds();
    
    nextLed = 0;
    lastUpdated = now;
  }
  
  lastSwitchState = switchState;
  
  if(now - lastUpdated > interval) {
     digitalWrite(nextLed, HIGH);
     nextLed ++; 
     lastUpdated = now;
  }
  
  //Grab attention when the timer is full
  // and the last LED has been on for a full interval
  if(nextLed == 9) {
    clearLeds();
    
    for (int i = 0; i < 3; ++i) {
      for(int j = 2; j < 8; ++j) {
        digitalWrite(j, HIGH);
        delay(80);
      }
      
      for(int j = 7; j > 1; --j) {
        digitalWrite(j, LOW);
        delay(80);
      }
    }
    
    for (int i = 0; i < 3; ++i) {
      for(int j = 2; j < 8; ++j) {
        digitalWrite(j, HIGH);
      }
      delay(400);
      
      for(int j = 2; j < 8; ++j) {
        digitalWrite(j, LOW);
      } 
      delay(100);
    }
    
    //Restart
    nextLed = 0;
  }
}
