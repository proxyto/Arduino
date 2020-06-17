#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>    
#include <TouchScreen.h>

//DEFINING INPUTS OF A DISPLAY AND DEFINING A COLORS
#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4 

#define TS_MINX 123
#define TS_MINY 136
#define TS_MAXX 933
#define TS_MAXY 901

#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xEDAA
#define PURPLE  0xBA55
#define INDIGO_BLUE 0x191
#define LIGHT_BLUE 0xEFF
#define SKY_BLUE  0xFFF
#define GRAY 0xC618

MCUFRIEND_kbv tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364);

boolean buttonPanelEnabled = true;
boolean buttonPhone = false;
boolean buttonBack = false;
boolean buttonHang = false;
const int  Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem = 39;         // button for start on/off the engine and only turn on the emblem
int count_phone_symer_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem = 0;        // count_phone_symer for the number of button presses
int State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem = 0;       // current state of the button
int Last_State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem = 0;
int pos_phone_symbols = 2;
int count_phone_sym = 0;
int phone_index = -1;
int phone_length;
char * choosen_phone_number = (char*)malloc(30);

char phone_keypad[] = {'1','2','3','4','5','6','7','8','9','*','0','#'};
void setup() 
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  Serial.begin(9600);
  
 //OBphone_indexECT FOR THE DISPLAY - tft
 tft.reset();
 uint16_t identifier = tft.readID();
 tft.begin(0x9486); 
 tft.setRotation(1);
 tft.fillScreen(BLACK);
}

void Home_Screen()
{ 
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  //PHONE
  tft.fillRect(407,274,73,46,WHITE);
  tft.setCursor(415,289);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("PHONE");
}

void Switched_Screen()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
}

void Back_Button()
{
  //BACK BUTTON
  tft.fillRect(240,295,70,25,BLACK);
  tft.drawLine(250,308,263,295,YELLOW);
  tft.drawLine(250,308,263,321,YELLOW);
  tft.drawLine(263,295,267,299,YELLOW);
  tft.drawLine(263,319,268,314,YELLOW);
  tft.drawLine(267,299,264,302,YELLOW);
  tft.drawLine(268,314,265,311,YELLOW);
  tft.drawLine(264,302,299,302,YELLOW);
  tft.drawLine(265,311,299,311,YELLOW);
  tft.drawLine(299,302,299,311,YELLOW);
  tft.setCursor(272,303);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Back");
}

void Phone()
{
  tft.fillScreen(BLACK);
  Back_Button();
  Design_Of_The_Phone();
}

void Design_Of_The_Phone()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  //FIRST LINE OF PHONE DIGITS 
  tft.drawRect(10,2,460,40,WHITE);
  tft.fillCircle(40,70,20,WHITE);
  tft.fillCircle(440,70,20,WHITE);
  tft.fillCircle(240,70,20,WHITE);

  //SECOND LINE OF PHONE DIGITS
  tft.fillCircle(40,125,20,WHITE);
  tft.fillCircle(440,125,20,WHITE);
  tft.fillCircle(240,125,20,WHITE);

  //THIRD LINE OF PHONE DIGITS
  tft.fillCircle(40,180,20,WHITE);
  tft.fillCircle(440,180,20,WHITE);
  tft.fillCircle(240,180,20,WHITE);

  //FOURTH LINE OF PHONE DIGITS
  tft.fillCircle(40,235,20,WHITE);
  tft.fillCircle(440,235,20,WHITE);
  tft.fillCircle(240,235,20,WHITE);

  //CALLING AND HANGING UP BUTTONS
  tft.fillCircle(40,290,20,GREEN);
  tft.fillCircle(440,290,20,RED);
  Back_Button();
  Phone_Call_Symbol();

  //1
  tft.setCursor(31,57);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[0]);

  //2
  tft.setCursor(231,57);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[1]);

  //3
  tft.setCursor(431,57);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[2]);

  //4
  tft.setCursor(31,112);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[3]);

  //5
  tft.setCursor(231,112);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[4]);

  //6
  tft.setCursor(431,112);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[5]);

  //7
  tft.setCursor(31,167);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[6]);

  //8
  tft.setCursor(231,167);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[7]);

  //9
  tft.setCursor(431,167);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[8]);
  
  //*
  tft.setCursor(31,222);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[9]);

  //0
  tft.setCursor(231,222);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[10]);

  //#
  tft.setCursor(431,222);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print(phone_keypad[11]);
}

