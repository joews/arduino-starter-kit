
const int KEYS_PIN = A0;
const int PIEZO_PIN = 10;

const int notes[] = {262,294,330,349};

void setup() {
   Serial.begin(9600); 
}

void loop() {
  int keyVal = analogRead(KEYS_PIN);
  Serial.println(keyVal);
  
  if(keyVal == 1023) {
    tone(PIEZO_PIN, notes[0]);
  }
  else if(keyVal >= 990 && keyVal <= 1010) {
    tone(PIEZO_PIN, notes[1]);
  }
  else if(keyVal >= 505 && keyVal <= 515) {
    tone(PIEZO_PIN, notes[2]);
  }
  else if(keyVal >= 5 && keyVal <= 10)
  {
    tone(PIEZO_PIN, notes[3]);
  }
  else {
     noTone(PIEZO_PIN); 
  }
}
