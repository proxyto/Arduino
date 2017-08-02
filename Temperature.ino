int val;
int tempPin = 1;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  val=analogRead(tempPin);
  float mv = (val/1024.0)*5000;
  float cel = mv/10;
  Serial.print("TEMPERATURE");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);
}

