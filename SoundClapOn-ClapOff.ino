int micPin = 2;
int gndPin = A1;
int powerPin = A2;
int micValue1 = 0;
int micValue2 = 0;
int led = 11;
boolean lightOn = false;

void setup() {
  pinMode(led,OUTPUT);
  pinMode(powerPin,OUTPUT);
  pinMode(gndPin,OUTPUT);
  pinMode(micPin,INPUT);
  digitalWrite(gndPin,LOW);
  delay(500);
  digitalWrite(powerPin,HIGH);

}

void loop() {
  micValue1 = analogRead(micPin);
  delay(1);
  micValue2 = analogRead(micPin);
  if(micValue1-micValue2>2 || micValue2-micValue1 > 2)
  {
    lightOn = !lightOn;
    delay(100);
    digitalWrite(led,lightOn);
  }

}
