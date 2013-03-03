int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

const int LED_PIN = 13;
const int LDR_PIN = A1;
const int PIEZO_PIN = 9;

void setup() {
  
  Serial.begin(9600);
  
  //Light LED while we are calibrating
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); 
  
  //Calibrate to get full range from analog in
  while(millis() < 5000) {
    sensorValue = analogRead(LDR_PIN);
    if(sensorValue > sensorHigh)
      sensorHigh = sensorValue;
    if(sensorValue < sensorLow)
      sensorLow = sensorValue;
  }
  
  Serial.print("Low: ");
  Serial.print(sensorLow);
  Serial.print(", High: ");
  Serial.println(sensorHigh);
  
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  sensorValue = analogRead(LDR_PIN);
  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);
  tone(PIEZO_PIN, pitch, 20);
  delay(10);  
}
