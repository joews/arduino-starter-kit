#include <stdio.h>

const int TEMP_SENSOR = A0;
float baselineTemp = 18.0;

const boolean verbose = true;

float getTemp() {
  int sensorVal = analogRead(TEMP_SENSOR);
  float sensorVoltage = (sensorVal / 1024.0) * 5.0;
  float sensorTemp = (sensorVoltage - 0.5) * 100;
  
  if(verbose) {
     char log[32];
     sprintf(log, "%d,%d,%d", (int)sensorVal, (int)sensorVoltage, (int)sensorTemp);
     Serial.println(log); 
  }
  
  return sensorTemp;
}

float setLeds(int a, int b, int c) {
  digitalWrite(2, a);
  digitalWrite(3, b);
  digitalWrite(4, c);  
}

void setup() {
  Serial.begin(9600); 
  
  //Calibrate
  //TODO - do I need a delay here?
  baselineTemp = getTemp();
  if(verbose) {
    char log[64];
    sprintf(log, "Calibration temperature: %d", (int)baselineTemp);
    Serial.println(log);
  }
  delay(1000);
  
  //LED pins
  for(int pin = 2; pin < 5; pin++) {
    pinMode(pin, OUTPUT);
  }
  setLeds(LOW, LOW, LOW);
  
}

void loop() {
 
  //How much warmer is the sensor than the calibration temperature?
  float delta = getTemp() - baselineTemp;
  if(delta <=2 ) {
    setLeds(LOW, LOW, LOW);
  } 
  else if(delta <= 4) {
    setLeds(HIGH, LOW, LOW);
  }
  else if(delta <= 6) {
    setLeds(HIGH, HIGH, LOW);
  }
  else {
    setLeds(HIGH, HIGH, HIGH);
  }
  
  delay(1);
}
