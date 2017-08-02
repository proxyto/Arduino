#include <LiquidCrystal.h>
#define trigPin 9
#define echoPin 10
int redLED = 3;
int redled = 1;


LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED,OUTPUT);
  pinMode(redled,OUTPUT);
}

void loop() {
  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  
  if ( distance <= 30){
    digitalWrite(redLED,HIGH);
    digitalWrite(redled,HIGH);
   
  }else
     {
      digitalWrite(redLED,LOW);
      digitalWrite(redled,LOW);
     }
}
