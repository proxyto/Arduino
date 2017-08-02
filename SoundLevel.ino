    int led[6] = {0,1,2, 3, 4, 5}; // Assign the pins for the leds
    int Audio = A0;  // pins A and D of the microphone in A0 on the UNO board
    int s,i;
    void setup()
    {
    for (i = 0; i < 6; i++)  
      pinMode(led[i], OUTPUT);
    }
    void loop()
    {
    s = analogRead(Audio);
    Serial.println(s);  
    s = s / 35;      //Change the  sensitivity by changing Denominator
      if (s == 0)  
       {
       for(i = 0; i < 6; i++)
         {
         digitalWrite(led[i], LOW);
         }
      }
      else
      {
       for (i = 0; i < s; i++) 
        {
         digitalWrite(led[i], HIGH);
         delay(30);
        }
        for(i = i; i < 6; i++)  
         {
          digitalWrite(led[i], LOW);
         }
      }
    }
