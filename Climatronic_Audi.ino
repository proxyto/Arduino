//LIBRARY FOR NEOPIXEL RINGS
#include <Adafruit_NeoPixel.h>
//LIBRARIES FOR THE LCD DISPLAY
//#include <Adafruit_TFTLCD.h>
#include <MCUFRIEND_kbv.h> 
#include <Adafruit_GFX.h>    
#include <TouchScreen.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 37
#define NUM_LEDS 60

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
#define ORANGE  0xFFA5
#define PURPLE  0xBA55
#define INDIGO_BLUE 0x51d8
#define LIGHT_BLUE 0xEFF
#define SKY_BLUE  0xFFF
#define GRAY 0xC618
#define BRIGHTNESS 50
//OBJECTS OF THE RINGS AND THE DISPLAY
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
MCUFRIEND_kbv  tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364);

//VARIALBLES FOR THE RINGS AND DISPLAY
const int  Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem = 39;         // button for start on/off the engine and only turn on the emblem
int Counter_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem = 0;        // counter for the number of button presses
int State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem = 0;       // current state of the button
int Last_State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem = 0;  // previous state of the button

byte neopix_gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

boolean buttonPanelEnabled = true;
boolean buttonLeftTemp = false;
boolean buttonRightTemp = false;
boolean buttonLeftProppeler = false;
boolean buttonRightProppeler = false;
boolean buttonLeftVent = false;
boolean buttonRightVent = false;
boolean buttonLeftVentOnOrOff = false;
boolean buttonRightVentOnOrOff = false;
boolean buttonLeftHeatingOnOrOff = false;
boolean buttonRightHeatingOnOrOff = false;
boolean buttonOffWholeClimateSys = false;
boolean buttonReturnHomeScreen = false;
boolean buttonClimaIsOnOrOff = false;
boolean buttonTurnOnClimatePanel = false;
boolean buttonSync = false;
boolean buttonCarFiltering = false;
boolean buttonLeftAutoPressed = false;
boolean buttonRightAutoPressed = false;

int left_auto_count = 0;
int right_auto_count = 0;
int left_vent_is_pressed = 0;
int right_vent_is_pressed = 0;
int count_filter = 0;
int count_sync = 0;
int count_climate = 0;
int level_vent_left = 0;
int level_vent_right = 0;
int level_heat_left = 0;
int level_heat_right = 0;
double temp_l = 22.0;
int isEven_l;
int vent_l = 4;
double temp_r = 21.0;
int isEven_r;
int vent_r = 2;

void setup() 
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  
  //OBJECT FOR THE RING - strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
  
 //OBJECT FOR THE DISPLAY - tft
 tft.reset();
 uint16_t identifier = tft.readID();
 tft.begin(0x9486); 
}

void Clima_Rings_Turn_At_Once(uint32_t c,uint32_t co) 
{
  uint16_t i = 1;
  for(int j = 255; j >= 0 ; j--)
  {
   for(; i < 8; i++) 
   {
     strip.setPixelColor(i, c);
   }       
  }
   //SKIP ONE PIXEL AND START FROM 10th WITH RED LIGHT
   i = 9;
   for(; i < strip.numPixels(); i++) 
   {
     strip.setPixelColor(i, co);
   }
  strip.show();  
}

void Climatronic_Lights_On()
{
  Clima_Rings_Turn_At_Once(strip.Color(0,0,255),strip.Color(255,0,0));
}

void Climatronic_Lights_Off()
{
  Clima_Rings_Turn_At_Once(strip.Color(0,0,0),strip.Color(0,0,0));
}

void Home_Screen()
{ 
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.fillRect(410,140,70,50,WHITE);
  tft.setCursor(419,153);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("A/C");
}

void PrintTemp_With_No_Trailing_Zeros_Left_Side(float myFloatValue) {
    int decimalPlaces;
    float temp = myFloatValue;
    for (decimalPlaces =0; decimalPlaces <7; decimalPlaces++) {
        if (temp == (long)temp)
             break;
        temp *= 10.0;  // Shift left one decimal digit
    }
    tft.print(myFloatValue, decimalPlaces);
}

void PrintTemp_With_No_Trailing_Zeros_Right_Side(float myFloatValue) {
    int decimalPlaces;
    float temp = myFloatValue;
    for (decimalPlaces =0; decimalPlaces <7; decimalPlaces++) {
        if (temp == (long)temp)
             break;
        temp *= 10.0;  // Shift left one decimal digit
    }
    tft.print(myFloatValue, decimalPlaces);
}

void Design_Of_The_Climate()
{
  //LEFT SIDE
  tft.drawLine(0,55,55,55,WHITE);
  tft.fillRect(0,55,20,160,RED);
  tft.fillRect(0,140,20,70,WHITE);
  tft.fillRect(0,180,20,85,LIGHT_BLUE);
  //TOP LINE
  tft.drawLine(55,55,220,55,BLACK);
  //BOTTOM LINE
  tft.drawLine(0,264,220,264,BLACK);
  //VERTICAL LINE OF THE LEFT SIDE
  tft.drawLine(219,55,219,264,BLACK);
  
  //RIGHT SIDE
  tft.drawLine(420,55,480,55,WHITE);
  tft.fillRect(460,55,20,160,RED);
  tft.fillRect(460,140,20,70,WHITE);
  tft.fillRect(460,180,20,85,LIGHT_BLUE);
  //TOP LINE
  tft.drawLine(260,55,420,55,BLACK);
  //BOTTOM LINE
  tft.drawLine(260,264,475,264,BLACK);
  //VERTICAL LINE OF THE RIGHT SIDE
  tft.drawLine(260,55,260,264,BLACK);
  //SEPARATING LINE 
  tft.drawLine(0,287,480,287,WHITE);
}

void Left_Vent()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.drawLine(175,55,220,55,WHITE);
  tft.drawLine(175,264,220,264,WHITE);
  tft.drawLine(220,55,220,264,WHITE);
  tft.fillRect(155,22,44,28,BLACK);
  tft.fillRect(177,22,20,28,BLACK);
  tft.setCursor(177,22);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print(vent_l);
}

void Left_Vent_Two_Digits()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.drawLine(175,55,220,55,WHITE);
  tft.drawLine(175,264,220,264,WHITE);
  tft.drawLine(220,55,220,264,WHITE);
  tft.fillRect(155,22,44,28,BLACK);
  tft.setCursor(155,22);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print(vent_l);
}

void Right_Vent()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.drawLine(260,55,305,55,WHITE);
  tft.drawLine(260,264,305,264,WHITE);
  tft.drawLine(260,55,260,264,WHITE);
  tft.fillRect(252,22,44,28,BLACK);
  tft.fillRect(274,22,20,28,BLACK);
  tft.setCursor(274,22);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print(vent_r);
}

void Right_Vent_Two_Digits()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.drawLine(260,55,305,55,WHITE);
  tft.drawLine(260,264,305,264,WHITE);
  tft.drawLine(260,55,260,264,WHITE);
  tft.fillRect(252,22,44,28,BLACK);
  tft.setCursor(252,22);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print(vent_r);
}

void Left_Temp()
{
  tft.fillRect(7,22,64,33,BLACK);
  tft.setCursor(7,22);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  if(isEven_l % 2 == 0)
  {
  PrintTemp_With_No_Trailing_Zeros_Left_Side(floor(temp_l));
  tft.setCursor(50,36);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print(".");
  tft.setCursor(60,36);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("0");
  }else
  {
    PrintTemp_With_No_Trailing_Zeros_Left_Side(floor(temp_l));
    tft.setCursor(50,36);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(".");
    tft.setCursor(60,36);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("5");
  }
  tft.drawCircle(55,23,2,WHITE);
  tft.setCursor(60,20);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("C");
}

void Right_Temp()
{
  tft.fillRect(410,22,64,33,BLACK);
  tft.setCursor(410,22);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  if(isEven_r % 2 == 0)
  {
  PrintTemp_With_No_Trailing_Zeros_Right_Side(floor(temp_r));
  tft.setCursor(453,36);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print(".");
  tft.setCursor(463,36);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("0");
  }else
  {
    PrintTemp_With_No_Trailing_Zeros_Right_Side(floor(temp_r));
    tft.setCursor(453,36);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(".");
    tft.setCursor(463,36);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("5");
  }
  tft.drawCircle(458,23,2,WHITE);
  tft.setCursor(463,20);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("C");
}

void TempsSigns()
{
  //INCREASE TEMP LEFT SIDE
  tft.fillRect(26,95,30,3,WHITE);
  tft.fillRect(39,81,3,30,WHITE);

  //DECREASE TEMP LEFT SIDE
  tft.fillRect(26,210,30,3,WHITE);

  //INCREASE TEMP RIGHT SIDE
  tft.fillRect(420,97,30,3,WHITE);
  tft.fillRect(433,83,3,30,WHITE);

  //DECREASE TEMP RIGHT SIDE
  tft.fillRect(420,212,30,3,WHITE); 
}

void Left_Arrows_Up_And_Down()
{
  //ARROW UP LEFT SIDE
  tft.drawTriangle(170,97,190,77,210,97,WHITE);
  tft.drawLine(170,97,210,97,BLACK);

  //ARROW DOWN LEFT SIDE
  tft.drawTriangle(210,212,190,232,170,212,WHITE);
  tft.drawLine(170,212,210,212,BLACK);
}

void Right_Arrows_Up_And_Down()
{
  //ARROW UP RIGHT SIDE
  tft.drawTriangle(270,97,290,77,310,97,WHITE);
  tft.drawLine(270,97,310,97,BLACK);

  //ARROW DOWN RIGHT SIDE
  tft.drawTriangle(310,212,290,232,270,212,WHITE);
  tft.drawLine(270,212,310,212,BLACK);
}

void Auto_Button()
{
  tft.setCursor(170,271);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("AUTO");

  tft.setCursor(264,271);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("AUTO");
}

void Left_Seat()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.drawLine(80,95,75,115,WHITE);
  tft.drawLine(80,95,85,94,WHITE);
  tft.drawLine(85,94,85,115,WHITE);
  tft.drawLine(77,115,70,125,WHITE);
  tft.drawLine(70,124,99,189,WHITE);
  tft.drawLine(77,115,84,115,WHITE);
  tft.drawLine(84,115,100,145,WHITE);
  tft.drawLine(99,145,99,148,WHITE);
  tft.drawLine(99,148,117,178,WHITE);
  tft.drawLine(117,178,110,188,WHITE);
  tft.drawLine(110,188,115,193,WHITE);
  tft.drawLine(115,193,125,190,WHITE);
  tft.drawLine(125,190,160,190,WHITE);
  tft.drawLine(165,185,165,190,WHITE);
  tft.drawPixel(164,184,WHITE);
  tft.drawPixel(163,183,WHITE);
  tft.drawPixel(162,183,WHITE);
  tft.drawLine(162,183,125,183,WHITE);
  tft.drawLine(125,183,119,185,WHITE);
}

void Right_Seat()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.drawLine(391,95,396,115,WHITE);
  tft.drawLine(391,95,386,94,WHITE);
  tft.drawLine(386,94,386,115,WHITE);
  tft.drawLine(394,115,401,125,WHITE);
  tft.drawLine(401,124,372,189,WHITE);
  tft.drawLine(394,115,387,115,WHITE);
  tft.drawLine(387,115,371,145,WHITE);
  tft.drawLine(372,145,372,148,WHITE);
  tft.drawLine(372,148,354,178,WHITE);
  tft.drawLine(354,178,361,188,WHITE);
  tft.drawLine(361,188,356,193,WHITE);
  tft.drawLine(356,193,346,190,WHITE);
  tft.drawLine(346,190,311,190,WHITE);
  tft.drawLine(306,185,306,190,WHITE);
  tft.drawPixel(307,184,WHITE);
  tft.drawPixel(308,183,WHITE);
  tft.drawPixel(309,183,WHITE);
  tft.drawLine(309,183,346,183,WHITE);
  tft.drawLine(346,183,352,185,WHITE);
}

void Propeller_Left()
{
  tft.fillRect(203,6,2,2,WHITE);
  tft.fillRect(206,6,2,2,WHITE);
  tft.fillRect(215,6,2,2,WHITE);
  tft.fillRect(218,6,2,2,WHITE);
  tft.fillRect(200,9,2,2,WHITE);
  tft.fillRect(203,9,2,2,WHITE);
  tft.fillRect(206,9,2,2,WHITE);
  tft.fillRect(212,9,2,2,WHITE);
  tft.fillRect(215,9,2,2,WHITE);
  tft.fillRect(218,9,2,2,WHITE);
  tft.fillRect(221,9,2,2,WHITE);
  tft.fillRect(200,12,2,2,WHITE);
  tft.fillRect(203,12,2,2,WHITE);
  tft.fillRect(206,12,2,2,WHITE);
  tft.fillRect(212,12,2,2,WHITE);
  tft.fillRect(215,12,2,2,WHITE);
  tft.fillRect(218,12,2,2,WHITE);
  tft.fillRect(221,12,2,2,WHITE);
  tft.fillRect(203,15,2,2,WHITE);
  tft.fillRect(206,15,2,2,WHITE);
  tft.fillRect(209,15,2,2,WHITE);
  tft.fillRect(212,15,2,2,WHITE);
  tft.fillRect(209,18,2,2,WHITE);
  tft.fillRect(212,18,2,2,WHITE);
  tft.fillRect(215,18,2,2,WHITE);
  tft.fillRect(218,18,2,2,WHITE);
  tft.fillRect(200,21,2,2,WHITE);
  tft.fillRect(203,21,2,2,WHITE);
  tft.fillRect(206,21,2,2,WHITE);
  tft.fillRect(209,21,2,2,WHITE);
  tft.fillRect(215,21,2,2,WHITE);
  tft.fillRect(218,21,2,2,WHITE);
  tft.fillRect(221,21,2,2,WHITE);
  tft.fillRect(200,24,2,2,WHITE);
  tft.fillRect(203,24,2,2,WHITE);
  tft.fillRect(206,24,2,2,WHITE);
  tft.fillRect(209,24,2,2,WHITE);
  tft.fillRect(215,24,2,2,WHITE);
  tft.fillRect(218,24,2,2,WHITE);
  tft.fillRect(221,24,2,2,WHITE);
  tft.fillRect(203,27,2,2,WHITE);
  tft.fillRect(206,27,2,2,WHITE);
  tft.fillRect(215,27,2,2,WHITE);
  tft.fillRect(218,27,2,2,WHITE);
}

void Propeller_Right()
{
  tft.fillRect(300,6,2,2,WHITE);
  tft.fillRect(303,6,2,2,WHITE);
  tft.fillRect(312,6,2,2,WHITE);
  tft.fillRect(315,6,2,2,WHITE);
  tft.fillRect(297,9,2,2,WHITE);
  tft.fillRect(300,9,2,2,WHITE);
  tft.fillRect(303,9,2,2,WHITE);
  tft.fillRect(309,9,2,2,WHITE);
  tft.fillRect(312,9,2,2,WHITE);
  tft.fillRect(315,9,2,2,WHITE);
  tft.fillRect(318,9,2,2,WHITE);
  tft.fillRect(297,12,2,2,WHITE);
  tft.fillRect(300,12,2,2,WHITE);
  tft.fillRect(303,12,2,2,WHITE);
  tft.fillRect(309,12,2,2,WHITE);
  tft.fillRect(312,12,2,2,WHITE);
  tft.fillRect(315,12,2,2,WHITE);
  tft.fillRect(318,12,2,2,WHITE);
  tft.fillRect(300,15,2,2,WHITE);
  tft.fillRect(303,15,2,2,WHITE);
  tft.fillRect(306,15,2,2,WHITE);
  tft.fillRect(309,15,2,2,WHITE);
  tft.fillRect(306,18,2,2,WHITE);
  tft.fillRect(309,18,2,2,WHITE);
  tft.fillRect(312,18,2,2,WHITE);
  tft.fillRect(315,18,2,2,WHITE);
  tft.fillRect(297,21,2,2,WHITE);
  tft.fillRect(300,21,2,2,WHITE);
  tft.fillRect(303,21,2,2,WHITE);
  tft.fillRect(306,21,2,2,WHITE);
  tft.fillRect(312,21,2,2,WHITE);
  tft.fillRect(315,21,2,2,WHITE);
  tft.fillRect(318,21,2,2,WHITE);
  tft.fillRect(297,24,2,2,WHITE);
  tft.fillRect(300,24,2,2,WHITE);
  tft.fillRect(303,24,2,2,WHITE);
  tft.fillRect(306,24,2,2,WHITE);
  tft.fillRect(312,24,2,2,WHITE);
  tft.fillRect(315,24,2,2,WHITE);
  tft.fillRect(318,24,2,2,WHITE);
  tft.fillRect(300,27,2,2,WHITE);
  tft.fillRect(303,27,2,2,WHITE);
  tft.fillRect(312,27,2,2,WHITE);
  tft.fillRect(315,27,2,2,WHITE);
}