void Phone_Call_Symbol()
{
  float start_angle = 3.0, end_angle = 2.0;
  int x = 60, y = 275, r = 30;
  for (float i = start_angle; i > end_angle; i = i - 0.05)
  {
    tft.drawPixel(x + cos(i) * r, y + sin(i) * r, WHITE); // center point is (50,100)
  }
  tft.drawLine(30,280,35,275,WHITE);
  tft.drawLine(35,275,40,282,WHITE);
  tft.drawLine(40,282,38,284,WHITE);

  start_angle = 3.0, end_angle = 2.0;
  x = 52, y = 281, r = 13;
  for (float phone_index = start_angle; phone_index > end_angle; phone_index = phone_index - 0.05)
  {
    tft.drawPixel(x + cos(phone_index) * r, y + sin(phone_index) * r, WHITE); // center point is (50,100)
  }
  tft.drawLine(46,292,47,290,WHITE);
  tft.drawLine(46,290,51,295,WHITE);
  tft.drawLine(51,295,46,301,WHITE);

  //HANGING UP SYMBOL
  start_angle = 3.7, end_angle = 2.6;
  x = 440, y = 315, r = 30;
  for (float k = start_angle; k > end_angle; k = k - 0.05)
  {
    tft.drawPixel(x + sin(k) * r, y + cos(k) * r, WHITE); // center point is (50,100)
  }

  start_angle = 3.7, end_angle = 2.6;
   x = 440, y = 304, r = 13;
  for (float l = start_angle; l > end_angle; l = l - 0.05)
  {
    tft.drawPixel(x + sin(l) * r, y + cos(l) * r, WHITE); // center point is (50,100)
  }

  tft.drawLine(425,288,428,296,WHITE);
  tft.drawLine(428,296,431,296,WHITE);
  tft.drawLine(431,296,433,294,WHITE);
  tft.drawLine(455,288,452,296,WHITE);
  tft.drawLine(452,296,449,296,WHITE);
  tft.drawLine(449,296,447,294,WHITE);
}

void Backspace_Button()
{
  tft.fillTriangle(356,278,339,294,356,310,WHITE);
  tft.fillRect(357,278,30,32,WHITE);
  tft.setCursor(361,281);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("x");
}

