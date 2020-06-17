/*int motorPortA = 46;
int motorPortB = 47;
void setup() 
{
  pinMode(motorPortA,OUTPUT);
  pinMode(motorPortB,OUTPUT);
}

void loop() 
{
 
 //HERE THE PINS OF THE MOTOR MUST BE PUT ON PWM PORTS
//analogWrite(motorPortA,120);
//delay(8000);
analogWrite(motorPortA,255);
delay(50);
analogWrite(motorPortA,80);
delay(8000);
analogWrite(motorPortA,255);
delay(8000);
analogWrite(motorPortA,0);
delay(8000);
 analogWrite(motorPortB,0);
}
*/
const int motorPin = 44;

int speed; //Variable to store Speed, by defaul 0 PWM
int flag;

void setup()
{
  pinMode(motorPin, OUTPUT); //Set pin 44 as an OUTPUT
  Serial.begin(9600); //Init serial communication
   //Print a message:
  Serial.println("Give a number from 50 to 255.");
  Serial.println(""); //Blank line
}

void loop()
{ 
  analogWrite(motorPin, 255);
  delay(8000);
  //Check if incoming data is available:
    if (Serial.available() > 0)
    {
      // If it is, we'll use parseInt() to pull out only numbers:
      Speed = Serial.parseInt();
      flag=0;
    }

  //Valid range is from 50 to 255
  if (Speed>=50 && Speed<=255){
    //Send PWM value with analogWrite to Arduino pin 3 and print a message to serial monitor
    analogWrite(motorPin, Speed);
      //Print message only once
      if (flag==0)
      { 
        Serial.print("Motor spinning with ");
        Serial.print(Speed);
        Serial.println(" PWM");
        delay(5000);
        for(int i = 0; i <= 255; i++)
        {
          analogWrite(motorPin, i);
          Serial.println(i);
          delay(500);
        }
        delay(5000);
        for(int i = 255; i >= 0; i--)
        {
          analogWrite(motorPin, i);
          Serial.println(i);
          delay(500);
        }
        flag=1;
      }
  }
  delay(1000);
}
