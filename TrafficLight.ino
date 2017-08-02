int red=10;
int yellow=11;
int green=12;
int redPed=9;
int greenPed=8;
void setup() {
  // put your setup code here, to run once:
// initialize digital pin LED_BUILTIN as an output.
  pinMode(red, OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(redPed,OUTPUT);
  pinMode(greenPed,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(red, HIGH);
  digitalWrite(redPed,LOW); 
  digitalWrite(greenPed,HIGH);  
  delay(10000); 
  digitalWrite(greenPed,HIGH);
  delay(500);
  digitalWrite(greenPed,LOW);
  delay(500);
  digitalWrite(greenPed,HIGH);
  delay(500);
  digitalWrite(greenPed,LOW);
  delay(500);
  digitalWrite(greenPed,HIGH);
  delay(500);
  digitalWrite(greenPed,LOW);
  delay(500);
  digitalWrite(greenPed,HIGH);
  delay(500);
  
  
  digitalWrite(redPed,HIGH);
  digitalWrite(greenPed,LOW);
  delay(2500);
  digitalWrite(yellow, HIGH);   
  delay(2000); 
  digitalWrite(redPed,HIGH);
  digitalWrite(green,HIGH);
  digitalWrite(yellow,LOW);
  digitalWrite(red,LOW);
  delay(10000);
  digitalWrite(green,HIGH);
  delay(500);
  digitalWrite(green,LOW);
  delay(500);
  digitalWrite(green,HIGH);
  delay(500);
  digitalWrite(green,LOW);
  delay(500);
  digitalWrite(green,HIGH);
  delay(500);
  digitalWrite(green,LOW);
  delay(500);
  digitalWrite(green,HIGH);
  delay(500);
  digitalWrite(yellow, HIGH);
  digitalWrite(green,LOW);
  delay(2100);
  digitalWrite(yellow,LOW);
  
}


