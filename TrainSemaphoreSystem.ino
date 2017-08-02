int TouchSensor1 = 8;
int TouchSensor2 = 10;

  int red1 = 4;
  int yellow1 = 3;
  int green1  = 2;
  int red2 = 7;
  int yellow2 = 6;
  int green2 = 5;
  boolean lightOn = true;
  boolean state2 = true;
  boolean state21 = true;

  int touched1 = 0;
  int touched2 = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(red1,OUTPUT);
  pinMode(yellow1,OUTPUT);
  pinMode(green1,OUTPUT);
  pinMode(TouchSensor1,INPUT);
  pinMode(TouchSensor2,INPUT);
digitalWrite(green1,lightOn);
digitalWrite(green2,state21);
}

void loop() {
 

if(digitalRead(TouchSensor1)==HIGH)
{
  
  touched1++;
  delay(50);
  Serial.println(touched1);
  
if(digitalRead(TouchSensor1)==HIGH  && touched1>1)
{
   touched1 = 0;
  //lightOn = !lightOn;
  delay(100);
  digitalWrite(green1,!lightOn);
  digitalWrite(red1,true);
  
}
}

if(digitalRead(TouchSensor2)==HIGH && digitalRead(TouchSensor1)==LOW)
{
  
  touched2++;
  delay(50);
  Serial.println(touched2);
  
if(digitalRead(TouchSensor2)==HIGH  && touched2>1)
{
  
   touched2 = 0;
  //state2 = !state2;
  //state21 = !state21;
  delay(100);
  digitalWrite(red1,!state2);
  digitalWrite(yellow1,true);
  digitalWrite(green2,!state21);
  digitalWrite(red2,true);
  
  
  
  
}
}
}