void Buttons_At_Bottom()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.drawLine(50,288,50,313,WHITE);
  tft.drawLine(100,288,100,313,WHITE);
  tft.drawLine(150,288,150,313,WHITE);
  tft.drawLine(200,288,200,313,WHITE);
  tft.drawLine(280,288,280,313,WHITE);
  tft.drawLine(330,288,330,313,WHITE);
  tft.drawLine(380,288,380,313,WHITE);
  tft.drawLine(430,288,430,313,WHITE);
  tft.setCursor(109,297);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("A/C");
  tft.setCursor(152,297);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("SYNC");
  tft.setCursor(289,297);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("OFF");
  tft.fillCircle(220,305,3,WHITE);
  tft.fillCircle(240,305,3,WHITE);
  tft.fillCircle(260,305,3,WHITE);
  
  //LEFT SEAT FOR HEATING
  tft.drawLine(15,295,14,300,WHITE);
  tft.drawLine(15,295,19,293,WHITE);
  tft.drawLine(19,293,19,300,WHITE);
  tft.drawLine(19,300,15,300,WHITE);
  tft.drawLine(15,300,12,303,WHITE);
  tft.drawLine(12,303,15,313,WHITE);
  tft.drawLine(19,300,21,306,WHITE);
  tft.drawLine(20,306,22,311,WHITE);
  tft.drawLine(22,311,20,313,WHITE);
  tft.drawLine(20,313,22,315,WHITE);
  tft.drawLine(22,315,27,314,WHITE);
  tft.drawLine(27,314,33,314,WHITE);
  tft.drawLine(35,314,35,311,WHITE);
  tft.drawLine(35,311,28,311,WHITE);
  tft.drawLine(28,311,23,313,WHITE);

  //HEATING SYMBOLS LEFT SEAT
  tft.fillTriangle(23,309,25,307,27,309,WHITE);
  tft.fillTriangle(28,309,30,307,32,309,WHITE);
  tft.drawLine(25,309,25,313,WHITE);
  tft.drawPixel(24,314,WHITE);
  tft.drawPixel(23,315,WHITE);
  tft.drawPixel(22,316,WHITE);
  tft.drawPixel(22,317,WHITE);
  tft.drawLine(30,309,30,313,WHITE);
  tft.drawPixel(29,314,WHITE);
  tft.drawPixel(28,315,WHITE);
  tft.drawPixel(27,316,WHITE);
  tft.drawPixel(27,317,WHITE);

  //LEFT SEAT FOR COOLING/VENTING
  tft.drawLine(65,295,64,300,WHITE);
  tft.drawLine(65,295,69,293,WHITE);
  tft.drawLine(69,293,69,300,WHITE);
  tft.drawLine(69,300,65,300,WHITE);
  tft.drawLine(65,300,62,303,WHITE);
  tft.drawLine(62,303,65,313,WHITE);
  tft.drawLine(69,300,71,306,WHITE);
  tft.drawLine(70,306,72,311,WHITE);
  tft.drawLine(72,311,70,313,WHITE);
  tft.drawLine(70,313,72,315,WHITE);
  tft.drawLine(72,315,77,314,WHITE);
  tft.drawLine(77,314,83,314,WHITE);
  tft.drawLine(85,314,85,311,WHITE);
  tft.drawLine(85,311,78,311,WHITE);
  tft.drawLine(78,311,73,313,WHITE);

  //RIGHT SEAT FOR HEATING
  tft.drawLine(465,295,466,300,WHITE);
  tft.drawLine(465,295,461,293,WHITE);
  tft.drawLine(461,293,461,300,WHITE);
  tft.drawLine(461,300,465,300,WHITE);
  tft.drawLine(465,300,468,303,WHITE);
  tft.drawLine(468,303,465,313,WHITE);
  tft.drawLine(461,300,459,306,WHITE);
  tft.drawLine(460,306,458,311,WHITE);
  tft.drawLine(458,311,460,313,WHITE);
  tft.drawLine(460,313,458,315,WHITE);
  tft.drawLine(458,315,453,314,WHITE);
  tft.drawLine(453,314,447,314,WHITE);
  tft.drawLine(445,314,445,311,WHITE);
  tft.drawLine(445,311,452,311,WHITE);
  tft.drawLine(452,311,457,313,WHITE);

  //HEATING SYMBOLS RIGHT SEAT
  tft.fillTriangle(453,309,455,307,457,309,WHITE);
  tft.fillTriangle(448,309,450,307,452,309,WHITE);
  tft.drawLine(455,309,455,313,WHITE);
  tft.drawPixel(456,314,WHITE);
  tft.drawPixel(457,315,WHITE);
  tft.drawPixel(458,316,WHITE);
  tft.drawPixel(458,317,WHITE);
  tft.drawLine(450,309,450,313,WHITE);
  tft.drawPixel(451,314,WHITE);
  tft.drawPixel(452,315,WHITE);
  tft.drawPixel(453,316,WHITE);
  tft.drawPixel(453,317,WHITE);

  //RIGHT SEAT FOR COOLING/VENTING
  tft.drawLine(415,295,416,300,WHITE);
  tft.drawLine(415,295,411,293,WHITE);
  tft.drawLine(411,293,411,300,WHITE);
  tft.drawLine(411,300,415,300,WHITE);
  tft.drawLine(415,300,418,303,WHITE);
  tft.drawLine(418,303,415,313,WHITE);
  tft.drawLine(411,300,409,306,WHITE);
  tft.drawLine(410,306,408,311,WHITE);
  tft.drawLine(408,311,410,313,WHITE);
  tft.drawLine(410,313,408,315,WHITE);
  tft.drawLine(408,315,403,314,WHITE);
  tft.drawLine(403,314,397,314,WHITE);
  tft.drawLine(395,314,395,311,WHITE);
  tft.drawLine(395,311,402,311,WHITE);
  tft.drawLine(402,311,407,313,WHITE);
  
  //PROPELLER ON THE COOLING LEFT SEAT
  tft.fillRect(75,296,1,1,WHITE);
  tft.fillRect(76,296,1,1,WHITE);
  tft.fillRect(79,296,1,1,WHITE);
  tft.fillRect(80,296,1,1,WHITE);
  tft.fillRect(74,297,1,1,WHITE);
  tft.fillRect(75,297,1,1,WHITE);
  tft.fillRect(76,297,1,1,WHITE);
  tft.fillRect(78,297,1,1,WHITE);
  tft.fillRect(79,297,1,1,WHITE);
  tft.fillRect(80,297,1,1,WHITE);
  tft.fillRect(81,297,1,1,WHITE);
  tft.fillRect(74,298,1,1,WHITE);
  tft.fillRect(75,298,1,1,WHITE);
  tft.fillRect(76,298,1,1,WHITE);
  tft.fillRect(78,298,1,1,WHITE);
  tft.fillRect(79,298,1,1,WHITE);
  tft.fillRect(80,298,1,1,WHITE);
  tft.fillRect(81,298,1,1,WHITE);
  tft.fillRect(75,299,1,1,WHITE);
  tft.fillRect(76,299,1,1,WHITE);
  tft.fillRect(77,299,1,1,WHITE);
  tft.fillRect(78,299,1,1,WHITE);
  tft.fillRect(77,300,1,1,WHITE);
  tft.fillRect(78,300,1,1,WHITE);
  tft.fillRect(79,300,1,1,WHITE);
  tft.fillRect(80,300,1,1,WHITE);
  tft.fillRect(74,301,1,1,WHITE);
  tft.fillRect(75,301,1,1,WHITE);
  tft.fillRect(76,301,1,1,WHITE);
  tft.fillRect(77,301,1,1,WHITE);
  tft.fillRect(79,301,1,1,WHITE);
  tft.fillRect(80,301,1,1,WHITE);
  tft.fillRect(81,301,1,1,WHITE);
  tft.fillRect(74,302,1,1,WHITE);
  tft.fillRect(75,302,1,1,WHITE);
  tft.fillRect(76,302,1,1,WHITE);
  tft.fillRect(77,302,1,1,WHITE);
  tft.fillRect(79,302,1,1,WHITE);
  tft.fillRect(80,302,1,1,WHITE);
  tft.fillRect(81,302,1,1,WHITE);
  tft.fillRect(75,303,1,1,WHITE);
  tft.fillRect(76,303,1,1,WHITE);
  tft.fillRect(79,303,1,1,WHITE);
  tft.fillRect(80,303,1,1,WHITE);

  //PROPELLER ON THE COOLING RIGHT SEAT
  tft.fillRect(400,296,1,1,WHITE);
  tft.fillRect(401,296,1,1,WHITE);
  tft.fillRect(404,296,1,1,WHITE);
  tft.fillRect(405,296,1,1,WHITE);
  tft.fillRect(399,297,1,1,WHITE);
  tft.fillRect(400,297,1,1,WHITE);
  tft.fillRect(401,297,1,1,WHITE);
  tft.fillRect(403,297,1,1,WHITE);
  tft.fillRect(404,297,1,1,WHITE);
  tft.fillRect(405,297,1,1,WHITE);
  tft.fillRect(406,297,1,1,WHITE);
  tft.fillRect(399,298,1,1,WHITE);
  tft.fillRect(400,298,1,1,WHITE);
  tft.fillRect(401,298,1,1,WHITE);
  tft.fillRect(403,298,1,1,WHITE);
  tft.fillRect(404,298,1,1,WHITE);
  tft.fillRect(405,298,1,1,WHITE);
  tft.fillRect(406,298,1,1,WHITE);
  tft.fillRect(400,299,1,1,WHITE);
  tft.fillRect(401,299,1,1,WHITE);
  tft.fillRect(402,299,1,1,WHITE);
  tft.fillRect(403,299,1,1,WHITE);
  tft.fillRect(402,300,1,1,WHITE);
  tft.fillRect(403,300,1,1,WHITE);
  tft.fillRect(404,300,1,1,WHITE);
  tft.fillRect(405,300,1,1,WHITE);
  tft.fillRect(399,301,1,1,WHITE);
  tft.fillRect(400,301,1,1,WHITE);
  tft.fillRect(401,301,1,1,WHITE);
  tft.fillRect(402,301,1,1,WHITE);
  tft.fillRect(404,301,1,1,WHITE);
  tft.fillRect(405,301,1,1,WHITE);
  tft.fillRect(406,301,1,1,WHITE);
  tft.fillRect(399,302,1,1,WHITE);
  tft.fillRect(400,302,1,1,WHITE);
  tft.fillRect(401,302,1,1,WHITE);
  tft.fillRect(402,302,1,1,WHITE);
  tft.fillRect(404,302,1,1,WHITE);
  tft.fillRect(405,302,1,1,WHITE);
  tft.fillRect(406,302,1,1,WHITE);
  tft.fillRect(400,303,1,1,WHITE);
  tft.fillRect(401,303,1,1,WHITE);
  tft.fillRect(404,303,1,1,WHITE);
  tft.fillRect(405,303,1,1,WHITE);
}

void Switched_Screen()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
}

void Climate_Indicator_On()
{
  tft.fillRect(101,288,49,4,RED);
}

void Climate_Indicator_Off()
{
  tft.fillRect(101,288,49,4,BLACK);
}

void Max_Heat_Indicator_Left_Seat()
{
  tft.fillRect(0,288,15,4,RED);
  tft.fillRect(17,288,15,4,RED);
  tft.fillRect(34,288,16,4,RED);
}

void Mid_Heat_Indicator_Left_Seat()
{
  tft.fillRect(0,288,15,4,RED);
  tft.fillRect(17,288,15,4,RED);
  tft.fillRect(34,288,16,4,GRAY);
}

void Min_Heat_Indicator_Left_Seat()
{
  tft.fillRect(0,288,15,4,RED);
  tft.fillRect(17,288,15,4,GRAY);
  tft.fillRect(34,288,16,4,GRAY);
}

void No_Heat_Indicator_Left_Seat()
{
  tft.fillRect(0,288,15,4,BLACK);
  tft.fillRect(17,288,15,4,BLACK);
  tft.fillRect(34,288,16,4,BLACK);
}

void Max_Heat_Indicator_Right_Seat()
{
  //HEATING INDICATOR OVER RIGHT SEAT
  tft.fillRect(432,288,14,4,RED);
  tft.fillRect(448,288,14,4,RED);
  tft.fillRect(464,288,16,4,RED);
}

void Mid_Heat_Indicator_Right_Seat()
{
  //HEATING INDICATOR OVER RIGHT SEAT
  tft.fillRect(432,288,14,4,RED);
  tft.fillRect(448,288,14,4,RED);
  tft.fillRect(464,288,16,4,GRAY);
}

void Min_Heat_Indicator_Right_Seat()
{
  //HEATING INDICATOR OVER RIGHT SEAT
  tft.fillRect(432,288,14,4,RED);
  tft.fillRect(448,288,14,4,GRAY);
  tft.fillRect(464,288,16,4,GRAY);
}

void No_Heat_Indicator_Right_Seat()
{
  //HEATING INDICATOR OVER RIGHT SEAT
  tft.fillRect(432,288,14,4,BLACK);
  tft.fillRect(448,288,14,4,BLACK);
  tft.fillRect(464,288,16,4,BLACK);
}

void Max_Cooling_Indicator_Left_Seat()
{
  //COOLING INDICATOR ABOVE LEFT SEAT
  tft.fillRect(52,289,14,4,BLUE);
  tft.fillRect(68,289,14,4,BLUE);
  tft.fillRect(84,289,16,4,BLUE);
}

void Mid_Cooling_Indicator_Left_Seat()
{
  //COOLING INDICATOR ABOVE LEFT SEAT
  tft.fillRect(52,289,14,4,BLUE);
  tft.fillRect(68,289,14,4,BLUE);
  tft.fillRect(84,289,16,4,GRAY);
}

void Min_Cooling_Indicator_Left_Seat()
{
  //COOLING INDICATOR ABOVE LEFT SEAT
  tft.fillRect(52,289,14,4,BLUE);
  tft.fillRect(68,289,14,4,GRAY);
  tft.fillRect(84,289,16,4,GRAY);
}

void No_Cooling_Indicator_Left_Seat()
{
  //COOLING INDICATOR ABOVE LEFT SEAT
  tft.fillRect(52,289,14,4,BLACK);
  tft.fillRect(68,289,14,4,BLACK);
  tft.fillRect(84,289,16,4,BLACK);
}

void Max_Cooling_Indicator_Right_Seat()
{
  //COOLING INDICATOR ABOVE RIGHT SEAT
  tft.fillRect(382,289,14,4,BLUE);
  tft.fillRect(398,289,14,4,BLUE);
  tft.fillRect(414,289,16,4,BLUE);
}

void Mid_Cooling_Indicator_Right_Seat()
{
  //COOLING INDICATOR ABOVE RIGHT SEAT
  tft.fillRect(382,289,14,4,BLUE);
  tft.fillRect(398,289,14,4,BLUE);
  tft.fillRect(414,289,16,4,GRAY);
}

void Min_Cooling_Indicator_Right_Seat()
{
  //COOLING INDICATOR ABOVE RIGHT SEAT
  tft.fillRect(382,289,14,4,BLUE);
  tft.fillRect(398,289,14,4,GRAY);
  tft.fillRect(414,289,16,4,GRAY);
}

void No_Cooling_Indicator_Right_Seat()
{
  //COOLING INDICATOR ABOVE RIGHT SEAT
  tft.fillRect(382,289,14,4,BLACK);
  tft.fillRect(398,289,14,4,BLACK);
  tft.fillRect(414,289,16,4,BLACK);
}

void Car_Symbol_For_Filtering()
{
  tft.drawLine(340,306,340,304,WHITE);
  tft.drawLine(340,303,348,301,WHITE);
  tft.drawLine(348,301,353,297,WHITE);
  tft.drawLine(353,297,363,297,WHITE);
  tft.drawLine(363,297,367,301,WHITE);
  tft.drawLine(367,301,369,301,WHITE);
  tft.drawLine(370,301,370,306,WHITE);
  tft.drawLine(340,306,345,306,WHITE);
  tft.drawPixel(346,307,WHITE);
  tft.drawPixel(347,308,WHITE);
  tft.drawPixel(348,308,WHITE);
  tft.drawPixel(349,308,WHITE);
  tft.drawPixel(350,307,WHITE);
  tft.drawPixel(351,306,WHITE);
  tft.drawLine(351,306,360,306,WHITE);
  tft.drawPixel(361,307,WHITE);
  tft.drawPixel(362,308,WHITE);
  tft.drawPixel(363,308,WHITE);
  tft.drawPixel(364,308,WHITE);
  tft.drawPixel(365,307,WHITE);
  tft.drawPixel(366,306,WHITE);
  tft.drawLine(366,306,370,306,WHITE);
  
  //ARROW IN THE CAR SYMBOL
  tft.drawPixel(358,299,WHITE);
  tft.drawPixel(357,299,WHITE);
  tft.drawPixel(356,299,WHITE);
  tft.drawPixel(355,299,WHITE);
  tft.drawPixel(354,300,WHITE);
  tft.drawPixel(354,301,WHITE);
  tft.drawPixel(354,302,WHITE);
  tft.drawPixel(354,303,WHITE);
  tft.drawPixel(355,303,WHITE);
  tft.drawPixel(356,303,WHITE);
  tft.drawPixel(357,303,WHITE);
  tft.drawPixel(358,303,WHITE);
  tft.drawPixel(359,303,WHITE);
  tft.fillTriangle(360,301,363,303,360,305,WHITE);
}

void Screen_For_Turning_On_AC()
{
  tft.fillRect(0,0,480,287,BLACK);
  Left_Seat();
  Right_Seat();
  tft.fillCircle(240,130,19,WHITE);
  tft.fillCircle(240,130,14,BLACK);
  tft.drawCircle(240,130,18,BLACK);
  tft.setCursor(100,90);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Turn on air conditioner"); 
}

