#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
int val;
int tempPin = 1;
int ledPinRed =  13;  
int ledPinGreen = 6;
int ledPinBlue = 5;
int ledStateRed = LOW; 
int ledStateGreen = LOW;
int ledStateBlue = LOW;
void setup() {
  Serial.begin(9600);
pinMode(ledPinGreen, OUTPUT);
 pinMode(ledPinRed,OUTPUT); 
 pinMode(ledPinBlue,OUTPUT);  
}

void loop() {
  val=analogRead(tempPin);
  float mv = (val/1024.0)*5000;
  float cel = mv/10;
  lcd.setCursor(7,0);
  lcd.print(cel);
  lcd.setCursor(0,0);
  lcd.print("Temp =");
  lcd.setCursor(13,0);
  lcd.print("*C");
  delay(200);
  if(cel>26)
  {
    ledStateRed = HIGH;
    ledStateGreen = LOW;
    ledStateBlue = LOW;
  }else
     if(cel>20 && cel<26)
     {
      ledStateGreen = HIGH;
      ledStateRed = LOW;
      ledStateBlue = LOW;
     }else
     if(cel<20)
     {
      ledStateBlue = HIGH;
      ledStateGreen = LOW;
      ledStateRed = LOW;
     }
  digitalWrite(ledPinRed, ledStateRed);
  digitalWrite(ledPinGreen,ledStateGreen);
  digitalWrite(ledPinBlue,ledStateBlue);
}
