#include <LiquidCrystal.h>

//Register select, enable, 4 data pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int SWITCH = 6;
const int CONTRAST = 10;
const int LED = 9;

int switchState = 0;
int prevSwitchState = 0;
int reply;

void setup() {
  pinMode(SWITCH, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(CONTRAST, OUTPUT);
  
  //PWM works well for the LED, and works with contrast
  // if a 100uF capacitor is used between PWM output and 
  // ground to smooth the signal.
  analogWrite(LED, 200);
  analogWrite(CONTRAST, 80);
  
  //cols/rows
  lcd.begin(16, 2);
  lcd.print("Uptime:");
}

void loop() {    
  lcd.setCursor(0,1);
  long seconds = millis() / 1000;
  lcd.print(seconds);
}