void Left_Proppeler_For_Turn_Vent()
{
  tft.fillRect(183,144,2,2,WHITE);
  tft.fillRect(186,144,2,2,WHITE);
  tft.fillRect(195,144,2,2,WHITE);
  tft.fillRect(198,144,2,2,WHITE);
  tft.fillRect(180,147,2,2,WHITE);
  tft.fillRect(183,147,2,2,WHITE);
  tft.fillRect(186,147,2,2,WHITE);
  tft.fillRect(192,147,2,2,WHITE);
  tft.fillRect(195,147,2,2,WHITE);
  tft.fillRect(198,147,2,2,WHITE);
  tft.fillRect(201,147,2,2,WHITE);
  tft.fillRect(180,150,2,2,WHITE);
  tft.fillRect(183,150,2,2,WHITE);
  tft.fillRect(186,150,2,2,WHITE);
  tft.fillRect(192,150,2,2,WHITE);
  tft.fillRect(195,150,2,2,WHITE);
  tft.fillRect(198,150,2,2,WHITE);
  tft.fillRect(201,150,2,2,WHITE);
  tft.fillRect(183,153,2,2,WHITE);
  tft.fillRect(186,153,2,2,WHITE);
  tft.fillRect(189,153,2,2,WHITE);
  tft.fillRect(192,153,2,2,WHITE);
  tft.fillRect(189,156,2,2,WHITE);
  tft.fillRect(192,156,2,2,WHITE);
  tft.fillRect(195,156,2,2,WHITE);
  tft.fillRect(198,156,2,2,WHITE);
  tft.fillRect(180,159,2,2,WHITE);
  tft.fillRect(183,159,2,2,WHITE);
  tft.fillRect(186,159,2,2,WHITE);
  tft.fillRect(189,159,2,2,WHITE);
  tft.fillRect(195,159,2,2,WHITE);
  tft.fillRect(198,159,2,2,WHITE);
  tft.fillRect(201,159,2,2,WHITE);
  tft.fillRect(180,162,2,2,WHITE);
  tft.fillRect(183,162,2,2,WHITE);
  tft.fillRect(186,162,2,2,WHITE);
  tft.fillRect(189,162,2,2,WHITE);
  tft.fillRect(195,162,2,2,WHITE);
  tft.fillRect(198,162,2,2,WHITE);
  tft.fillRect(201,162,2,2,WHITE);
  tft.fillRect(183,165,2,2,WHITE);
  tft.fillRect(186,165,2,2,WHITE);
  tft.fillRect(195,165,2,2,WHITE);
  tft.fillRect(198,165,2,2,WHITE);
}

void No_Left_Proppeler_For_Turn_Vent()
{
  tft.fillRect(183,144,2,2,BLACK);
  tft.fillRect(186,144,2,2,BLACK);
  tft.fillRect(195,144,2,2,BLACK);
  tft.fillRect(198,144,2,2,BLACK);
  tft.fillRect(180,147,2,2,BLACK);
  tft.fillRect(183,147,2,2,BLACK);
  tft.fillRect(186,147,2,2,BLACK);
  tft.fillRect(192,147,2,2,BLACK);
  tft.fillRect(195,147,2,2,BLACK);
  tft.fillRect(198,147,2,2,BLACK);
  tft.fillRect(201,147,2,2,BLACK);
  tft.fillRect(180,150,2,2,BLACK);
  tft.fillRect(183,150,2,2,BLACK);
  tft.fillRect(186,150,2,2,BLACK);
  tft.fillRect(192,150,2,2,BLACK);
  tft.fillRect(195,150,2,2,BLACK);
  tft.fillRect(198,150,2,2,BLACK);
  tft.fillRect(201,150,2,2,BLACK);
  tft.fillRect(183,153,2,2,BLACK);
  tft.fillRect(186,153,2,2,BLACK);
  tft.fillRect(189,153,2,2,BLACK);
  tft.fillRect(192,153,2,2,BLACK);
  tft.fillRect(189,156,2,2,BLACK);
  tft.fillRect(192,156,2,2,BLACK);
  tft.fillRect(195,156,2,2,BLACK);
  tft.fillRect(198,156,2,2,BLACK);
  tft.fillRect(180,159,2,2,BLACK);
  tft.fillRect(183,159,2,2,BLACK);
  tft.fillRect(186,159,2,2,BLACK);
  tft.fillRect(189,159,2,2,BLACK);
  tft.fillRect(195,159,2,2,BLACK);
  tft.fillRect(198,159,2,2,BLACK);
  tft.fillRect(201,159,2,2,BLACK);
  tft.fillRect(180,162,2,2,BLACK);
  tft.fillRect(183,162,2,2,BLACK);
  tft.fillRect(186,162,2,2,BLACK);
  tft.fillRect(189,162,2,2,BLACK);
  tft.fillRect(195,162,2,2,BLACK);
  tft.fillRect(198,162,2,2,BLACK);
  tft.fillRect(201,162,2,2,BLACK);
  tft.fillRect(183,165,2,2,BLACK);
  tft.fillRect(186,165,2,2,BLACK);
  tft.fillRect(195,165,2,2,BLACK);
  tft.fillRect(198,165,2,2,BLACK);
}

void Right_Proppeler_For_Turn_Vent()
{
  tft.fillRect(280,144,2,2,WHITE);
  tft.fillRect(283,144,2,2,WHITE);
  tft.fillRect(292,144,2,2,WHITE);
  tft.fillRect(295,144,2,2,WHITE);
  tft.fillRect(277,147,2,2,WHITE);
  tft.fillRect(280,147,2,2,WHITE);
  tft.fillRect(283,147,2,2,WHITE);
  tft.fillRect(289,147,2,2,WHITE);
  tft.fillRect(292,147,2,2,WHITE);
  tft.fillRect(295,147,2,2,WHITE);
  tft.fillRect(298,147,2,2,WHITE);
  tft.fillRect(277,150,2,2,WHITE);
  tft.fillRect(280,150,2,2,WHITE);
  tft.fillRect(283,150,2,2,WHITE);
  tft.fillRect(289,150,2,2,WHITE);
  tft.fillRect(292,150,2,2,WHITE);
  tft.fillRect(295,150,2,2,WHITE);
  tft.fillRect(298,150,2,2,WHITE);
  tft.fillRect(280,153,2,2,WHITE);
  tft.fillRect(283,153,2,2,WHITE);
  tft.fillRect(286,153,2,2,WHITE);
  tft.fillRect(289,153,2,2,WHITE);
  tft.fillRect(286,156,2,2,WHITE);
  tft.fillRect(289,156,2,2,WHITE);
  tft.fillRect(292,156,2,2,WHITE);
  tft.fillRect(295,156,2,2,WHITE);
  tft.fillRect(277,159,2,2,WHITE);
  tft.fillRect(280,159,2,2,WHITE);
  tft.fillRect(283,159,2,2,WHITE);
  tft.fillRect(286,159,2,2,WHITE);
  tft.fillRect(292,159,2,2,WHITE);
  tft.fillRect(295,159,2,2,WHITE);
  tft.fillRect(298,159,2,2,WHITE);
  tft.fillRect(277,162,2,2,WHITE);
  tft.fillRect(280,162,2,2,WHITE);
  tft.fillRect(283,162,2,2,WHITE);
  tft.fillRect(286,162,2,2,WHITE);
  tft.fillRect(292,162,2,2,WHITE);
  tft.fillRect(295,162,2,2,WHITE);
  tft.fillRect(298,162,2,2,WHITE);
  tft.fillRect(280,165,2,2,WHITE);
  tft.fillRect(283,165,2,2,WHITE);
  tft.fillRect(292,165,2,2,WHITE);
  tft.fillRect(295,165,2,2,WHITE);
}

void No_Right_Proppeler_For_Turn_Vent()
{
  tft.fillRect(280,144,2,2,BLACK);
  tft.fillRect(283,144,2,2,BLACK);
  tft.fillRect(292,144,2,2,BLACK);
  tft.fillRect(295,144,2,2,BLACK);
  tft.fillRect(277,147,2,2,BLACK);
  tft.fillRect(280,147,2,2,BLACK);
  tft.fillRect(283,147,2,2,BLACK);
  tft.fillRect(289,147,2,2,BLACK);
  tft.fillRect(292,147,2,2,BLACK);
  tft.fillRect(295,147,2,2,BLACK);
  tft.fillRect(298,147,2,2,BLACK);
  tft.fillRect(277,150,2,2,BLACK);
  tft.fillRect(280,150,2,2,BLACK);
  tft.fillRect(283,150,2,2,BLACK);
  tft.fillRect(289,150,2,2,BLACK);
  tft.fillRect(292,150,2,2,BLACK);
  tft.fillRect(295,150,2,2,BLACK);
  tft.fillRect(298,150,2,2,BLACK);
  tft.fillRect(280,153,2,2,BLACK);
  tft.fillRect(283,153,2,2,BLACK);
  tft.fillRect(286,153,2,2,BLACK);
  tft.fillRect(289,153,2,2,BLACK);
  tft.fillRect(286,156,2,2,BLACK);
  tft.fillRect(289,156,2,2,BLACK);
  tft.fillRect(292,156,2,2,BLACK);
  tft.fillRect(295,156,2,2,BLACK);
  tft.fillRect(277,159,2,2,BLACK);
  tft.fillRect(280,159,2,2,BLACK);
  tft.fillRect(283,159,2,2,BLACK);
  tft.fillRect(286,159,2,2,BLACK);
  tft.fillRect(292,159,2,2,BLACK);
  tft.fillRect(295,159,2,2,BLACK);
  tft.fillRect(298,159,2,2,BLACK);
  tft.fillRect(277,162,2,2,BLACK);
  tft.fillRect(280,162,2,2,BLACK);
  tft.fillRect(283,162,2,2,BLACK);
  tft.fillRect(286,162,2,2,BLACK);
  tft.fillRect(292,162,2,2,BLACK);
  tft.fillRect(295,162,2,2,BLACK);
  tft.fillRect(298,162,2,2,BLACK);
  tft.fillRect(280,165,2,2,BLACK);
  tft.fillRect(283,165,2,2,BLACK);
  tft.fillRect(292,165,2,2,BLACK);
  tft.fillRect(295,165,2,2,BLACK);
}

void Off_Red_Indicator()
{
  tft.fillRect(281,288,49,4,RED);
}

void No_Off_Red_Indicator()
{
  tft.fillRect(281,288,49,4,BLACK);
}

void SYNC_Red_Indicator()
{
  tft.fillRect(151,288,49,4,RED);
}

void No_SYNC_Red_Indicator()
{
  tft.fillRect(151,288,49,4,BLACK);
}

void Car_Filter_Indicator()
{
  tft.fillRect(331,288,49,4,RED);
}

void No_Car_Filter_Indicator()
{
  tft.fillRect(331,288,49,4,BLACK);
}

void Left_Auto_Indicator()
{
  tft.fillRect(166,266,55,3,RED);
}

void No_Left_Auto_Indicator()
{
  tft.fillRect(166,266,55,3,BLACK);
}

void Right_Auto_Indicator()
{
  tft.fillRect(260,266,55,3,RED);
}

void No_Right_Auto_Indicator()
{
  tft.fillRect(260,266,55,3,BLACK);
}

void Hide_Left_Vent_If_Left_Auto_Pressed()
{
  //TOP LINE
  tft.drawLine(55,55,220,55,BLACK);
  //BOTTOM LINE
  tft.drawLine(0,264,220,264,BLACK);
  //VERTICAL LINE OF THE LEFT SIDE
  tft.drawLine(220,55,220,264,BLACK);
  //ARROW UP LEFT SIDE
  tft.drawTriangle(170,97,190,77,210,97,BLACK);
  tft.drawLine(170,97,210,97,BLACK);

  //ARROW DOWN LEFT SIDE
  tft.drawTriangle(210,212,190,232,170,212,BLACK);
  tft.drawLine(170,212,210,212,BLACK);
  tft.fillRect(155,5,68,48,BLACK);
}

void Hide_Right_Vent_If_Right_Auto_Pressed()
{
  //TOP LINE
  tft.drawLine(260,55,420,55,BLACK);
  //BOTTOM LINE
  tft.drawLine(260,264,475,264,BLACK);
  //VERTICAL LINE OF THE RIGHT SIDE
  tft.drawLine(260,55,260,264,BLACK);
  //ARROW UP RIGHT SIDE
  tft.drawTriangle(270,97,290,77,310,97,BLACK);
  tft.drawLine(270,97,310,97,BLACK);

  //ARROW DOWN RIGHT SIDE
  tft.drawTriangle(310,212,290,232,270,212,BLACK);
  tft.drawLine(270,212,310,212,BLACK);
  tft.fillRect(255,5,68,48,BLACK);
}

void Climate_Bar()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  Design_Of_The_Climate();
  Left_Temp();
  Right_Temp();
  TempsSigns();
  Auto_Button();
  Buttons_At_Bottom();
  Car_Symbol_For_Filtering();
  Left_Proppeler_For_Turn_Vent();
  Right_Proppeler_For_Turn_Vent();
  Left_Seat();
  Right_Seat();
  Left_Auto_Indicator();
  Right_Auto_Indicator();
}

