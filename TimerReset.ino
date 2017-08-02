#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
// constants won't change. Used here to
// set pin numbers:
int ledPinRed =  13;  
int ledPinGreen = 6;// the number of the LED pin

// Variables will change:
int ledStateRed = LOW; 
int ledStateGreen = LOW;// ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
           

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 5000;           // interval at which to blink (milliseconds)
void setup() {
  // put your setup code here, to run once:
  // set the digital pin as output:
 pinMode(ledPinGreen, OUTPUT);
 pinMode(ledPinRed,OUTPUT);      
 
}

void loop() {
  // put your main code here, to run repeatedly:
  
 unsigned long currentMillis = millis();
lcd.setCursor(0,0); 
   lcd.print(currentMillis/1000);
 
 if(currentMillis - previousMillis > interval) {
   // save the last time you blinked the LED
   previousMillis = currentMillis; 
   
   // if the LED is off turn it on and vice-versa:
   if (ledStateRed == LOW){
     ledStateRed = HIGH;
     ledStateGreen = LOW;
     lcd.setCursor(5,0);
     lcd.print("RED");
     lcd.setCursor(8,0);
     lcd.print("      ");
 }else {
     ledStateRed = LOW;
     ledStateGreen = HIGH;
     lcd.setCursor(8,0);
     lcd.print("GREEN");
     lcd.setCursor(5,0);
     lcd.print("   ");
     
   }
   // set the LED with the ledState of the variable:
   digitalWrite(ledPinRed, ledStateRed);
   digitalWrite(ledPinGreen,ledStateGreen);
   
 }
}