void loop()
{
  State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem = digitalRead(Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem);
  if(State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem != Last_State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem) 
  {
    // if the state has changed, increment the count_phone_symer
    if(State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem == HIGH) 
   {
      // if the current state is HIGH then the button
      // wend from off to on:
       count_phone_symer_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem++;
       Serial.println(count_phone_symer_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem);
       if(count_phone_symer_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem % 2 != 0)
        {
          buttonPanelEnabled = true;
          delay(100);
          Home_Screen();
        }else if(count_phone_symer_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem % 2 == 0)
        {
          delay(1500);
          buttonPanelEnabled = false;
          buttonBack = false;
          buttonPhone = false;
          free(choosen_phone_number);
          Switched_Screen();
        }
     }
  }
  TSPoint p = ts.getPoint();
  TSPoint b = ts.getPoint();
  TSPoint phone = ts.getPoint();
 if(p.z > ts.pressureThreshhold && buttonPanelEnabled  == true)
 {
  p.x = map(p.x, TS_MINX, TS_MAXX , tft.height(),0);
  p.y = map(p.y, TS_MAXY, TS_MINY, 0,tft.width());
  int t = p.x;
  p.x = p.y;
  p.y = t;
  //Z = p.z;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if(p.x > 410 && p.x < 485)
  {
    if(p.y >= 274 && p.y <= 320)
    {
      delay(200);
      buttonPanelEnabled = false;
      buttonBack = true;
      buttonPhone = true;
      Phone();
    }
  }else
   if(p.x > 410 && p.x < 485 && p.y >= 274 && p.y <= 320)
   {
     delay(200);
     buttonPanelEnabled = false;
     buttonBack = true;
     buttonPhone = true;
     Phone();
   }
 }
 
 //SELECTING BUTTONS FROM PHONE KEYBOARD
 if(phone.z > ts.pressureThreshhold && buttonPhone  == true)
 {
  phone.x = map(phone.x, TS_MINX, TS_MAXX , tft.height(),0);
  phone.y = map(phone.y, TS_MAXY, TS_MINY, 0,tft.width());
  int t = phone.x;
  phone.x = phone.y;
  phone.y = t;
  //Z = p.z;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  //IF 1 IS PRESSED
  if(phone.x > -12 && phone.x < 35)
  {
    if(phone.y >= 55 && phone.y <= 95)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '1';
      pos_phone_symbols += 19;
      tft.fillCircle(40,70,20,BLUE);
      tft.setCursor(31,57);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[0]);
      delay(220);
      tft.fillCircle(40,70,20,WHITE);
      tft.setCursor(31,57);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[0]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[0]);
      Backspace_Button();
    }
  }else
   if(phone.x > -12 && phone.x < 35 && phone.y >= 55 && phone.y <= 95)
   {
     delay(100);
     phone_index++;
     count_phone_sym++;
     choosen_phone_number[phone_index] = '1';
     pos_phone_symbols += 19;
     tft.fillCircle(40,70,20,BLUE);
     tft.setCursor(31,57);
     tft.setTextColor(WHITE);
     tft.setTextSize(4);
     tft.print(phone_keypad[0]);
     delay(220);
     tft.fillCircle(40,70,20,WHITE);
     tft.setCursor(31,57);
     tft.setTextColor(BLACK);
     tft.setTextSize(4);
     tft.print(phone_keypad[0]);
     tft.setCursor(pos_phone_symbols,12);
     tft.setTextSize(3);
     tft.setTextColor(WHITE);
     tft.print(phone_keypad[0]);
     Backspace_Button();
   }
   
  // IF 2 IS PRESSED
  if(phone.x > 210 && phone.x < 267)
  {
    if(phone.y >= 55 && phone.y <= 95)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '2';
      pos_phone_symbols += 19;
      tft.fillCircle(240,70,20,BLUE);
      tft.setCursor(231,57);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[1]);
      delay(220);
      tft.fillCircle(240,70,20,WHITE);
      tft.setCursor(231,57);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[1]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[1]);
      Backspace_Button();
    }
  }else
   if(phone.x > 210 && phone.x < 267 && phone.y >= 55 && phone.y <= 95)
   {
     delay(100);
     phone_index++;
     count_phone_sym++;
     choosen_phone_number[phone_index] = '2';
     pos_phone_symbols += 19;
     tft.fillCircle(240,70,20,BLUE);
     tft.setCursor(231,57);
     tft.setTextColor(WHITE);
     tft.setTextSize(4);
     tft.print(phone_keypad[1]);
     delay(220);
     tft.fillCircle(240,70,20,WHITE);
     tft.setCursor(231,57);
     tft.setTextColor(BLACK);
     tft.setTextSize(4);
     tft.print(phone_keypad[1]);
     tft.setCursor(pos_phone_symbols,12);
     tft.setTextSize(3);
     tft.setTextColor(WHITE);
     tft.print(phone_keypad[1]);
     Backspace_Button();
   }

   //IF 3 IS PRESSED
   if(phone.x > 437 && phone.x < 493)
  {
    if(phone.y >= 55 && phone.y <= 95)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '3';
      pos_phone_symbols += 19;
      tft.fillCircle(440,70,20,BLUE);
      tft.setCursor(431,57);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[2]);
      delay(220);
      tft.fillCircle(440,70,20,WHITE);
      tft.setCursor(431,57);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[2]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[2]);
      Backspace_Button();
    }
  }else
   if(phone.x > 437 && phone.x < 493 && phone.y >= 55 && phone.y <= 95)
   {
     delay(100);
     phone_index++;
     count_phone_sym++;
     choosen_phone_number[phone_index] = '3';
     pos_phone_symbols += 19;
     tft.fillCircle(440,70,20,BLUE);
     tft.setCursor(431,57);
     tft.setTextColor(WHITE);
     tft.setTextSize(4);
     tft.print(phone_keypad[2]);
     delay(220);
     tft.fillCircle(440,70,20,WHITE);
     tft.setCursor(431,57);
     tft.setTextColor(BLACK);
     tft.setTextSize(4);
     tft.print(phone_keypad[2]);
     tft.setCursor(pos_phone_symbols,12);
     tft.setTextSize(3);
     tft.setTextColor(WHITE);
     tft.print(phone_keypad[2]);
     Backspace_Button();
   }

   //IF 4 IS PRESSED
   if(phone.x > -12 && phone.x < 35)
  {
    if(phone.y >= 110 && phone.y <= 150)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '4';
      pos_phone_symbols += 19;
      tft.fillCircle(40,125,20,BLUE);
      tft.setCursor(31,112);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[3]);
      delay(220);
      tft.fillCircle(40,125,20,WHITE);
      tft.setCursor(31,112);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[3]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[3]);
      Backspace_Button(); 
    }
  }else
   if(phone.x > -12 && phone.x < 35 && phone.y >= 110 && phone.y <= 150)
   {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '4';
      pos_phone_symbols += 19;
      tft.fillCircle(40,125,20,BLUE);
      tft.setCursor(31,112);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[3]);
      delay(220);
      tft.fillCircle(40,125,20,WHITE);
      tft.setCursor(31,112);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[3]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[3]);
      Backspace_Button();
   }

   //IF 5 IS PRESSED
   if(phone.x > 210 && phone.x < 267)
  {
    if(phone.y >= 110 && phone.y <= 150)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '5';
      pos_phone_symbols += 19;
      tft.fillCircle(240,125,20,BLUE);
      tft.setCursor(231,112);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[4]);
      delay(220);
      tft.fillCircle(240,125,20,WHITE);
      tft.setCursor(231,112);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[4]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[4]);
      Backspace_Button();
    }
  }else
   if(phone.x > 210 && phone.x < 267 && phone.y >= 110 && phone.y <= 150)
   {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '5';
      pos_phone_symbols += 19;
      tft.fillCircle(40,125,20,BLUE);
      tft.setCursor(31,112);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[4]);
      delay(220);
      tft.fillCircle(40,125,20,WHITE);
      tft.setCursor(31,112);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[3]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[4]);
      Backspace_Button();
   }

   //IF 6 IS PRESSED
   if(phone.x > 437 && phone.x < 493)
  {
    if(phone.y >= 110 && phone.y <= 150)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '6';
      pos_phone_symbols += 19;
      tft.fillCircle(440,125,20,BLUE);
      tft.setCursor(431,112);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[5]);
      delay(220);
      tft.fillCircle(440,125,20,WHITE);
      tft.setCursor(431,112);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[5]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[5]);
      Backspace_Button();
    }
  }else
   if(phone.x > 437 && phone.x < 493 && phone.y >= 110 && phone.y <= 150)
   {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '6';
      pos_phone_symbols += 19;
      tft.fillCircle(440,125,20,BLUE);
      tft.setCursor(431,112);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[5]);
      delay(220);
      tft.fillCircle(440,125,20,WHITE);
      tft.setCursor(431,112);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[5]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[5]);
      Backspace_Button();
   }

   //IF 7 IS PRESSED
   if(phone.x > -12 && phone.x < 35)
  {
    if(phone.y >= 164 && phone.y <= 205)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '7';
      pos_phone_symbols += 19;
      tft.fillCircle(40,180,20,BLUE);
      tft.setCursor(31,167);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[6]);
      delay(220);
      tft.fillCircle(40,180,20,WHITE);
      tft.setCursor(31,167);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[6]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[6]);
      Backspace_Button();
    }
  }else
   if(phone.x > -12 && phone.x < 35 && phone.y >= 164 && phone.y <= 205)
   {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '7';
      pos_phone_symbols += 19;
      tft.fillCircle(40,180,20,BLUE);
      tft.setCursor(31,167);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[6]);
      delay(220);
      tft.fillCircle(40,180,20,WHITE);
      tft.setCursor(31,167);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[6]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[6]);
      Backspace_Button();
   }

   //IF 8 IS PRESSED
   if(phone.x > 210 && phone.x < 267)
  {
    if(phone.y >= 164 && phone.y <= 205)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '8';
      pos_phone_symbols += 19;
      tft.fillCircle(240,180,20,BLUE);
      tft.setCursor(231,167);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[7]);
      delay(220);
      tft.fillCircle(240,180,20,WHITE);
      tft.setCursor(231,167);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[7]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[7]);
      Backspace_Button();
    }
  }else
   if(phone.x > 210 && phone.x < 267 && phone.y >= 164 && phone.y <= 205)
   {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '8';
      pos_phone_symbols += 19;
      tft.fillCircle(240,180,20,BLUE);
      tft.setCursor(231,167);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[7]);
      delay(220);
      tft.fillCircle(240,180,20,WHITE);
      tft.setCursor(231,167);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[7]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[7]);
      Backspace_Button();
   }

   //IF 9 IS PRESSED
   if(phone.x > 437 && phone.x < 493)
  {
    if(phone.y >= 164 && phone.y <= 205)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '9';
      pos_phone_symbols += 19;
      tft.fillCircle(440,180,20,BLUE);
      tft.setCursor(431,167);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[8]);
      delay(220);
      tft.fillCircle(440,180,20,WHITE);
      tft.setCursor(431,167);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[8]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[8]);
      Backspace_Button();
    }
  }else
   if(phone.x > 437 && phone.x < 493 && phone.y >= 164 && phone.y <= 205)
   {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '9';
      pos_phone_symbols += 19;
      tft.fillCircle(440,180,20,BLUE);
      tft.setCursor(431,167);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[8]);
      delay(220);
      tft.fillCircle(440,180,20,WHITE);
      tft.setCursor(431,167);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[8]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[8]);
      Backspace_Button();
   }

   //IF * IS PRESSED
   if(phone.x > -12 && phone.x < 35)
  {
    if(phone.y >= 219 && phone.y <= 260)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '*';
      pos_phone_symbols += 19;
      tft.fillCircle(40,235,20,BLUE);
      tft.setCursor(31,222);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[9]);
      delay(220);
      tft.fillCircle(40,235,20,WHITE);
      tft.setCursor(31,222);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[9]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[9]);
      Backspace_Button();
    }
  }else
   if(phone.x > -12 && phone.x < 35 && phone.y >= 219 && phone.y <= 260)
   {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '*';
      pos_phone_symbols += 19;
      tft.fillCircle(40,235,20,BLUE);
      tft.setCursor(31,222);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[9]);
      delay(220);
      tft.fillCircle(40,235,20,WHITE);
      tft.setCursor(31,222);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[9]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[9]);
      Backspace_Button();
   }

   //IF 0 IS PRESSED
   if(phone.x > 210 && phone.x < 267)
  {
    if(phone.y >= 219 && phone.y <= 260)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '0';
      pos_phone_symbols += 19;
      tft.fillCircle(240,235,20,BLUE);
      tft.setCursor(231,222);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[10]);
      delay(220);
      tft.fillCircle(240,235,20,WHITE);
      tft.setCursor(231,222);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[10]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[10]);
      Backspace_Button();
    }
  }else
   if(phone.x > 210 && phone.x < 267 && phone.y >= 219 && phone.y <= 260)
   {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '0';
      pos_phone_symbols += 19;
      tft.fillCircle(240,235,20,BLUE);
      tft.setCursor(231,222);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[10]);
      delay(220);
      tft.fillCircle(240,235,20,WHITE);
      tft.setCursor(231,222);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[10]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[10]);
      Backspace_Button();
   }

   //IF # IS PRESSED
   if(phone.x > 437 && phone.x < 493)
  {
    if(phone.y >= 219 && phone.y <= 260)
    {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '#';
      pos_phone_symbols += 19;
      tft.fillCircle(440,235,20,BLUE);
      tft.setCursor(431,222);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[11]);
      delay(220);
      tft.fillCircle(440,235,20,WHITE);
      tft.setCursor(431,222);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[11]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[11]);
      Backspace_Button();
    }
  }else
   if(phone.x > 437 && phone.x < 493 && phone.y >= 219 && phone.y <= 260)
   {
      delay(100);
      phone_index++;
      count_phone_sym++;
      choosen_phone_number[phone_index] = '#';
      pos_phone_symbols += 19;
      tft.fillCircle(440,235,20,BLUE);
      tft.setCursor(431,222);
      tft.setTextColor(WHITE);
      tft.setTextSize(4);
      tft.print(phone_keypad[11]);
      delay(220);
      tft.fillCircle(440,235,20,WHITE);
      tft.setCursor(431,222);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.print(phone_keypad[11]);
      tft.setCursor(pos_phone_symbols,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(phone_keypad[11]);
      Backspace_Button();
   }

   //IF CALL BUTTON IS PRESSED
   if(phone.x > -12 && phone.x < 35)
  {
    if(phone.y >= 270)
    {
      delay(100);
      buttonHang = true;
      tft.fillRect(15,12,300,23,BLACK);
      tft.setCursor(15,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.fillTriangle(356,278,339,294,356,310,BLACK);
      tft.fillRect(357,278,30,32,BLACK);
      tft.print("Calling"); 
      int new_pos_of_phone = 160;   
      for(phone_length = 0; phone_length < count_phone_sym; phone_length++)
      {
        new_pos_of_phone += 20;     
        tft.setCursor(new_pos_of_phone,12);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print(choosen_phone_number[phone_length]);  
      }
      while(phone_length > 0)
     {
      phone_length--;
      if(choosen_phone_number[phone_length] == '#' || choosen_phone_number[phone_length] == '*' || count_phone_sym < 10 || count_phone_sym > 10)
      {
        delay(2000);
        tft.fillRect(15,12,400,27,BLACK);
        tft.setCursor(15,12);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("Invalid number");
        buttonHang = false;
        delay(3000);
        tft.fillRect(15,12,400,27,BLACK);
        pos_phone_symbols = 2;
        count_phone_sym = 0;
        phone_index = -1; 
        free(choosen_phone_number);
        break;
      }
     }    
    }
  }else
   if(phone.x > -12 && phone.x < 35 && phone.y >= 272)
   {
     delay(100);
     buttonHang = true;
     tft.fillRect(15,12,300,23,BLACK);
     tft.setCursor(15,12);
     tft.setTextSize(3);
     tft.setTextColor(WHITE);
     tft.fillTriangle(356,278,339,294,356,310,BLACK);
     tft.fillRect(357,278,30,32,BLACK);
     tft.print("Calling");
     int new_pos_of_phone = 160;
     for(phone_length = 0; phone_length < count_phone_sym; phone_length++)
     {
      new_pos_of_phone += 20;     
      tft.setCursor(new_pos_of_phone,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print(choosen_phone_number[phone_length]);  
     }
     while(phone_length > 0)
     {
      phone_length--;
      if(choosen_phone_number[phone_length] == '#' || choosen_phone_number[phone_length] == '*' || count_phone_sym < 10 || count_phone_sym > 10)
      {
        delay(2000);
        tft.fillRect(15,12,400,27,BLACK);
        tft.setCursor(15,12);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("Invalid number");
        buttonHang = false;
        delay(3000);
        tft.fillRect(15,12,400,27,BLACK);
        pos_phone_symbols = 2;
        count_phone_sym = 0;
        phone_index = -1; 
        free(choosen_phone_number);
        break;
      }
     }
   }

   //IF HANG BUTTON IS PRESSED
   if(phone.x > 437 && phone.x < 493)
  {
    if(phone.y >= 270 && buttonHang == true)
    {
      delay(200);
      tft.fillRect(15,12,130,27,BLACK);
      tft.setCursor(15,12);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.print("Hanging");
      pos_phone_symbols = 2;
      count_phone_sym = 0;
      phone_index = -1;
      delay(2000);
      buttonHang = false;
      free(choosen_phone_number);
      tft.fillRect(15,12,400,27,BLACK);
    }
  }else
   if(phone.x > 437 && phone.x < 493 && phone.y >= 272 && buttonHang == true)
   {
     delay(200);
     tft.fillRect(15,12,130,27,BLACK);
     tft.setCursor(15,12);
     tft.setTextSize(3);
     tft.setTextColor(WHITE);
     tft.print("Hanging");
     pos_phone_symbols = 2;
     count_phone_sym = 0;
     phone_index = -1;
     delay(2000);
     tft.fillRect(15,12,400,27,BLACK);
     buttonHang = false;
     free(choosen_phone_number);
     tft.fillRect(15,12,400,27,BLACK);
   }
   if(phone.x > 353 && phone.x < 415)
   {
    if(phone.y >=285)
    {
      if(pos_phone_symbols <= 2)
      {
        pos_phone_symbols = 2;
      }else
      {
        delay(150);
        tft.fillTriangle(356,278,339,294,356,310,BLUE);
        tft.fillRect(357,278,30,32,BLUE);
        tft.setCursor(361,281);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("x");
        delay(220);
        tft.fillTriangle(356,278,339,294,356,310,WHITE);
        tft.fillRect(357,278,30,32,WHITE);
        tft.setCursor(361,281);
        tft.setTextSize(3);
        tft.setTextColor(BLACK);
        tft.print("x");
        count_phone_sym--;
        choosen_phone_number[phone_index] = NULL;
        phone_index--;
        tft.fillRect(pos_phone_symbols,12,19,23,BLACK);
        pos_phone_symbols -= 19;
        if(choosen_phone_number[0] == NULL)
        {
          tft.fillTriangle(356,278,339,294,356,310,BLACK);
          tft.fillRect(357,278,30,32,BLACK);
        }
      }
    }else
     if(phone.x > 353 && phone.x < 415 && phone.y >=285)
     {
      if(pos_phone_symbols <= 2)
      {
        pos_phone_symbols = 2;
      }else
      {
        delay(150);
        tft.fillTriangle(356,278,339,294,356,310,BLUE);
        tft.fillRect(357,278,30,32,BLUE);
        tft.setCursor(361,281);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("x");
        delay(220);
        tft.fillTriangle(356,278,339,294,356,310,WHITE);
        tft.fillRect(357,278,30,32,WHITE);
        tft.setCursor(361,281);
        tft.setTextSize(3);
        tft.setTextColor(BLACK);
        tft.print("x");
        count_phone_sym--;
        choosen_phone_number[phone_index] = NULL;
        phone_index--;
        tft.fillRect(pos_phone_symbols,12,19,23,BLACK);
        pos_phone_symbols -= 19;
        if(choosen_phone_number[0] == NULL)
        {
          tft.fillTriangle(356,278,339,294,356,310,BLACK);
          tft.fillRect(357,278,30,32,BLACK);
        }
      }
    }
  }
 }
 if(b.z > ts.pressureThreshhold && buttonBack == true)
 {
  b.x = map(b.x, TS_MINX, TS_MAXX , tft.height(),0);
  b.y = map(b.y, TS_MAXY, TS_MINY, 0,tft.width());
  int t = b.x;
  b.x = b.y;
  b.y = t;
  //Z = p.z;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if(b.x > 230 && b.x < 308)
  {
   if(b.y >= 288 && b.y <= 315)
   {
    delay(100);
    buttonPanelEnabled = true;
    buttonBack = false;
    buttonPhone = false;
    buttonHang = false;
    pos_phone_symbols = 2;
    free(choosen_phone_number);
    Home_Screen();
   }
  }else
   if(b.x > 230 && b.x < 308 && b.y >= 288 && b.y <= 315)
   {
    delay(100);
    buttonPanelEnabled = true;
    buttonBack = false;
    buttonPhone = false;
    buttonHang = false;
    pos_phone_symbols = 2;
    free(choosen_phone_number);
    Home_Screen(); 
   } 
  }
}