void loop()
{
 State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem = digitalRead(Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem);
  if(State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem != Last_State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem) 
  {
    // if the state has changed, increment the counter
    if(State_Of_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem == HIGH) 
   {
      // if the current state is HIGH then the button
      // wend from off to on:
       Counter_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem++;
       Serial.println(Counter_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem);
       if(Counter_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem % 2 != 0)
        {
          buttonPanelEnabled = true;
          Home_Screen();
          //Climate_Bar();
          //Climatronic_On();
        }else if(Counter_Turn_On_And_Off_Engine_And_Turn_On_Color_Emblem % 2 == 0)
        {
          Switched_Screen();
          Climatronic_Lights_Off();
          buttonPanelEnabled = false;
          buttonLeftTemp = false;
          buttonRightTemp = false;
          buttonLeftProppeler = false;
          buttonRightProppeler = false;
          buttonLeftVent = false;
          buttonRightVent = false;
          buttonLeftVentOnOrOff = false;
          buttonRightVentOnOrOff = false;
          buttonLeftHeatingOnOrOff = false;
          buttonRightHeatingOnOrOff = false;
          buttonOffWholeClimateSys = false;
          buttonReturnHomeScreen = false;
          buttonClimaIsOnOrOff = false;
          buttonTurnOnClimatePanel = false;
          buttonSync = false;
          buttonCarFiltering = false;
          buttonLeftAutoPressed = false;
          buttonRightAutoPressed = false;
        }
     }
  }

  TSPoint ac = ts.getPoint();
  TSPoint left_temp = ts.getPoint();
  TSPoint right_temp = ts.getPoint();
  TSPoint left_vent = ts.getPoint(); 
  TSPoint right_vent = ts.getPoint();
  TSPoint left_vent_on_off = ts.getPoint();
  TSPoint right_vent_on_off = ts.getPoint();
  TSPoint left_heating = ts.getPoint();
  TSPoint right_heating = ts.getPoint();
  TSPoint button_off_cli_sys = ts.getPoint();
  TSPoint but_ret_home = ts.getPoint();
  TSPoint ac_on_off = ts.getPoint();
  TSPoint left_proppeler = ts.getPoint();
  TSPoint right_proppeler = ts.getPoint();
  TSPoint climate_panel = ts.getPoint();
  TSPoint button_sync = ts.getPoint();
  TSPoint car_filter_button = ts.getPoint();
  TSPoint left_auto_button = ts.getPoint();
  TSPoint right_auto_button = ts.getPoint();
  
  if(ac.z > ts.pressureThreshhold && buttonPanelEnabled == true)
 {
  ac.x = map(ac.x, TS_MINX, TS_MAXX ,tft.height(),0);
  ac.y = map(ac.y, TS_MAXY, TS_MINY, 0,tft.width());
  int t = ac.x;
  ac.x = ac.y;
  ac.y = t;
  //Z = p.z;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if(ac.x > 410 && ac.x < 485)
  {
   if(ac.y >= 140 && ac.y <= 192)
   {
    delay(300);
    buttonPanelEnabled = false;
    buttonLeftTemp = true;
    buttonRightTemp = true;
    buttonLeftProppeler = true;
    buttonRightProppeler = true;
    buttonLeftVentOnOrOff = true;
    buttonRightVentOnOrOff = true;
    buttonLeftHeatingOnOrOff = true;
    buttonRightHeatingOnOrOff = true;
    buttonOffWholeClimateSys = true;
    buttonReturnHomeScreen = true;
    buttonClimaIsOnOrOff = true;
    buttonSync = true;
    buttonCarFiltering = true;
    buttonLeftAutoPressed = false;
    buttonRightAutoPressed = false;
    Climate_Bar();
    
    //SAVING THE INDICATOR OF A/C IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_climate % 2 !=0)
    {
     Climate_Indicator_On();
    }

    //SAVING THE INDICATOR OF SYNC IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_sync % 2 !=0)
    {
     SYNC_Red_Indicator();
    }

    //SAVING THE INDICATOR OF FILTERING BUTTON IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_filter % 2 !=0)
    {
      Car_Filter_Indicator();
    }
    
    //SAVING THE INDICATOR OF VENTILATION OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(level_vent_left == 1 && level_vent_left % 1 == 0)
    {
     Left_Seat();
     Max_Cooling_Indicator_Left_Seat();
    }else
     if(level_vent_left == 2 && level_vent_left % 2 == 0)
     {
       Left_Seat();
       Mid_Cooling_Indicator_Left_Seat();
     }else
      if(level_vent_left == 3 && level_vent_left % 3 == 0)
      {
       Left_Seat();
       Min_Cooling_Indicator_Left_Seat();
      }else
       if(level_vent_left == 4 && level_vent_left % 4 == 0)
       {
        level_vent_left = 0;
        No_Cooling_Indicator_Left_Seat();
       }

     //SAVING THE INDICATOR OF VENTILATION OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED  
    if(level_vent_right == 1 && level_vent_right % 1 == 0)
    {
     Right_Seat();
     Max_Cooling_Indicator_Right_Seat();
    }else
     if(level_vent_right == 2 && level_vent_right % 2 == 0)
     {
       Right_Seat();
       Mid_Cooling_Indicator_Right_Seat();
     }else
      if(level_vent_right == 3 && level_vent_right % 3 == 0)
      {
       Right_Seat();
       Min_Cooling_Indicator_Right_Seat();
      }else
       if(level_vent_right == 4 && level_vent_right % 4 == 0)
       {
        level_vent_right = 0;
        No_Cooling_Indicator_Right_Seat();
       }

      //SAVING THE INDICATOR OF HEATING OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
     if(level_heat_left == 1 && level_heat_left % 1 == 0)
     {
      Left_Seat();
      Max_Heat_Indicator_Left_Seat();
     }else
     if(level_heat_left == 2 && level_heat_left % 2 == 0)
     {
       Left_Seat();
       Mid_Heat_Indicator_Left_Seat();
     }else
      if(level_heat_left == 3 && level_heat_left % 3 == 0)
      {
        Left_Seat();
        Min_Heat_Indicator_Left_Seat();
      }else
      if(level_heat_left == 4 && level_heat_left % 4 == 0)
      {
       level_heat_left = 0;
       No_Heat_Indicator_Left_Seat();
      }
      //SAVING THE INDICATOR OF HEATING OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
      if(level_heat_right == 1 && level_heat_right % 1 == 0)
      {
       Right_Seat();
       Max_Heat_Indicator_Right_Seat();
      }else
       if(level_heat_right == 2 && level_heat_right % 2 == 0)
       {
        Right_Seat();
        Mid_Heat_Indicator_Right_Seat();
       }else
        if(level_heat_right == 3 && level_heat_right % 3 == 0)
        {
         Right_Seat();
         Min_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 4 && level_heat_right % 4 == 0)
         {
          level_heat_right= 0;
          No_Heat_Indicator_Right_Seat();
         }
     }
 }else
  if(ac.x > 410 && ac.x < 485 && ac.y >= 140 && ac.y <= 192)
  {
    delay(300);
    buttonPanelEnabled = false;
    buttonLeftTemp = true;
    buttonRightTemp = true;
    buttonLeftProppeler = true;
    buttonRightProppeler = true;
    buttonLeftVentOnOrOff = true;
    buttonRightVentOnOrOff = true;
    buttonLeftHeatingOnOrOff = true;
    buttonRightHeatingOnOrOff = true;
    buttonOffWholeClimateSys = true;
    buttonReturnHomeScreen = true;
    buttonClimaIsOnOrOff = true;
    buttonSync = true;
    buttonCarFiltering = true;
    buttonLeftAutoPressed = false;
    buttonRightAutoPressed = false;
    Climate_Bar();
    
    //SAVING THE INDICATOR OF A/C IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_climate % 2 !=0)
    {
     Climate_Indicator_On();
    }

    //SAVING THE INDICATOR OF SYNC IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_sync % 2 !=0)
    {
     SYNC_Red_Indicator();
    }

    //SAVING THE INDICATOR OF FILTERING BUTTON IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_filter % 2 !=0)
    {
      Car_Filter_Indicator();
    }
    
    //SAVING THE INDICATOR OF VENTILATION OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(level_vent_left == 1 && level_vent_left % 1 == 0)
    {
     Left_Seat();
     Max_Cooling_Indicator_Left_Seat();
    }else
     if(level_vent_left == 2 && level_vent_left % 2 == 0)
     {
       Left_Seat();
       Mid_Cooling_Indicator_Left_Seat();
     }else
      if(level_vent_left == 3 && level_vent_left % 3 == 0)
      {
       Left_Seat();
       Min_Cooling_Indicator_Left_Seat();
      }else
       if(level_vent_left == 4 && level_vent_left % 4 == 0)
       {
        level_vent_left = 0;
        No_Cooling_Indicator_Left_Seat();
       }

    //SAVING THE INDICATOR OF VENTILATION OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED   
    if(level_vent_right == 1 && level_vent_right % 1 == 0)
    {
     Right_Seat();
     Max_Cooling_Indicator_Right_Seat();
    }else
     if(level_vent_right == 2 && level_vent_right % 2 == 0)
     {
       Right_Seat();
       Mid_Cooling_Indicator_Right_Seat();
     }else
      if(level_vent_right == 3 && level_vent_right % 3 == 0)
      {
       Right_Seat();
       Min_Cooling_Indicator_Right_Seat();
      }else
       if(level_vent_right == 4 && level_vent_right % 4 == 0)
       {
        level_vent_right = 0;
        No_Cooling_Indicator_Right_Seat();
       }

      //SAVING THE INDICATOR OF HEATING OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
      if(level_heat_left == 1 && level_heat_left % 1 == 0)
       {
        Left_Seat();
        Max_Heat_Indicator_Left_Seat();
       }else
        if(level_heat_left == 2 && level_heat_left % 2 == 0)
        {
          Left_Seat();
          Mid_Heat_Indicator_Left_Seat();
        }else
         if(level_heat_left == 3 && level_heat_left % 3 == 0)
         {
          Left_Seat();
          Min_Heat_Indicator_Left_Seat();
         }else
          if(level_heat_left == 4 && level_heat_left % 4 == 0)
          {
            level_heat_left = 0;
            No_Heat_Indicator_Left_Seat();
          }

      //SAVING THE INDICATOR OF HEATING OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED    
      if(level_heat_right == 1 && level_heat_right % 1 == 0)
        {
         Right_Seat();
         Max_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 2 && level_heat_right % 2 == 0)
         {
           Right_Seat();
           Mid_Heat_Indicator_Right_Seat();
         }else
         if(level_heat_right == 3 && level_heat_right % 3 == 0)
         {
          Right_Seat();
          Min_Heat_Indicator_Right_Seat();
         }else
          if(level_heat_right == 4 && level_heat_right % 4 == 0)
          {
            level_heat_right= 0;
            No_Heat_Indicator_Right_Seat();
          }    
     }   
  // SHOW VENT SETTINGS FOR LEFT SIDE IF RETURN BUTTON IS PRESSED
  if(ac.x > 410 && ac.x < 485 && left_vent_is_pressed == 1)
  {
   if(ac.y >= 140 && ac.y <= 192 && left_vent_is_pressed == 1)
   {
    delay(300);
    buttonPanelEnabled = false;
    buttonLeftTemp = true;
    buttonRightTemp = true;
    buttonLeftVent = false;
    buttonRightVent = false;
    buttonLeftProppeler = true;
    buttonRightProppeler = true;
    buttonLeftVentOnOrOff = true;
    buttonRightVentOnOrOff = true;
    buttonLeftHeatingOnOrOff = true;
    buttonRightHeatingOnOrOff = true;
    buttonOffWholeClimateSys = true;
    buttonReturnHomeScreen = true;
    buttonClimaIsOnOrOff = true;
    buttonSync = true;
    buttonCarFiltering = true;
    buttonLeftAutoPressed = true;
    if(left_auto_count == 0 && left_vent_is_pressed == 0)
      {
        buttonLeftAutoPressed = false;
        buttonLeftProppeler = true;
        Hide_Left_Vent_If_Left_Auto_Pressed();
        Left_Proppeler_For_Turn_Vent();
        Left_Auto_Indicator();   
      }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && vent_l < 10)
       {
        buttonLeftAutoPressed = true;
        buttonLeftProppeler = false;
        buttonLeftVent = true;
        Left_Vent();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
       }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && vent_l > 9)
       {
        buttonLeftAutoPressed = true;
        buttonLeftProppeler = false;
        buttonLeftVent = true;
        Left_Vent_Two_Digits();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
       }else
        if(left_auto_count == 1 && left_vent_is_pressed == 1)
        {
          buttonLeftAutoPressed = false;
          buttonLeftProppeler = true;
          Hide_Left_Vent_If_Left_Auto_Pressed();
          Left_Proppeler_For_Turn_Vent();
          Left_Auto_Indicator();
          left_vent_is_pressed = 1;
          left_auto_count = 0;
        }
     
    //SAVING THE INDICATOR OF A/C IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_climate % 2 !=0)
    {
     Climate_Indicator_On();
    }

    //SAVING THE INDICATOR OF SYNC IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_sync % 2 !=0)
    {
     SYNC_Red_Indicator();
    }

    //SAVING THE INDICATOR OF FILTERING BUTTON IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_filter % 2 !=0)
    {
      Car_Filter_Indicator();
    }
    
    //SAVING THE INDICATOR OF VENTILATION OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(level_vent_left == 1 && level_vent_left % 1 == 0)
    {
     Left_Seat();
     Max_Cooling_Indicator_Left_Seat();
    }else
     if(level_vent_left == 2 && level_vent_left % 2 == 0)
     {
       Left_Seat();
       Mid_Cooling_Indicator_Left_Seat();
     }else
      if(level_vent_left == 3 && level_vent_left % 3 == 0)
      {
       Left_Seat();
       Min_Cooling_Indicator_Left_Seat();
      }else
       if(level_vent_left == 4 && level_vent_left % 4 == 0)
       {
        level_vent_left = 0;
        No_Cooling_Indicator_Left_Seat();
       }

     //SAVING THE INDICATOR OF VENTILATION OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED  
    if(level_vent_right == 1 && level_vent_right % 1 == 0)
    {
     Right_Seat();
     Max_Cooling_Indicator_Right_Seat();
    }else
     if(level_vent_right == 2 && level_vent_right % 2 == 0)
     {
       Right_Seat();
       Mid_Cooling_Indicator_Right_Seat();
     }else
      if(level_vent_right == 3 && level_vent_right % 3 == 0)
      {
       Right_Seat();
       Min_Cooling_Indicator_Right_Seat();
      }else
       if(level_vent_right == 4 && level_vent_right % 4 == 0)
       {
        level_vent_right = 0;
        No_Cooling_Indicator_Right_Seat();
       }

      //SAVING THE INDICATOR OF HEATING OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
     if(level_heat_left == 1 && level_heat_left % 1 == 0)
     {
      Left_Seat();
      Max_Heat_Indicator_Left_Seat();
     }else
     if(level_heat_left == 2 && level_heat_left % 2 == 0)
     {
       Left_Seat();
       Mid_Heat_Indicator_Left_Seat();
     }else
      if(level_heat_left == 3 && level_heat_left % 3 == 0)
      {
        Left_Seat();
        Min_Heat_Indicator_Left_Seat();
      }else
      if(level_heat_left == 4 && level_heat_left % 4 == 0)
      {
       level_heat_left = 0;
       No_Heat_Indicator_Left_Seat();
      }
      //SAVING THE INDICATOR OF HEATING OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
      if(level_heat_right == 1 && level_heat_right % 1 == 0)
      {
       Right_Seat();
       Max_Heat_Indicator_Right_Seat();
      }else
       if(level_heat_right == 2 && level_heat_right % 2 == 0)
       {
        Right_Seat();
        Mid_Heat_Indicator_Right_Seat();
       }else
        if(level_heat_right == 3 && level_heat_right % 3 == 0)
        {
         Right_Seat();
         Min_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 4 && level_heat_right % 4 == 0)
         {
          level_heat_right= 0;
          No_Heat_Indicator_Right_Seat();
         }
     }
 }else
  if(ac.x > 410 && ac.x < 485 && ac.y >= 140 && ac.y <= 192 && left_vent_is_pressed == 1)
  {
    delay(300);
    buttonPanelEnabled = false;
    buttonLeftTemp = true;
    buttonRightTemp = true;
    buttonLeftVent = false;
    buttonRightVent = false;
    buttonLeftProppeler = true;
    buttonRightProppeler = true;
    buttonLeftVentOnOrOff = true;
    buttonRightVentOnOrOff = true;
    buttonLeftHeatingOnOrOff = true;
    buttonRightHeatingOnOrOff = true;
    buttonOffWholeClimateSys = true;
    buttonReturnHomeScreen = true;
    buttonClimaIsOnOrOff = true;
    buttonSync = true;
    buttonCarFiltering = true;
    buttonLeftAutoPressed = true;
    if(left_auto_count == 0 && left_vent_is_pressed == 0)
      {
        buttonLeftAutoPressed = false;
        buttonLeftProppeler = true;
        Hide_Left_Vent_If_Left_Auto_Pressed();
        Left_Proppeler_For_Turn_Vent();
        Left_Auto_Indicator();   
      }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && vent_l < 10)
       {
        buttonLeftAutoPressed = true;
        buttonLeftProppeler = false;
        buttonLeftVent = true;
        Left_Vent();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
       }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && vent_l > 9)
       {
        buttonLeftAutoPressed = true;
        buttonLeftProppeler = false;
        buttonLeftVent = true;
        Left_Vent_Two_Digits();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
       }else
        if(left_auto_count == 1 && left_vent_is_pressed == 1)
        {
          buttonLeftAutoPressed = false;
          buttonLeftProppeler = true;
          Hide_Left_Vent_If_Left_Auto_Pressed();
          Left_Proppeler_For_Turn_Vent();
          Left_Auto_Indicator();
          left_vent_is_pressed = 1;
          left_auto_count = 0;
        }
       
    //SAVING THE INDICATOR OF A/C IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_climate % 2 !=0)
    {
     Climate_Indicator_On();
    }

    //SAVING THE INDICATOR OF SYNC IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_sync % 2 !=0)
    {
     SYNC_Red_Indicator();
    }

    //SAVING THE INDICATOR OF FILTERING BUTTON IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_filter % 2 !=0)
    {
      Car_Filter_Indicator();
    }
    
    //SAVING THE INDICATOR OF VENTILATION OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(level_vent_left == 1 && level_vent_left % 1 == 0)
    {
     Left_Seat();
     Max_Cooling_Indicator_Left_Seat();
    }else
     if(level_vent_left == 2 && level_vent_left % 2 == 0)
     {
       Left_Seat();
       Mid_Cooling_Indicator_Left_Seat();
     }else
      if(level_vent_left == 3 && level_vent_left % 3 == 0)
      {
       Left_Seat();
       Min_Cooling_Indicator_Left_Seat();
      }else
       if(level_vent_left == 4 && level_vent_left % 4 == 0)
       {
        level_vent_left = 0;
        No_Cooling_Indicator_Left_Seat();
       }

    //SAVING THE INDICATOR OF VENTILATION OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED   
    if(level_vent_right == 1 && level_vent_right % 1 == 0)
    {
     Right_Seat();
     Max_Cooling_Indicator_Right_Seat();
    }else
     if(level_vent_right == 2 && level_vent_right % 2 == 0)
     {
       Right_Seat();
       Mid_Cooling_Indicator_Right_Seat();
     }else
      if(level_vent_right == 3 && level_vent_right % 3 == 0)
      {
       Right_Seat();
       Min_Cooling_Indicator_Right_Seat();
      }else
       if(level_vent_right == 4 && level_vent_right % 4 == 0)
       {
        level_vent_right = 0;
        No_Cooling_Indicator_Right_Seat();
       }

      //SAVING THE INDICATOR OF HEATING OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
      if(level_heat_left == 1 && level_heat_left % 1 == 0)
       {
        Left_Seat();
        Max_Heat_Indicator_Left_Seat();
       }else
        if(level_heat_left == 2 && level_heat_left % 2 == 0)
        {
          Left_Seat();
          Mid_Heat_Indicator_Left_Seat();
        }else
         if(level_heat_left == 3 && level_heat_left % 3 == 0)
         {
          Left_Seat();
          Min_Heat_Indicator_Left_Seat();
         }else
          if(level_heat_left == 4 && level_heat_left % 4 == 0)
          {
            level_heat_left = 0;
            No_Heat_Indicator_Left_Seat();
          }

      //SAVING THE INDICATOR OF HEATING OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED    
      if(level_heat_right == 1 && level_heat_right % 1 == 0)
        {
         Right_Seat();
         Max_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 2 && level_heat_right % 2 == 0)
         {
           Right_Seat();
           Mid_Heat_Indicator_Right_Seat();
         }else
         if(level_heat_right == 3 && level_heat_right % 3 == 0)
         {
          Right_Seat();
          Min_Heat_Indicator_Right_Seat();
         }else
          if(level_heat_right == 4 && level_heat_right % 4 == 0)
          {
            level_heat_right= 0;
            No_Heat_Indicator_Right_Seat();
          }    
     }
  // SHOW VENT SETTINGS FOR RIGHT SIDE IF RETURN BUTTON IS PRESSED
  if(ac.x > 410 && ac.x < 485 && right_vent_is_pressed == 1)
  {
   if(ac.y >= 140 && ac.y <= 192 && right_vent_is_pressed == 1)
   {
    delay(300);
    buttonPanelEnabled = false;
    buttonLeftTemp = true;
    buttonRightTemp = true;
    buttonLeftVent = false;
    buttonRightVent = false;
    buttonLeftProppeler = true;
    buttonRightProppeler = true;
    buttonLeftVentOnOrOff = true;
    buttonRightVentOnOrOff = true;
    buttonLeftHeatingOnOrOff = true;
    buttonRightHeatingOnOrOff = true;
    buttonOffWholeClimateSys = true;
    buttonReturnHomeScreen = true;
    buttonClimaIsOnOrOff = true;
    buttonSync = true;
    buttonCarFiltering = true;
    buttonRightAutoPressed = true;
    if(right_auto_count == 0 && right_vent_is_pressed == 0)
      {
        buttonRightAutoPressed = false;
        buttonRightProppeler = true;
        Hide_Right_Vent_If_Right_Auto_Pressed();
        Right_Proppeler_For_Turn_Vent();
        Right_Auto_Indicator();   
      }else
       if(right_auto_count == 0 && right_vent_is_pressed == 1 && vent_r < 10)
       {
        buttonRightAutoPressed = true;
        buttonRightProppeler = false;
        buttonRightVent = true;
        Right_Vent();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
       if(right_auto_count == 0 && right_vent_is_pressed == 1 && vent_r > 9)
       {
        buttonRightAutoPressed = true;
        buttonRightProppeler = false;
        buttonRightVent = true;
        Right_Vent_Two_Digits();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
        if(right_auto_count == 1 && right_vent_is_pressed == 1)
        {
          buttonRightAutoPressed = false;
          buttonRightProppeler = true;
          Hide_Right_Vent_If_Right_Auto_Pressed();
          Right_Proppeler_For_Turn_Vent();
          Right_Auto_Indicator();
          right_vent_is_pressed = 1;
          right_auto_count = 0;
        }
    
    //SAVING THE INDICATOR OF A/C IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_climate % 2 !=0)
    {
     Climate_Indicator_On();
    }

    //SAVING THE INDICATOR OF SYNC IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_sync % 2 !=0)
    {
     SYNC_Red_Indicator();
    }

    //SAVING THE INDICATOR OF FILTERING BUTTON IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_filter % 2 !=0)
    {
      Car_Filter_Indicator();
    }
    
    //SAVING THE INDICATOR OF VENTILATION OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(level_vent_left == 1 && level_vent_left % 1 == 0)
    {
     Left_Seat();
     Max_Cooling_Indicator_Left_Seat();
    }else
     if(level_vent_left == 2 && level_vent_left % 2 == 0)
     {
       Left_Seat();
       Mid_Cooling_Indicator_Left_Seat();
     }else
      if(level_vent_left == 3 && level_vent_left % 3 == 0)
      {
       Left_Seat();
       Min_Cooling_Indicator_Left_Seat();
      }else
       if(level_vent_left == 4 && level_vent_left % 4 == 0)
       {
        level_vent_left = 0;
        No_Cooling_Indicator_Left_Seat();
       }

     //SAVING THE INDICATOR OF VENTILATION OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED  
    if(level_vent_right == 1 && level_vent_right % 1 == 0)
    {
     Right_Seat();
     Max_Cooling_Indicator_Right_Seat();
    }else
     if(level_vent_right == 2 && level_vent_right % 2 == 0)
     {
       Right_Seat();
       Mid_Cooling_Indicator_Right_Seat();
     }else
      if(level_vent_right == 3 && level_vent_right % 3 == 0)
      {
       Right_Seat();
       Min_Cooling_Indicator_Right_Seat();
      }else
       if(level_vent_right == 4 && level_vent_right % 4 == 0)
       {
        level_vent_right = 0;
        No_Cooling_Indicator_Right_Seat();
       }

      //SAVING THE INDICATOR OF HEATING OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
     if(level_heat_left == 1 && level_heat_left % 1 == 0)
     {
      Left_Seat();
      Max_Heat_Indicator_Left_Seat();
     }else
     if(level_heat_left == 2 && level_heat_left % 2 == 0)
     {
       Left_Seat();
       Mid_Heat_Indicator_Left_Seat();
     }else
      if(level_heat_left == 3 && level_heat_left % 3 == 0)
      {
        Left_Seat();
        Min_Heat_Indicator_Left_Seat();
      }else
      if(level_heat_left == 4 && level_heat_left % 4 == 0)
      {
       level_heat_left = 0;
       No_Heat_Indicator_Left_Seat();
      }
      //SAVING THE INDICATOR OF HEATING OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
      if(level_heat_right == 1 && level_heat_right % 1 == 0)
      {
       Right_Seat();
       Max_Heat_Indicator_Right_Seat();
      }else
       if(level_heat_right == 2 && level_heat_right % 2 == 0)
       {
        Right_Seat();
        Mid_Heat_Indicator_Right_Seat();
       }else
        if(level_heat_right == 3 && level_heat_right % 3 == 0)
        {
         Right_Seat();
         Min_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 4 && level_heat_right % 4 == 0)
         {
          level_heat_right= 0;
          No_Heat_Indicator_Right_Seat();
         }
     }
 }else
  if(ac.x > 410 && ac.x < 485 && ac.y >= 140 && ac.y <= 192 && right_vent_is_pressed == 1)
  {
    delay(300);
    buttonPanelEnabled = false;
    buttonLeftTemp = true;
    buttonRightTemp = true;
    buttonLeftVent = false;
    buttonRightVent = false;
    buttonLeftProppeler = true;
    buttonRightProppeler = true;
    buttonLeftVentOnOrOff = true;
    buttonRightVentOnOrOff = true;
    buttonLeftHeatingOnOrOff = true;
    buttonRightHeatingOnOrOff = true;
    buttonOffWholeClimateSys = true;
    buttonReturnHomeScreen = true;
    buttonClimaIsOnOrOff = true;
    buttonSync = true;
    buttonCarFiltering = true;
    buttonRightAutoPressed = true;
    if(right_auto_count == 0 && right_vent_is_pressed == 0)
      {
        buttonRightAutoPressed = false;
        buttonRightProppeler = true;
        Hide_Right_Vent_If_Right_Auto_Pressed();
        Right_Proppeler_For_Turn_Vent();
        Right_Auto_Indicator();   
      }else
       if(right_auto_count == 0 && right_vent_is_pressed == 1 && vent_r < 10)
       {
        buttonRightAutoPressed = true;
        buttonRightProppeler = false;
        buttonRightVent = true;
        Right_Vent();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
       if(right_auto_count == 0 && right_vent_is_pressed == 1 && vent_r > 9)
       {
        buttonRightAutoPressed = true;
        buttonRightProppeler = false;
        buttonRightVent = true;
        Right_Vent_Two_Digits();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
        if(right_auto_count == 1 && right_vent_is_pressed == 1)
        {
          buttonRightAutoPressed = false;
          buttonRightProppeler = true;
          Hide_Right_Vent_If_Right_Auto_Pressed();
          Right_Proppeler_For_Turn_Vent();
          Right_Auto_Indicator();
          right_vent_is_pressed = 1;
          right_auto_count = 0;
        }
    
    //SAVING THE INDICATOR OF A/C IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_climate % 2 !=0)
    {
     Climate_Indicator_On();
    }

    //SAVING THE INDICATOR OF SYNC IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_sync % 2 !=0)
    {
     SYNC_Red_Indicator();
    }

    //SAVING THE INDICATOR OF FILTERING BUTTON IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_filter % 2 !=0)
    {
      Car_Filter_Indicator();
    }
    
    //SAVING THE INDICATOR OF VENTILATION OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(level_vent_left == 1 && level_vent_left % 1 == 0)
    {
     Left_Seat();
     Max_Cooling_Indicator_Left_Seat();
    }else
     if(level_vent_left == 2 && level_vent_left % 2 == 0)
     {
       Left_Seat();
       Mid_Cooling_Indicator_Left_Seat();
     }else
      if(level_vent_left == 3 && level_vent_left % 3 == 0)
      {
       Left_Seat();
       Min_Cooling_Indicator_Left_Seat();
      }else
       if(level_vent_left == 4 && level_vent_left % 4 == 0)
       {
        level_vent_left = 0;
        No_Cooling_Indicator_Left_Seat();
       }

    //SAVING THE INDICATOR OF VENTILATION OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED   
    if(level_vent_right == 1 && level_vent_right % 1 == 0)
    {
     Right_Seat();
     Max_Cooling_Indicator_Right_Seat();
    }else
     if(level_vent_right == 2 && level_vent_right % 2 == 0)
     {
       Right_Seat();
       Mid_Cooling_Indicator_Right_Seat();
     }else
      if(level_vent_right == 3 && level_vent_right % 3 == 0)
      {
       Right_Seat();
       Min_Cooling_Indicator_Right_Seat();
      }else
       if(level_vent_right == 4 && level_vent_right % 4 == 0)
       {
        level_vent_right = 0;
        No_Cooling_Indicator_Right_Seat();
       }

      //SAVING THE INDICATOR OF HEATING OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
      if(level_heat_left == 1 && level_heat_left % 1 == 0)
       {
        Left_Seat();
        Max_Heat_Indicator_Left_Seat();
       }else
        if(level_heat_left == 2 && level_heat_left % 2 == 0)
        {
          Left_Seat();
          Mid_Heat_Indicator_Left_Seat();
        }else
         if(level_heat_left == 3 && level_heat_left % 3 == 0)
         {
          Left_Seat();
          Min_Heat_Indicator_Left_Seat();
         }else
          if(level_heat_left == 4 && level_heat_left % 4 == 0)
          {
            level_heat_left = 0;
            No_Heat_Indicator_Left_Seat();
          }

      //SAVING THE INDICATOR OF HEATING OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED    
      if(level_heat_right == 1 && level_heat_right % 1 == 0)
        {
         Right_Seat();
         Max_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 2 && level_heat_right % 2 == 0)
         {
           Right_Seat();
           Mid_Heat_Indicator_Right_Seat();
         }else
         if(level_heat_right == 3 && level_heat_right % 3 == 0)
         {
          Right_Seat();
          Min_Heat_Indicator_Right_Seat();
         }else
          if(level_heat_right == 4 && level_heat_right % 4 == 0)
          {
            level_heat_right= 0;
            No_Heat_Indicator_Right_Seat();
          }    
     }
  // SHOW VENT SETTINGS FOR BOTH LEFT AND RIGHT SIDES IF RETURN BUTTON IS PRESSED 
  if(ac.x > 410 && ac.x < 485 && left_vent_is_pressed == 1 && right_vent_is_pressed == 1)
  {
   if(ac.y >= 140 && ac.y <= 192 && left_vent_is_pressed == 1 && right_vent_is_pressed == 1)
   {
    delay(300);
    buttonPanelEnabled = false;
    buttonLeftTemp = true;
    buttonRightTemp = true;
    buttonLeftVent = false;
    buttonRightVent = false;
    buttonLeftProppeler = true;
    buttonRightProppeler = true;
    buttonLeftVentOnOrOff = true;
    buttonRightVentOnOrOff = true;
    buttonLeftHeatingOnOrOff = true;
    buttonRightHeatingOnOrOff = true;
    buttonOffWholeClimateSys = true;
    buttonReturnHomeScreen = true;
    buttonClimaIsOnOrOff = true;
    buttonSync = true;
    buttonCarFiltering = true;
    buttonLeftAutoPressed = true;
    buttonRightAutoPressed = true;
    if(left_auto_count == 0 && left_vent_is_pressed == 0 && right_auto_count == 0 && right_vent_is_pressed == 0 )
      {
        buttonLeftAutoPressed = false;
        buttonRightAutoPressed = false;
        buttonLeftProppeler = true;
        buttonRightProppeler = true;
        Hide_Left_Vent_If_Left_Auto_Pressed();
        Left_Proppeler_For_Turn_Vent();
        Left_Auto_Indicator();
        Hide_Right_Vent_If_Right_Auto_Pressed();
        Right_Proppeler_For_Turn_Vent();
        Right_Auto_Indicator();   
      }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && right_auto_count == 0 && right_vent_is_pressed == 1 && vent_l < 10 && vent_r < 10)
       {
        buttonLeftAutoPressed = true;
        buttonRightAutoPressed = true;
        buttonLeftProppeler = false;
        buttonRightProppeler = false;
        buttonLeftVent = true;
        buttonRightVent = true;
        Left_Vent();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
        Right_Vent();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && right_auto_count == 0 && right_vent_is_pressed == 1 && vent_l > 9 && vent_r > 9)
       {
        buttonLeftAutoPressed = true;
        buttonRightAutoPressed = true;
        buttonLeftProppeler = false;
        buttonRightProppeler = false;
        buttonLeftVent = true;
        buttonRightVent = true;
        Left_Vent_Two_Digits();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
        Right_Vent_Two_Digits();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
       if(left_vent_is_pressed == 0 && right_vent_is_pressed == 0)
       {
        buttonLeftAutoPressed = false;
        buttonRightAutoPressed = false;
        buttonLeftProppeler = true;
        buttonRightProppeler = true;
        Hide_Left_Vent_If_Left_Auto_Pressed();
        Left_Proppeler_For_Turn_Vent();
        Left_Auto_Indicator();
        Hide_Right_Vent_If_Right_Auto_Pressed();
        Right_Proppeler_For_Turn_Vent();
        Right_Auto_Indicator();
        left_vent_is_pressed = 1;
        left_auto_count = 0;
        right_vent_is_pressed = 1;
        right_auto_count = 0;
       }
    
    //SAVING THE INDICATOR OF A/C IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_climate % 2 !=0)
    {
     Climate_Indicator_On();
    }

    //SAVING THE INDICATOR OF SYNC IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_sync % 2 !=0)
    {
     SYNC_Red_Indicator();
    }

    //SAVING THE INDICATOR OF FILTERING BUTTON IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_filter % 2 !=0)
    {
      Car_Filter_Indicator();
    }
    
    //SAVING THE INDICATOR OF VENTILATION OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(level_vent_left == 1 && level_vent_left % 1 == 0)
    {
     Left_Seat();
     Max_Cooling_Indicator_Left_Seat();
    }else
     if(level_vent_left == 2 && level_vent_left % 2 == 0)
     {
       Left_Seat();
       Mid_Cooling_Indicator_Left_Seat();
     }else
      if(level_vent_left == 3 && level_vent_left % 3 == 0)
      {
       Left_Seat();
       Min_Cooling_Indicator_Left_Seat();
      }else
       if(level_vent_left == 4 && level_vent_left % 4 == 0)
       {
        level_vent_left = 0;
        No_Cooling_Indicator_Left_Seat();
       }

     //SAVING THE INDICATOR OF VENTILATION OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED  
    if(level_vent_right == 1 && level_vent_right % 1 == 0)
    {
     Right_Seat();
     Max_Cooling_Indicator_Right_Seat();
    }else
     if(level_vent_right == 2 && level_vent_right % 2 == 0)
     {
       Right_Seat();
       Mid_Cooling_Indicator_Right_Seat();
     }else
      if(level_vent_right == 3 && level_vent_right % 3 == 0)
      {
       Right_Seat();
       Min_Cooling_Indicator_Right_Seat();
      }else
       if(level_vent_right == 4 && level_vent_right % 4 == 0)
       {
        level_vent_right = 0;
        No_Cooling_Indicator_Right_Seat();
       }

      //SAVING THE INDICATOR OF HEATING OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
     if(level_heat_left == 1 && level_heat_left % 1 == 0)
     {
      Left_Seat();
      Max_Heat_Indicator_Left_Seat();
     }else
     if(level_heat_left == 2 && level_heat_left % 2 == 0)
     {
       Left_Seat();
       Mid_Heat_Indicator_Left_Seat();
     }else
      if(level_heat_left == 3 && level_heat_left % 3 == 0)
      {
        Left_Seat();
        Min_Heat_Indicator_Left_Seat();
      }else
      if(level_heat_left == 4 && level_heat_left % 4 == 0)
      {
       level_heat_left = 0;
       No_Heat_Indicator_Left_Seat();
      }
      //SAVING THE INDICATOR OF HEATING OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
      if(level_heat_right == 1 && level_heat_right % 1 == 0)
      {
       Right_Seat();
       Max_Heat_Indicator_Right_Seat();
      }else
       if(level_heat_right == 2 && level_heat_right % 2 == 0)
       {
        Right_Seat();
        Mid_Heat_Indicator_Right_Seat();
       }else
        if(level_heat_right == 3 && level_heat_right % 3 == 0)
        {
         Right_Seat();
         Min_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 4 && level_heat_right % 4 == 0)
         {
          level_heat_right= 0;
          No_Heat_Indicator_Right_Seat();
         }
     }
 }else
  if(ac.x > 410 && ac.x < 485 && ac.y >= 140 && ac.y <= 192 && left_vent_is_pressed == 1 && right_vent_is_pressed == 1)
  {
    delay(300);
    buttonPanelEnabled = false;
    buttonLeftTemp = true;
    buttonRightTemp = true;
    buttonLeftVent = false;
    buttonRightVent = false;
    buttonLeftProppeler = true;
    buttonRightProppeler = true;
    buttonLeftVentOnOrOff = true;
    buttonRightVentOnOrOff = true;
    buttonLeftHeatingOnOrOff = true;
    buttonRightHeatingOnOrOff = true;
    buttonOffWholeClimateSys = true;
    buttonReturnHomeScreen = true;
    buttonClimaIsOnOrOff = true;
    buttonSync = true;
    buttonCarFiltering = true;
    buttonLeftAutoPressed = true;
    buttonRightAutoPressed = true;
    if(left_auto_count == 0 && left_vent_is_pressed == 0 && right_auto_count == 0 && right_vent_is_pressed == 0 )
      {
        buttonLeftAutoPressed = false;
        buttonRightAutoPressed = false;
        buttonLeftProppeler = true;
        buttonRightProppeler = true;
        Hide_Left_Vent_If_Left_Auto_Pressed();
        Left_Proppeler_For_Turn_Vent();
        Left_Auto_Indicator();
        Hide_Right_Vent_If_Right_Auto_Pressed();
        Right_Proppeler_For_Turn_Vent();
        Right_Auto_Indicator();   
      }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && right_auto_count == 0 && right_vent_is_pressed == 1 && vent_l < 10 && vent_r < 10)
       {
        buttonLeftAutoPressed = true;
        buttonRightAutoPressed = true;
        buttonLeftProppeler = false;
        buttonRightProppeler = false;
        buttonLeftVent = true;
        buttonRightVent = true;
        Left_Vent();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
        Right_Vent();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && right_auto_count == 0 && right_vent_is_pressed == 1 && vent_l > 9 && vent_r > 9)
       {
        buttonLeftAutoPressed = true;
        buttonRightAutoPressed = true;
        buttonLeftProppeler = false;
        buttonRightProppeler = false;
        buttonLeftVent = true;
        buttonRightVent = true;
        Left_Vent_Two_Digits();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
        Right_Vent_Two_Digits();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
       if(left_vent_is_pressed == 0 && right_vent_is_pressed == 0)
       {
        buttonLeftAutoPressed = false;
        buttonRightAutoPressed = false;
        buttonLeftProppeler = true;
        buttonRightProppeler = true;
        Hide_Left_Vent_If_Left_Auto_Pressed();
        Left_Proppeler_For_Turn_Vent();
        Left_Auto_Indicator();
        Hide_Right_Vent_If_Right_Auto_Pressed();
        Right_Proppeler_For_Turn_Vent();
        Right_Auto_Indicator();
        left_vent_is_pressed = 1;
        left_auto_count = 0;
        right_vent_is_pressed = 1;
        right_auto_count = 0;
       }
   
    //SAVING THE INDICATOR OF A/C IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_climate % 2 !=0)
    {
     Climate_Indicator_On();
    }

    //SAVING THE INDICATOR OF SYNC IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_sync % 2 !=0)
    {
     SYNC_Red_Indicator();
    }

    //SAVING THE INDICATOR OF FILTERING BUTTON IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(count_filter % 2 !=0)
    {
      Car_Filter_Indicator();
    }
    
    //SAVING THE INDICATOR OF VENTILATION OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED
    if(level_vent_left == 1 && level_vent_left % 1 == 0)
    {
     Left_Seat();
     Max_Cooling_Indicator_Left_Seat();
    }else
     if(level_vent_left == 2 && level_vent_left % 2 == 0)
     {
       Left_Seat();
       Mid_Cooling_Indicator_Left_Seat();
     }else
      if(level_vent_left == 3 && level_vent_left % 3 == 0)
      {
       Left_Seat();
       Min_Cooling_Indicator_Left_Seat();
      }else
       if(level_vent_left == 4 && level_vent_left % 4 == 0)
       {
        level_vent_left = 0;
        No_Cooling_Indicator_Left_Seat();
       }

    //SAVING THE INDICATOR OF VENTILATION OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED   
    if(level_vent_right == 1 && level_vent_right % 1 == 0)
    {
     Right_Seat();
     Max_Cooling_Indicator_Right_Seat();
    }else
     if(level_vent_right == 2 && level_vent_right % 2 == 0)
     {
       Right_Seat();
       Mid_Cooling_Indicator_Right_Seat();
     }else
      if(level_vent_right == 3 && level_vent_right % 3 == 0)
      {
       Right_Seat();
       Min_Cooling_Indicator_Right_Seat();
      }else
       if(level_vent_right == 4 && level_vent_right % 4 == 0)
       {
        level_vent_right = 0;
        No_Cooling_Indicator_Right_Seat();
       }

      //SAVING THE INDICATOR OF HEATING OF LEFT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED 
      if(level_heat_left == 1 && level_heat_left % 1 == 0)
       {
        Left_Seat();
        Max_Heat_Indicator_Left_Seat();
       }else
        if(level_heat_left == 2 && level_heat_left % 2 == 0)
        {
          Left_Seat();
          Mid_Heat_Indicator_Left_Seat();
        }else
         if(level_heat_left == 3 && level_heat_left % 3 == 0)
         {
          Left_Seat();
          Min_Heat_Indicator_Left_Seat();
         }else
          if(level_heat_left == 4 && level_heat_left % 4 == 0)
          {
            level_heat_left = 0;;
            No_Heat_Indicator_Left_Seat();
          }

      //SAVING THE INDICATOR OF HEATING OF RIGHT SEAT IF RETURN HOME SCREEN BUTTON IS PRESSED    
      if(level_heat_right == 1 && level_heat_right % 1 == 0)
        {
         Right_Seat();
         Max_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 2 && level_heat_right % 2 == 0)
         {
           Right_Seat();
           Mid_Heat_Indicator_Right_Seat();
         }else
         if(level_heat_right == 3 && level_heat_right % 3 == 0)
         {
          Right_Seat();
          Min_Heat_Indicator_Right_Seat();
         }else
          if(level_heat_right == 4 && level_heat_right % 4 == 0)
          {
            level_heat_right= 0;
            No_Heat_Indicator_Right_Seat();
          }    
     }
 }
 //LEFT PROPELLER SYMBOL FOR TURNING THE VENTILATION SETTINGS
  if(left_proppeler.z >  ts.pressureThreshhold && buttonLeftProppeler == true)
 {
  left_proppeler.x = map(left_proppeler.x, TS_MINX, TS_MAXX ,tft.height(),0);
  left_proppeler.y = map(left_proppeler.y, TS_MAXY, TS_MINY, 0,tft.width());
  int t = left_proppeler.x;
  left_proppeler.x = left_proppeler.y;
  left_proppeler.y = t;
  //Z = p.z;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if(left_proppeler.x > 156 && left_proppeler.x < 205)
  {
    if(left_proppeler.y >= 140 && left_proppeler.y <= 190)
    {
      delay(200);
      left_vent_is_pressed = 1;
      left_auto_count = 0;
      buttonLeftVent = true;
      buttonLeftAutoPressed = true;
      Left_Arrows_Up_And_Down();
      Propeller_Left();
      No_Left_Proppeler_For_Turn_Vent();
      No_Left_Auto_Indicator();
      if(left_auto_count == 0 && left_vent_is_pressed == 0)
      {
        buttonLeftAutoPressed = false;
        buttonLeftProppeler = true;
        Hide_Left_Vent_If_Left_Auto_Pressed();
        Left_Proppeler_For_Turn_Vent();
        Left_Auto_Indicator();   
      }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && vent_l < 10)
       {
        buttonLeftAutoPressed = true;
        buttonLeftProppeler = false;
        Left_Vent();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
       }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && vent_l > 9)
       {
        buttonLeftAutoPressed = true;
        buttonLeftProppeler = false;
        Left_Vent_Two_Digits();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
       }
        if(left_auto_count == 1 && left_vent_is_pressed == 1)
        {
          buttonLeftAutoPressed = false;
          buttonLeftProppeler = true;
          Hide_Left_Vent_If_Left_Auto_Pressed();
          Left_Proppeler_For_Turn_Vent();
          Left_Auto_Indicator();
          left_vent_is_pressed = 0;
          left_auto_count = 0;
        }
    }
  }else
   if(left_proppeler.x > 156 && left_proppeler.x < 205 && left_proppeler.y >= 140 && left_proppeler.y <= 190)
   {
    delay(200);
    left_vent_is_pressed = 1;
    left_auto_count = 0;
    buttonLeftVent = true;
    buttonLeftAutoPressed = true;
    Left_Arrows_Up_And_Down();
    Propeller_Left();
    No_Left_Proppeler_For_Turn_Vent();
    No_Left_Auto_Indicator();
    if(left_auto_count == 0 && left_vent_is_pressed == 0)
      {
        buttonLeftAutoPressed = false;
        buttonLeftProppeler = true;
        Hide_Left_Vent_If_Left_Auto_Pressed();
        Left_Proppeler_For_Turn_Vent();
        Left_Auto_Indicator();   
      }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && vent_l < 10)
       {
        buttonLeftAutoPressed = true;
        buttonLeftProppeler = false;
        Left_Vent();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
       }else
       if(left_auto_count == 0 && left_vent_is_pressed == 1 && vent_l > 9)
       {
        buttonLeftAutoPressed = true;
        buttonLeftProppeler = false;
        Left_Vent_Two_Digits();
        Left_Arrows_Up_And_Down();
        Propeller_Left();
        No_Left_Proppeler_For_Turn_Vent();
        No_Left_Auto_Indicator();
       }
        if(left_auto_count == 1 && left_vent_is_pressed == 1)
        {
          buttonLeftAutoPressed = false;
          buttonLeftProppeler = true;
          Hide_Left_Vent_If_Left_Auto_Pressed();
          Left_Proppeler_For_Turn_Vent();
          Left_Auto_Indicator();
          left_vent_is_pressed = 0;
          left_auto_count = 0;
        }       
   } 
 }
 //RIGHT PROPELLER SYMBOL FOR TURNING THE VENTILATION SETTINGS
 if(right_proppeler.z >  ts.pressureThreshhold && buttonRightProppeler == true)
 {
  right_proppeler.x = map(right_proppeler.x, TS_MINX, TS_MAXX ,tft.height(),0);
  right_proppeler.y = map(right_proppeler.y, TS_MAXY, TS_MINY, 0,tft.width());
  int t = right_proppeler.x;
  right_proppeler.x = right_proppeler.y;
  right_proppeler.y = t;
  //Z = p.z;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if(right_proppeler.x > 267 && right_proppeler.x < 317)
  {
    if(right_proppeler.y >= 140 && right_proppeler.y <= 190)
    {
      delay(200);
      right_vent_is_pressed = 1;
      right_auto_count = 0;
      buttonRightVent = true;
      buttonRightAutoPressed = true;
      Right_Arrows_Up_And_Down();
      Propeller_Right();
      No_Right_Proppeler_For_Turn_Vent();
      No_Right_Auto_Indicator();
      if(right_auto_count == 0 && right_vent_is_pressed == 0)
      {
        buttonRightAutoPressed = false;
        buttonRightProppeler = true;
        Hide_Right_Vent_If_Right_Auto_Pressed();
        Right_Proppeler_For_Turn_Vent();
        Right_Auto_Indicator();   
      }else
       if(right_auto_count == 0 && right_vent_is_pressed == 1 && vent_r < 10)
       {
        buttonRightAutoPressed = true;
        buttonRightProppeler = false;
        Right_Vent();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
       if(right_auto_count == 0 && right_vent_is_pressed == 1 && vent_r > 9)
       {
        buttonRightAutoPressed = true;
        buttonRightProppeler = false;
        Right_Vent_Two_Digits();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
        if(right_auto_count == 1 && right_vent_is_pressed == 1)
        {
          buttonRightAutoPressed = false;
          buttonRightProppeler = true;
          Hide_Right_Vent_If_Right_Auto_Pressed();
          Right_Proppeler_For_Turn_Vent();
          Right_Auto_Indicator();
          right_vent_is_pressed = 0;
          right_auto_count = 0;
        }
    }
  }else
   if(right_proppeler.x > 267 && right_proppeler.x < 317 && right_proppeler.y >= 140 && right_proppeler.y <= 190)
   {
    delay(200);
    right_vent_is_pressed = 1;
    right_auto_count = 0;
    buttonRightVent = true;
    buttonRightAutoPressed = true;
    Right_Arrows_Up_And_Down();
    Propeller_Right();
    No_Right_Proppeler_For_Turn_Vent();
    No_Right_Auto_Indicator();
    if(right_auto_count == 0 && right_vent_is_pressed == 0)
      {
        buttonRightAutoPressed = false;
        buttonRightProppeler = true;
        Hide_Right_Vent_If_Right_Auto_Pressed();
        Right_Proppeler_For_Turn_Vent();
        Right_Auto_Indicator();   
      }else
       if(right_auto_count == 0 && right_vent_is_pressed == 1 && vent_r < 10)
       {
        buttonRightAutoPressed = true;
        buttonRightProppeler = false;
        Right_Vent();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
       if(right_auto_count == 0 && right_vent_is_pressed == 1 && vent_r > 9)
       {
        buttonRightAutoPressed = true;
        buttonRightProppeler = false;
        Right_Vent_Two_Digits();
        Right_Arrows_Up_And_Down();
        Propeller_Right();
        No_Right_Proppeler_For_Turn_Vent();
        No_Right_Auto_Indicator();
       }else
        if(right_auto_count == 1 && right_vent_is_pressed == 1)
        {
          buttonRightAutoPressed = false;
          buttonRightProppeler = true;
          Hide_Right_Vent_If_Right_Auto_Pressed();
          Right_Proppeler_For_Turn_Vent();
          Right_Auto_Indicator();
          right_vent_is_pressed = 0;
          right_auto_count = 0;
        }
   } 
 }
 //LEFT TEMP
 if(left_temp.z > ts.pressureThreshhold && buttonLeftTemp == true)
 {
  left_temp.x = map(left_temp.x, TS_MINX, TS_MAXX ,tft.height(),0);
  left_temp.y = map(left_temp.y, TS_MAXY, TS_MINY, 0,tft.width());
  int t = left_temp.x;
  left_temp.x = left_temp.y;
  left_temp.y = t;
  //Z = p.z;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //FOR INCREASING LEFT TEMP
  if(left_temp.x > 4 && left_temp.x < 37)
  {
    if(left_temp.y >= 90 && left_temp.y <= 116)
    {
      delay(300);
      count_sync = 0;
      No_SYNC_Red_Indicator();
      temp_l += 0.5;
      if(temp_l > 30.0)
      {
        temp_l = 30.0;
      }
      isEven_l = temp_l * 10;
      Left_Temp();
    }
  }else
   if(left_temp.x > 4 && left_temp.x < 37 && left_temp.y >= 90 && left_temp.y <= 116)
   {
     delay(300);
     count_sync = 0;
     No_SYNC_Red_Indicator();
     temp_l += 0.5;
     if(temp_l > 30.0)
     {
       temp_l = 30.0;
     }
     isEven_l = temp_l * 10;
     Left_Temp();
   }
   //FOR DECREASING LEFT TEMP
   if(left_temp.x > 4 && left_temp.x < 37)
   {
    if(left_temp.y >= 200 && left_temp.y <= 230)
    {
      delay(300);
      count_sync = 0;
      No_SYNC_Red_Indicator();
      temp_l -= 0.5;
      if(temp_l < 16.0)
      {
        temp_l = 16.0;
      }
      isEven_l = temp_l * 10;
      Left_Temp();
    }
   }else
    if(left_temp.x > 4 && left_temp.x < 37 && left_temp.y >= 200 && left_temp.y <= 230)
    {
      delay(300);
      count_sync = 0;
      No_SYNC_Red_Indicator();
      temp_l -= 0.5;
      if(temp_l < 16.0)
      {
        temp_l = 16.0;
      }
      isEven_l = temp_l * 10;
      Left_Temp();
    }
    //LEFT VENT
   if(left_vent.z > ts.pressureThreshhold && buttonLeftVent == true)
   {
    left_vent.x = map(left_vent.x, TS_MINX, TS_MAXX ,tft.height(),0);
    left_vent.y = map(left_vent.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = left_vent.x;
    left_vent.x = left_vent.y;
    left_vent.y = t;
    //Z = p.z;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    //FOR INCREASING LEFT VENT
    if(left_vent.x > 170 && left_vent.x < 210)
    {
      if(left_vent.y >=85 && left_vent.y <= 102)
      {
        delay(300);
        count_sync = 0;
        No_SYNC_Red_Indicator();
        vent_l += 1;
        if(vent_l > 12)
        {
          vent_l = 12;
        }  
        if(vent_l > 9)
        {
          Left_Vent_Two_Digits();
        }else
        {
          Left_Vent();
        }       
      }
    }else
     if(left_vent.x > 170 && left_vent.x < 210 && left_vent.y >=85 && left_vent.y <= 102)
     {
        delay(300);
        count_sync = 0;
        No_SYNC_Red_Indicator();
        vent_l += 1;
        if(vent_l > 12)
        {
          vent_l = 12;
        }
        if(vent_l > 9)
        {
          Left_Vent_Two_Digits();
        }else
        {
          Left_Vent();
        }
     }
     //FOR DECREASING LEFT VENT
     if(left_vent.x > 164 && left_vent.x < 208)
     {
      if(left_vent.y >= 214 && left_vent.y <= 234)
      {
        delay(300);
        count_sync = 0;
        No_SYNC_Red_Indicator();
        vent_l -= 1;
        if(vent_l < 1)
        {
          vent_l = 1;
        }
        if(vent_l > 9)
        {
          Left_Vent_Two_Digits();
        }else
        {
          Left_Vent();
        }
      }
     }else
      if(left_vent.x > 164 && left_vent.x < 208 && left_vent.y >= 214 && left_vent.y <= 234)
      {
        delay(300);
        count_sync = 0;
        No_SYNC_Red_Indicator();
        vent_l -= 1;
        if(vent_l < 1)
        {
          vent_l = 1;
        }
        if(vent_l > 9)
        {
          Left_Vent_Two_Digits();
        }else
        {
          Left_Vent();
        }
      }
   }
 }
 //RIGHT TEMP
 if(right_temp.z > ts.pressureThreshhold && buttonRightTemp == true)
 {
  right_temp.x = map(right_temp.x, TS_MINX, TS_MAXX ,tft.height(),0);
  right_temp.y = map(right_temp.y, TS_MAXY, TS_MINY, 0,tft.width());
  int t = right_temp.x;
  right_temp.x = right_temp.y;
  right_temp.y = t;
  //Z = p.z;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //FOR INCREASING RIGHT TEMP
  if(right_temp.x > 442 && right_temp.x < 475)
  {
    if(right_temp.y >= 89 && right_temp.y <= 117)
    {
      delay(300);
      count_sync = 0;
      No_SYNC_Red_Indicator();
      temp_r += 0.5;
      if(temp_r > 30.0)
      {
        temp_r = 30.0;
      }
      isEven_r = temp_r * 10;
      Right_Temp();
    }else
    if(right_temp.x > 442 && right_temp.x < 475 && right_temp.y >= 89 && right_temp.y <= 117)
    {
      delay(300);
      count_sync = 0;
      No_SYNC_Red_Indicator();
      temp_r += 0.5;
      if(temp_r > 30.0)
      {
        temp_r = 30.0;
      }
      isEven_r = temp_r * 10;
      Right_Temp();
    }
    //FOR DECREASING RIGHT TEMP
    if(right_temp.x > 442 && right_temp.x < 475)
    {
      if(right_temp.y >= 195 && right_temp.y <= 230)
      {
        delay(300);
        count_sync = 0;
        No_SYNC_Red_Indicator();
        temp_r -= 0.5;
        if(temp_r < 16.0)
        {
          temp_r = 16.0;
        }
        isEven_r = temp_r * 10;
        Right_Temp();
      }
    }else
      if(right_temp.x > 442 && right_temp.x < 475 && right_temp.y >= 195 && right_temp.y <= 230)
      {
        delay(300);
        count_sync = 0;
        No_SYNC_Red_Indicator();
        temp_r -= 0.5;
        if(temp_r < 16.0)
        {
          temp_r = 16.0;
        }
        isEven_r = temp_r * 10;
        Right_Temp();
      } 
    }
    //RIGHT VENT
   if(right_vent.z > ts.pressureThreshhold && buttonRightVent == true)
   {
    right_vent.x = map(right_vent.x, TS_MINX, TS_MAXX ,tft.height(),0);
    right_vent.y = map(right_vent.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = right_vent.x;
    right_vent.x = right_vent.y;
    right_vent.y = t;
    //Z = p.z;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    //FOR INCREASING RIGHT VENT
    if(right_vent.x > 274 && right_vent.x < 318)
    {
      if(right_vent.y >=84 && right_vent.y <= 102)
      {
        delay(300);
        count_sync = 0;
        No_SYNC_Red_Indicator();
        vent_r += 1;
        if(vent_r > 12)
        {
          vent_r = 12;
        }  
        if(vent_r > 9)
        {
          Right_Vent_Two_Digits();
        }else
        {
          Right_Vent();
        }
      }
    }else
     if(right_vent.x > 274 && right_vent.x < 318 && right_vent.y >=84 && right_vent.y <= 102)
     {
        delay(300);
        count_sync = 0;
        No_SYNC_Red_Indicator();
        vent_r += 1;
        if(vent_r > 12)
        {
          vent_r = 12;
        }  
        if(vent_r > 9)
        {
          Right_Vent_Two_Digits();
        }else
        {
          Right_Vent();
        }
     }
     //FOR DECREASING RIGHT VENT
     if(right_vent.x > 275 && right_vent.x < 320)
     {
      if(right_vent.y >= 213 && right_vent.y <= 235)
      {
        delay(300);
        count_sync = 0;
        No_SYNC_Red_Indicator();
        vent_r -= 1;
        if(vent_r < 1)
        {
          vent_r = 1;
        }  
        if(vent_r > 9)
        {
          Right_Vent_Two_Digits();
        }else
        {
          Right_Vent();
        }
      }
     }else
      if(right_vent.x > 275 && right_vent.x < 320 && right_vent.y >= 213 && right_vent.y <= 235)
      {
        delay(300);
        count_sync = 0;
        No_SYNC_Red_Indicator();
        vent_r -= 1;
        if(vent_r < 1)
        {
          vent_r = 1;
        }  
        if(vent_r > 9)
        {
          Right_Vent_Two_Digits();
        }else
        {
          Right_Vent();
        }
      }
    }
  }
  // EXIT FROM CLIMATE SCREEN ( NOT TURN OFF THE CLIMATE)
  if(but_ret_home.z > ts.pressureThreshhold && buttonReturnHomeScreen == true)
   {
    but_ret_home.x = map(but_ret_home.x, TS_MINX, TS_MAXX ,tft.height(),0);
    but_ret_home.y = map(but_ret_home.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = but_ret_home.x;
    but_ret_home.x = but_ret_home.y;
    but_ret_home.y = t;
    //Z = p.z;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if(but_ret_home.x > 190 && but_ret_home.x < 282)
    {
     if(but_ret_home.y >= 295 && but_ret_home.y <= 319)
     {
      delay(100);
      buttonPanelEnabled = true;
      buttonLeftTemp = false;
      buttonRightTemp = false;
      buttonLeftProppeler = false;
      buttonRightProppeler = false;
      buttonLeftVent = false;
      buttonRightVent = false;
      buttonLeftVentOnOrOff = false;
      buttonRightVentOnOrOff = false;
      buttonLeftHeatingOnOrOff = false;
      buttonRightHeatingOnOrOff = false;
      buttonOffWholeClimateSys = false;
      buttonReturnHomeScreen = false;
      buttonClimaIsOnOrOff = false;
      buttonTurnOnClimatePanel = false;
      buttonSync = false;
      buttonCarFiltering = false;
      Home_Screen();
     }
    }else
    if(but_ret_home.x > 190 && but_ret_home.x < 282 && but_ret_home.y >= 295 && but_ret_home.y <= 319)
    {
      delay(100);
      buttonPanelEnabled = true;
      buttonLeftTemp = false;
      buttonRightTemp = false;
      buttonLeftProppeler = false;
      buttonRightProppeler = false;
      buttonLeftVent = false;
      buttonRightVent = false;
      buttonLeftVentOnOrOff = false;
      buttonRightVentOnOrOff = false;
      buttonLeftHeatingOnOrOff = false;
      buttonRightHeatingOnOrOff = false;
      buttonOffWholeClimateSys = false;
      buttonReturnHomeScreen = false;
      buttonClimaIsOnOrOff = false;
      buttonTurnOnClimatePanel = false;
      buttonSync = false;
      buttonCarFiltering = false;
      Home_Screen();
    }
   }
   //TURN ON OR OFF THE CLIMATE
  if(ac_on_off.z > ts.pressureThreshhold && buttonClimaIsOnOrOff == true)
   {
    ac_on_off.x = map(ac_on_off.x, TS_MINX, TS_MAXX ,tft.height(),0);
    ac_on_off.y = map(ac_on_off.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = ac_on_off.x;
    ac_on_off.x = ac_on_off.y;
    ac_on_off.y = t;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if(ac_on_off.x > 77 && ac_on_off.x < 134)
    {
      if(ac_on_off.y >= 295 && ac_on_off.y <= 319)
      {
        delay(300);
        count_climate++;
        buttonOffWholeClimateSys = true;
        buttonCarFiltering = true;
        if(count_climate % 2 !=0)
        {
          Climatronic_Lights_On();
          Climate_Indicator_On();
        }else
        {
          Climatronic_Lights_Off();
          Climate_Indicator_Off();
          No_SYNC_Red_Indicator();
          No_Car_Filter_Indicator();
        }
      }else
       if(ac_on_off.x > 77 && ac_on_off.x < 134 && ac_on_off.y >= 295 && ac_on_off.y <= 319)
       {
         delay(300);
         count_climate++;
         buttonOffWholeClimateSys = true;
         buttonCarFiltering = true;;
         if(count_climate % 2 !=0)
         {
          Climatronic_Lights_On();
          Climate_Indicator_On();
         }else
         {
          Climatronic_Lights_Off();
          Climate_Indicator_Off();
          No_SYNC_Red_Indicator();
          No_Car_Filter_Indicator();
         }
       }
     }
   }
   //TURN ON OR OFF THE VENTILATION OF THE LEFT SEAT
   if(left_vent_on_off.z > ts.pressureThreshhold && buttonLeftVentOnOrOff == true)
   {
    left_vent_on_off.x = map(left_vent_on_off.x, TS_MINX, TS_MAXX ,tft.height(),0);
    left_vent_on_off.y = map(left_vent_on_off.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = left_vent_on_off.x;
    left_vent_on_off.x = left_vent_on_off.y;
    left_vent_on_off.y = t;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if(left_vent_on_off.x > 20 && left_vent_on_off.x < 77)
    {
      if(left_vent_on_off.y >= 295 && left_vent_on_off.y <= 319)
      {
        delay(100);
        level_vent_left++;
        if(level_vent_left == 1 && level_vent_left % 1 == 0)
        {
         Left_Seat();
         Max_Cooling_Indicator_Left_Seat();
        }else
         if(level_vent_left == 2 && level_vent_left % 2 == 0)
         {
           Left_Seat();
           Mid_Cooling_Indicator_Left_Seat();
         }else
         if(level_vent_left == 3 && level_vent_left % 3 == 0)
         {
          Left_Seat();
          Min_Cooling_Indicator_Left_Seat();
         }else
          if(level_vent_left == 4 && level_vent_left % 4 == 0)
          {
            level_vent_left = 0;
            No_Cooling_Indicator_Left_Seat();
          }
      }
    }else
      if(left_vent_on_off.x > 20 && left_vent_on_off.x < 77 && left_vent_on_off.y >= 295 && left_vent_on_off.y <= 319)
      {
        delay(100);       
        level_vent_left++;
        if(level_vent_left == 1 && level_vent_left % 1 == 0)
        {
         Left_Seat();
         Max_Cooling_Indicator_Left_Seat();
        }else
         if(level_vent_left == 2 && level_vent_left % 2 == 0)
         {
           Left_Seat();
           Mid_Cooling_Indicator_Left_Seat();
         }else
         if(level_vent_left == 3 && level_vent_left % 3 == 0)
         {
          Left_Seat();
          Min_Cooling_Indicator_Left_Seat();
         }else
          if(level_vent_left == 4 && level_vent_left % 4 == 0)
          {
            level_vent_left = 0;
            No_Cooling_Indicator_Left_Seat();
          }
      }
   }
   //TURN ON OR OFF THE HEATING OF THE LEFT SEAT
  if(left_heating.z > ts.pressureThreshhold && buttonLeftHeatingOnOrOff == true)
  {
    left_heating.x = map(left_heating.x, TS_MINX, TS_MAXX ,tft.height(),0);
    left_heating.y = map(left_heating.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = left_heating.x;
    left_heating.x = left_heating.y;
    left_heating.y = t;
    //Z = p.z;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if(left_heating.x < 20)
    {
      if(left_heating.y >= 295 && left_heating.y <= 319)
      {
        delay(300);
        level_heat_left++;
        if(level_heat_left == 1 && level_heat_left % 1 == 0)
        {
         Left_Seat();
         Max_Heat_Indicator_Left_Seat();
        }else
         if(level_heat_left == 2 && level_heat_left % 2 == 0)
         {
           Left_Seat();
           Mid_Heat_Indicator_Left_Seat();
         }else
         if(level_heat_left == 3 && level_heat_left % 3 == 0)
         {
          Left_Seat();
          Min_Heat_Indicator_Left_Seat();
         }else
          if(level_heat_left == 4 && level_heat_left % 4 == 0)
          {
            level_heat_left = 0;
            No_Heat_Indicator_Left_Seat();
          }
      }
    }else
     if(left_heating.x < 20 && left_heating.y >= 295 && left_heating.y <= 319)
     {
       delay(300);
       level_heat_left++;
       if(level_heat_left == 1 && level_heat_left % 1 == 0)
       {
        Left_Seat();
        Max_Heat_Indicator_Left_Seat();
       }else
        if(level_heat_left == 2 && level_heat_left % 2 == 0)
        {
          Left_Seat();
          Mid_Heat_Indicator_Left_Seat();
        }else
         if(level_heat_left == 3 && level_heat_left % 3 == 0)
         {
          Left_Seat();
          Min_Heat_Indicator_Left_Seat();
         }else
          if(level_heat_left == 4 && level_heat_left % 4 == 0)
          {
            level_heat_left = 0;
            No_Heat_Indicator_Left_Seat();
          }
     }
  }
  // BUTTON FOR TURN OFF THE WHOLE CLIMATE SYSTEM WITHOUT ALL FEATURES-LIKE VENTING HEATING
  if(button_off_cli_sys.z > ts.pressureThreshhold && buttonOffWholeClimateSys == true)
  {
   button_off_cli_sys.x = map(button_off_cli_sys.x, TS_MINX, TS_MAXX ,tft.height(),0);
   button_off_cli_sys.y = map(button_off_cli_sys.y, TS_MAXY, TS_MINY, 0,tft.width());
   int t = button_off_cli_sys.x;
   button_off_cli_sys.x = button_off_cli_sys.y;
   button_off_cli_sys.y = t;
   //Z = p.z;
   pinMode(XM, OUTPUT);
   pinMode(YP, OUTPUT);
   if(button_off_cli_sys.x > 282 && button_off_cli_sys.x < 339)
   {
    if(button_off_cli_sys.y >= 295 && button_off_cli_sys.y <= 319)
    {
      delay(200);
      buttonTurnOnClimatePanel = true;
      buttonOffWholeClimateSys = false;
      buttonLeftTemp = false;
      buttonRightTemp = false;
      buttonLeftProppeler = false;
      buttonRightProppeler = false;
      buttonLeftVent = false;
      buttonRightVent = false;
      buttonClimaIsOnOrOff = false;
      buttonSync = false;
      buttonCarFiltering = false;
      buttonLeftAutoPressed = false;
      buttonRightAutoPressed = false;
      left_auto_count = 0;
      right_auto_count = 0;
      left_vent_is_pressed = 0;
      right_vent_is_pressed = 0;
      count_climate = 0;
      Climate_Indicator_Off();
      No_SYNC_Red_Indicator();
      No_Car_Filter_Indicator();
      Off_Red_Indicator();
      Screen_For_Turning_On_AC();
      Climatronic_Lights_Off();
    }
   }else
    if(button_off_cli_sys.x > 282 && button_off_cli_sys.x < 339 && button_off_cli_sys.y >= 295 && button_off_cli_sys.y <= 319)
    {
      delay(200);
      buttonTurnOnClimatePanel = true;
      buttonOffWholeClimateSys = false;
      buttonLeftTemp = false;
      buttonRightTemp = false;
      buttonLeftProppeler = false;
      buttonRightProppeler = false;
      buttonLeftVent = false;
      buttonRightVent = false;
      buttonClimaIsOnOrOff = false;
      buttonSync = false;
      buttonCarFiltering = false;
      buttonLeftAutoPressed = false;
      buttonRightAutoPressed = false;
      left_auto_count = 0;
      right_auto_count = 0;
      left_vent_is_pressed = 0;
      right_vent_is_pressed = 0;
      count_climate = 0;
      Climate_Indicator_Off();
      No_SYNC_Red_Indicator();
      No_Car_Filter_Indicator();
      Off_Red_Indicator();
      Screen_For_Turning_On_AC();
      Climatronic_Lights_Off();
    }
  }
  //TURN ON OR OFF VENTING RIGHT SEAT
  if(right_vent_on_off.z > ts.pressureThreshhold && buttonRightVentOnOrOff == true)
   {
    right_vent_on_off.x = map(right_vent_on_off.x, TS_MINX, TS_MAXX ,tft.height(),0);
    right_vent_on_off.y = map(right_vent_on_off.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = right_vent_on_off.x;
    right_vent_on_off.x = right_vent_on_off.y;
    right_vent_on_off.y = t;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if(right_vent_on_off.x > 395 && right_vent_on_off.x < 453)
    {
      if(left_vent_on_off.y >= 295 && left_vent_on_off.y <= 319)
      {
        delay(100);       
        level_vent_right++;
        if(level_vent_right == 1 && level_vent_right % 1 == 0)
        {
         Right_Seat();
         Max_Cooling_Indicator_Right_Seat();
        }else
         if(level_vent_right == 2 && level_vent_right % 2 == 0)
         {
           Right_Seat();
           Mid_Cooling_Indicator_Right_Seat();
         }else
         if(level_vent_right == 3 && level_vent_right % 3 == 0)
         {
          Right_Seat();
          Min_Cooling_Indicator_Right_Seat();
         }else
          if(level_vent_right == 4 && level_vent_right % 4 == 0)
          {
            level_vent_right = 0;
            No_Cooling_Indicator_Right_Seat();
          }
      }
    }else
      if(right_vent_on_off.x > 395 && right_vent_on_off.x < 453 && right_vent_on_off.y >= 295 && right_vent_on_off.y <= 319)
      {
        delay(100);       
        level_vent_right++;
        if(level_vent_right == 1 && level_vent_right % 1 == 0)
        {
         Right_Seat();
         Max_Cooling_Indicator_Right_Seat();
        }else
         if(level_vent_right == 2 && level_vent_right % 2 == 0)
         {
           Right_Seat();
           Mid_Cooling_Indicator_Right_Seat();
         }else
         if(level_vent_right == 3 && level_vent_right % 3 == 0)
         {
          Right_Seat();
          Min_Cooling_Indicator_Right_Seat();
         }else
          if(level_vent_right == 4 && level_vent_right % 4 == 0)
          {
            level_vent_right = 0;
            No_Cooling_Indicator_Right_Seat();
          }
      }
   }
   //TURN ON OR OFF RIGHT SEAT HEATING 
   if(right_heating.z > ts.pressureThreshhold && buttonRightHeatingOnOrOff == true)
  {
    right_heating.x = map(right_heating.x, TS_MINX, TS_MAXX ,tft.height(),0);
    right_heating.y = map(right_heating.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = right_heating.x;
    right_heating.x = right_heating.y;
    right_heating.y = t;
    //Z = p.z;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if(right_heating.x > 453)
    {
      if(right_heating.y >= 295 && right_heating.y <= 319)
      {
        delay(300);
        level_heat_right++;
        if(level_heat_right == 1 && level_heat_right % 1 == 0)
        {
         Right_Seat();
         Max_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 2 && level_heat_right % 2 == 0)
         {
           Right_Seat();
           Mid_Heat_Indicator_Right_Seat();
         }else
         if(level_heat_right == 3 && level_heat_right % 3 == 0)
         {
          Right_Seat();
          Min_Heat_Indicator_Right_Seat();
         }else
          if(level_heat_right == 4 && level_heat_right % 4 == 0)
          {
            level_heat_right= 0;
            No_Heat_Indicator_Right_Seat();
          }
      }
    }else
     if(right_heating.x > 453 && right_heating.y >= 295 && right_heating.y <= 319)
     {
      delay(300);
      level_heat_right++;
      if(level_heat_right == 1 && level_heat_right % 1 == 0)
      {
       Right_Seat();
       Max_Heat_Indicator_Right_Seat();
      }else
       if(level_heat_right == 2 && level_heat_right % 2 == 0)
       {
        Right_Seat();
        Mid_Heat_Indicator_Right_Seat();
       }else
        if(level_heat_right == 3 && level_heat_right % 3 == 0)
        {
         Right_Seat();
         Min_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 4 && level_heat_right % 4 == 0)
         {
          level_heat_right= 0;
          No_Heat_Indicator_Right_Seat();
         }
      }
   }
   //TURN ON A/C FROM SCREEN PANEL
   if(climate_panel.z > ts.pressureThreshhold && buttonTurnOnClimatePanel == true)
  {
    climate_panel.x = map(climate_panel.x, TS_MINX, TS_MAXX ,tft.height(),0);
    climate_panel.y = map(climate_panel.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = climate_panel.x;
    climate_panel.x = climate_panel.y;
    climate_panel.y = t;
    //Z = p.z;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if(climate_panel.x > 215 && climate_panel.x < 265)
    {
      if(climate_panel.y >= 120 && climate_panel.y <= 160)
      {
        delay(200);
        buttonOffWholeClimateSys = true;
        buttonLeftTemp = true;
        buttonRightTemp = true;
        buttonLeftProppeler = true;
        buttonRightProppeler = true;
        buttonLeftVent = false;
        buttonRightVent = false;
        buttonClimaIsOnOrOff = true;
        buttonSync = true;
        buttonCarFiltering = true;
        count_climate = 1;
        Climate_Bar();
        No_Off_Red_Indicator();
        Climate_Indicator_On();
        Climatronic_Lights_On();
        
       //SAVING THE INDICATOR OF VENTILATION OF LEFT SEAT IF OFF BUTTON IS PRESSED
       if(level_vent_left == 1 && level_vent_left % 1 == 0)
       {
        Left_Seat();
        Max_Cooling_Indicator_Left_Seat();
       }else
        if(level_vent_left == 2 && level_vent_left % 2 == 0)
        {
         Left_Seat();
         Mid_Cooling_Indicator_Left_Seat();
        }else
         if(level_vent_left == 3 && level_vent_left % 3 == 0)
         {
          Left_Seat();
          Min_Cooling_Indicator_Left_Seat();
         }else
          if(level_vent_left == 4 && level_vent_left % 4 == 0)
          {
           level_vent_left = 0;
           No_Cooling_Indicator_Left_Seat();
          }

       //SAVING THE INDICATOR OF VENTILATION OF RIGHT SEAT IF OFF BUTTON IS PRESSED   
       if(level_vent_right == 1 && level_vent_right % 1 == 0)
       {
        Right_Seat();
        Max_Cooling_Indicator_Right_Seat();
       }else
        if(level_vent_right == 2 && level_vent_right % 2 == 0)
        {
         Right_Seat();
         Mid_Cooling_Indicator_Right_Seat();
        }else
         if(level_vent_right == 3 && level_vent_right % 3 == 0)
         {
          Right_Seat();
          Min_Cooling_Indicator_Right_Seat();
         }else
          if(level_vent_right == 4 && level_vent_right % 4 == 0)
          {
           level_vent_right = 0;
           No_Cooling_Indicator_Right_Seat();
          }

       //SAVING THE INDICATOR OF HEATING OF LEFT SEAT IF OFF BUTTON IS PRESSED 
       if(level_heat_left == 1 && level_heat_left % 1 == 0)
       {
        Left_Seat();
        Max_Heat_Indicator_Left_Seat();
       }else
        if(level_heat_left == 2 && level_heat_left % 2 == 0)
        {
          Left_Seat();
          Mid_Heat_Indicator_Left_Seat();
        }else
         if(level_heat_left == 3 && level_heat_left % 3 == 0)
         {
          Left_Seat();
          Min_Heat_Indicator_Left_Seat();
         }else
          if(level_heat_left == 4 && level_heat_left % 4 == 0)
          {
            level_heat_left = 0;
            No_Heat_Indicator_Left_Seat();
          }

        //SAVING THE INDICATOR OF HEATING OF RIGHT SEAT IF OFF BUTTON IS PRESSED    
        if(level_heat_right == 1 && level_heat_right % 1 == 0)
        {
         Right_Seat();
         Max_Heat_Indicator_Right_Seat();
        }else
         if(level_heat_right == 2 && level_heat_right % 2 == 0)
         {
           Right_Seat();
           Mid_Heat_Indicator_Right_Seat();
         }else
         if(level_heat_right == 3 && level_heat_right % 3 == 0)
         {
          Right_Seat();
          Min_Heat_Indicator_Right_Seat();
         }else
          if(level_heat_right == 4 && level_heat_right % 4 == 0)
          {
            level_heat_right= 0;
            No_Heat_Indicator_Right_Seat();
          }
      }
    }else
     if(climate_panel.x > 215 && climate_panel.x < 265 && climate_panel.y >= 120 && climate_panel.y <= 160)
     {
      delay(200);
      buttonOffWholeClimateSys = true;
      buttonLeftTemp = true;
      buttonRightTemp = true;
      buttonLeftProppeler = true;
      buttonRightProppeler = true;
      buttonLeftVent = false;
      buttonRightVent = false;
      buttonClimaIsOnOrOff = true;
      buttonSync = true;
      buttonCarFiltering = true;
      count_climate = 1;
      Climate_Bar();
      No_Off_Red_Indicator();
      Climate_Indicator_On();
      Climatronic_Lights_On();
      
      //SAVING THE INDICATOR OF VENTILATION OF LEFT SEAT IF OFF BUTTON IS PRESSED
       if(level_vent_left == 1 && level_vent_left % 1 == 0)
       {
        Left_Seat();
        Max_Cooling_Indicator_Left_Seat();
       }else
        if(level_vent_left == 2 && level_vent_left % 2 == 0)
        {
         Left_Seat();
         Mid_Cooling_Indicator_Left_Seat();
        }else
         if(level_vent_left == 3 && level_vent_left % 3 == 0)
         {
          Left_Seat();
          Min_Cooling_Indicator_Left_Seat();
         }else
          if(level_vent_left == 4 && level_vent_left % 4 == 0)
          {
           level_vent_left = 0;
           No_Cooling_Indicator_Left_Seat();
          }

       //SAVING THE INDICATOR OF VENTILATION OF RIGHT SEAT IF OFF BUTTON IS PRESSED   
       if(level_vent_right == 1 && level_vent_right % 1 == 0)
       {
        Right_Seat();
        Max_Cooling_Indicator_Right_Seat();
       }else
        if(level_vent_right == 2 && level_vent_right % 2 == 0)
        {
         Right_Seat();
         Mid_Cooling_Indicator_Right_Seat();
        }else
         if(level_vent_right == 3 && level_vent_right % 3 == 0)
         {
          Right_Seat();
          Min_Cooling_Indicator_Right_Seat();
         }else
          if(level_vent_right == 4 && level_vent_right % 4 == 0)
          {
           level_vent_right = 0;
           No_Cooling_Indicator_Right_Seat();
          }

       //SAVING THE INDICATOR OF HEATING OF LEFT SEAT IF OFF BUTTON IS PRESSED 
       if(level_heat_left == 1 && level_heat_left % 1 == 0)
       {
        Left_Seat();
        Max_Heat_Indicator_Left_Seat();
       }else
        if(level_heat_left == 2 && level_heat_left % 2 == 0)
        {
          Left_Seat();
          Mid_Heat_Indicator_Left_Seat();
        }else
         if(level_heat_left == 3 && level_heat_left % 3 == 0)
         {
          Left_Seat();
          Min_Heat_Indicator_Left_Seat();
         }else
          if(level_heat_left == 4 && level_heat_left % 4 == 0)
          {
            level_heat_left = 0;
            No_Heat_Indicator_Left_Seat();
          }

        //SAVING THE INDICATOR OF HEATING OF RIGHT SEAT IF OFF BUTTON IS PRESSED    
        if(level_heat_right == 1 && level_heat_right % 1 == 0)
        {
         Right_Seat();
         Max_Heat_Indicator_Right_Seat();
        }else
        if(level_heat_right == 2 && level_heat_right % 2 == 0)
        {
          Right_Seat();
          Mid_Heat_Indicator_Right_Seat();
        }else
        if(level_heat_right == 3 && level_heat_right % 3 == 0)
        {
         Right_Seat();
         Min_Heat_Indicator_Right_Seat();
        }else
        if(level_heat_right == 4 && level_heat_right % 4 == 0)
        {
          level_heat_right= 0;
          No_Heat_Indicator_Right_Seat();
        }
     }
  }
  //TURN ON SYNC BUTTON ( FOR TEMPERATURE. VENT ALSO WILL BE SYNCED BUT IF VENT IS NOT OPEN IT WONT BE SEEN) )
  if(button_sync.z > ts.pressureThreshhold && buttonSync == true)
   {
    button_sync.x = map(button_sync.x, TS_MINX, TS_MAXX ,tft.height(),0);
    button_sync.y = map(button_sync.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = button_sync.x;
    button_sync.x = button_sync.y;
    button_sync.y = t;
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if(button_sync.x > 134 && button_sync.x < 190)
    {
      if(button_sync.y >= 295 && button_sync.y <= 319)
      {
        delay(200);
        count_sync++;
        if(count_sync % 2 !=0)
        {
         SYNC_Red_Indicator();
         temp_r = temp_l;
         vent_r = vent_l;
         //if(
        }else
        {
         No_SYNC_Red_Indicator();
        }
        if(isEven_l % 2 == 0 || isEven_l % 2 != 0)
        {
         isEven_r = isEven_l;
         Right_Temp();
        }
       if(vent_r > 9 && buttonRightVent == true)
       {
        vent_r = vent_l;
        Right_Vent_Two_Digits();
       }else
       if(vent_r < 10 && buttonRightVent == true)
       {
        vent_r = vent_l;
        Right_Vent();
       }
      }
    }else
     if(button_sync.x > 134 && button_sync.x < 190 && button_sync.y >= 295 && button_sync.y <= 319)
     {
      delay(200);
      count_sync++;
      if(count_sync % 2 !=0)
      {
        SYNC_Red_Indicator();
        temp_r = temp_l;
        vent_r = vent_l;
      }else
      {
        No_SYNC_Red_Indicator();
      }
      if(isEven_l % 2 == 0 || isEven_l % 2 != 0)
      {
        isEven_r = isEven_l;
        Right_Temp();
      }
      if(vent_r > 9 && buttonRightVent == true)
       {
        vent_r = vent_l;
        Right_Vent_Two_Digits();
       }else
       if(vent_r < 10 && buttonRightVent == true)
       {
        vent_r = vent_l;
        Right_Vent();
       }
    }
  }
  //TURN ON OR OFF CAR FILTER BUTTON
  if(car_filter_button.z > ts.pressureThreshhold && buttonCarFiltering == true)
  {
   car_filter_button.x = map(car_filter_button.x, TS_MINX, TS_MAXX ,tft.height(),0);
   car_filter_button.y = map(car_filter_button.y, TS_MAXY, TS_MINY, 0,tft.width());
   int t = car_filter_button.x;
   car_filter_button.x = car_filter_button.y;
   car_filter_button.y = t;
   pinMode(XM, OUTPUT);
   pinMode(YP, OUTPUT);
   if(car_filter_button.x > 339 && car_filter_button.x < 395)
   {
     if(car_filter_button.y >= 295 && car_filter_button.y <= 319)
     {
      delay(200);
      count_filter++;
      if(count_filter % 2 !=0)
      {
        Car_Filter_Indicator();
      }else
      {
        No_Car_Filter_Indicator();
      }
     }
   }else
   if(car_filter_button.x > 339 && car_filter_button.x < 395 && car_filter_button.y >= 295 && car_filter_button.y <= 319)
   {
     delay(200);
     count_filter++;
     if(count_filter % 2 !=0)
     {
       Car_Filter_Indicator();
     }else
     {
       No_Car_Filter_Indicator();
     }
   }
 }
 //TURN ON LEFT AUTO BUTTON
 if(left_auto_button.z >  ts.pressureThreshhold && buttonLeftAutoPressed  == true)
 {
  left_auto_button.x = map(left_auto_button.x, TS_MINX, TS_MAXX ,tft.height(),0);
  left_auto_button.y = map(left_auto_button.y, TS_MAXY, TS_MINY, 0,tft.width());
  int t = left_auto_button.x;
  left_auto_button.x = left_auto_button.y;
  left_auto_button.y = t;
  //Z = p.z;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if(left_auto_button.x > 155 && left_auto_button.x < 209)
  {
    if(left_auto_button.y >= 270 && left_auto_button.y <= 290)
    {
      delay(200);
      left_auto_count = 1;
      left_vent_is_pressed = 0;
      buttonLeftAutoPressed = false;
      buttonLeftProppeler = true;
      buttonLeftVent = false;
      Hide_Left_Vent_If_Left_Auto_Pressed();
      Left_Proppeler_For_Turn_Vent();
      Left_Auto_Indicator();
    }
  }else
   if(left_auto_button.x > 155 && left_auto_button.x < 209 && left_auto_button.y >= 270 && left_auto_button.y <= 290)
   {
    delay(200);
    left_auto_count = 1;
    left_vent_is_pressed = 0;
    buttonLeftAutoPressed = false;
    buttonLeftProppeler = true;
    buttonLeftVent = false;
    Hide_Left_Vent_If_Left_Auto_Pressed();
    Left_Proppeler_For_Turn_Vent();
    Left_Auto_Indicator();
   }
 }
 //TURN ON RIGHT AUTO BUTTON
 if(right_auto_button.z >  ts.pressureThreshhold && buttonRightAutoPressed == true)
 {
  right_auto_button.x = map(right_auto_button.x, TS_MINX, TS_MAXX ,tft.height(),0);
  right_auto_button.y = map(right_auto_button.y, TS_MAXY, TS_MINY, 0,tft.width());
  int t = right_auto_button.x;
  right_auto_button.x = right_auto_button.y;
  right_auto_button.y = t;
  //Z = p.z;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if(right_auto_button.x > 264 && right_auto_button.x < 316)
  {
    if(right_auto_button.y >= 270 && right_auto_button.y <= 290)
    {
      delay(200);
      right_auto_count = 1;
      right_vent_is_pressed = 0;
      buttonRightAutoPressed = false;
      buttonRightProppeler = true;
      buttonRightVent = false;
      Hide_Right_Vent_If_Right_Auto_Pressed();
      Right_Proppeler_For_Turn_Vent();
      Right_Auto_Indicator();
    }
  }else
   if(right_auto_button.x > 264 && right_auto_button.x < 316 && right_auto_button.y >= 270 && right_auto_button.y <= 290)
   {
    delay(200);
    right_auto_count = 1;
    right_vent_is_pressed = 0;
    buttonRightAutoPressed = false;
    buttonRightProppeler = true;
    buttonRightVent = false;
    Hide_Right_Vent_If_Right_Auto_Pressed();
    Right_Proppeler_For_Turn_Vent();
    Right_Auto_Indicator();
   }
 }
}
