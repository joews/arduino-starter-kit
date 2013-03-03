const int R_SENSOR = A0;
const int G_SENSOR = A1;
const int B_SENSOR = A2;

const int R_LED = 11;
const int B_LED = 10;
const int G_LED = 9;
const int SERIAL_LED = 13;

//Compensate for strengths of LEDs
const float R_WEIGHT = 0.3;
const float G_WEIGHT = 1.0;
const float B_WEIGHT = 0.5;

const int SERIAL_BUTTON = 8;

boolean verbose = false;
boolean serialMode = false;

int newR, newG, newB;

void setup() {
  Serial.begin(9600);
  
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);  
  pinMode(SERIAL_LED, OUTPUT);
}

void setLeds(int r, int g, int b) {
  analogWrite(R_LED, r);
  analogWrite(G_LED, g);
  analogWrite(B_LED, b);  
}

int readSensor(int sensor){
  int rawIn = analogRead(sensor);
  delay(5); //Give the ADC change to catch up  
  return rawIn / 4; //Map ADC's 0-1023 to analog out's 0-255;
}

//Fade in and out over several colours to white
void loopX() {
  for(int r = 0; r < 256; r ++) {
    setLeds(r, 0, 0);
    delay(10);
  } 
  for(int r = 255; r >= 0; r --) {
    setLeds(r, 0, 0);
    delay(10);
  } 
  delay(100);
 
 for(int g = 0; g < 256; g ++) {
    setLeds(0, g, 0);
    delay(10);
  }
  for(int g = 255; g >= 0; g --) {
    setLeds(0, g, 0);
    delay(10);
  }
  delay(100);
 
 for(int b = 0; b < 256; b ++) {
    setLeds(0 ,0, b);
    delay(10);
  } 
  for(int b = 255; b >= 0; b --) {
    setLeds(0 ,0, b);
    delay(10);
  } 
  delay(100);
}

void loop() {
   
  //TODO - toggle behaviour
  //serialMode = (digitalRead(SERIAL_BUTTON) == HIGH);
  
  if(serialMode) {
    digitalWrite(SERIAL_LED, HIGH);
    int serialR, serialB, serialG;
  
     while(Serial.available()) {
       serialR = Serial.parseInt();
       serialG = Serial.parseInt();
       serialB = Serial.parseInt();
       if(Serial.read() == ';') {
          newR = constrain(serialR, 0, 255); 
          newG = constrain(serialG, 0, 255); 
          newB = constrain(serialB, 0, 255); 
       }
    
    }
  }
  else {
    newR = readSensor(R_SENSOR);
    newG = readSensor(G_SENSOR);
    newB = readSensor(B_SENSOR);
  }
  
  if(verbose) {
    Serial.print("R:");
    Serial.print(newR);
    Serial.print(",G:");
    Serial.print(newG);
    Serial.print(",B:");
    Serial.println(newB);
  }
  
  //newR = (int)(newR * R_WEIGHT);
  //newG = (int)(newG * G_WEIGHT);
  //newB = (int)(newB * B_WEIGHT);
  
  setLeds(newR, newG, newB);
}

