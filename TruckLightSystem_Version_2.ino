#include <Adafruit_NeoPixel.h>
#include <IRremote.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LONG_LIGHTS_PIN 41
#define BACK_LIGHTS_PIN 39
#define SHORT_LIGHTS_PIN 37
#define RIGHT_TURN_SIGNAL_PIN 35
#define LEFT_TURN_SIGNAL_PIN 33
#define TRAILER_SIDE_LIGHTS_PIN 31
#define NUM_PIXEL_LONG_LIGHTS 2
#define NUM_PIXEL_SHORT_LIGHTS 2
#define NUM_PIXEL_BACK_LIGHTS 4
#define NUM_PIXEL_LEFT_TURN_SIGNAL_LIGHTS 3
#define NUM_PIXEL_RIGHT_TURN_SIGNAL_LIGHTS 3
#define NUM_PIXEL_TRAILER_SIDE_LIGHTS 6

Adafruit_NeoPixel short_lights_of_truck = Adafruit_NeoPixel(NUM_PIXEL_SHORT_LIGHTS,SHORT_LIGHTS_PIN,NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel back_lights_of_truck = Adafruit_NeoPixel(NUM_PIXEL_BACK_LIGHTS,BACK_LIGHTS_PIN,NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel long_lights_of_truck = Adafruit_NeoPixel(NUM_PIXEL_LONG_LIGHTS,LONG_LIGHTS_PIN,NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel left_turn_signal_of_truck = Adafruit_NeoPixel(NUM_PIXEL_LEFT_TURN_SIGNAL_LIGHTS,LEFT_TURN_SIGNAL_PIN,NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel right_turn_signal_of_truck = Adafruit_NeoPixel(NUM_PIXEL_RIGHT_TURN_SIGNAL_LIGHTS,RIGHT_TURN_SIGNAL_PIN,NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel trailer_side_lights_of_truck = Adafruit_NeoPixel(NUM_PIXEL_TRAILER_SIDE_LIGHTS,TRAILER_SIDE_LIGHTS_PIN,NEO_GRBW + NEO_KHZ800);

const int RECV_PIN = 43;
IRrecv irrecv(RECV_PIN);
decode_results results;
int count_remote_control_short_lights = 0;
int count_remote_control_long_lights = 0;
int count_remote_control_hazard_lights = 0;
int count_remote_control_left_turn_signal = 0;
int count_remote_control_right_turn_signal = 0;
int counter_left;
int counter_right;
int previous_left;
int previous_right;
char buffer[100];
int str = 0;

const int Button_Long_Lights = 4;
int Counter_Turn_On_And_Off_Long_Lights = 0;        // counter for the number of button presses
int State_Of_Turn_On_And_Off_Long_Lights = 0;    // current state of the button
int Last_State_Of_Turn_On_And_Off_Long_Lights = 0;  // previous state of the button

const int Button_Main_Lights = 2;
int Counter_Turn_On_And_Off_Main_Lights = 0;        // counter for the number of button presses
int State_Of_Turn_On_And_Off_Main_Lights = 0;    // current state of the button
int Last_State_Of_Turn_On_And_Off_Main_Lights = 0;  // previous state of the button

const int Button_Right_Turn_Signal = 3;
int Counter_Turn_On_And_Off_Right_Turn_Signal = 0;        // counter for the number of button presses
int State_Of_Turn_On_And_Off_Right_Turn_Signal = 0;    // current state of the button
int Last_State_Of_Turn_On_And_Off_Right_Turn_Signal = 0;  // previous state of the button

const int Button_Left_Turn_Signal = 6;
int Counter_Turn_On_And_Off_Left_Turn_Signal = 0;        // counter for the number of button presses
int State_Of_Turn_On_And_Off_Left_Turn_Signal = 0;    // current state of the button
int Last_State_Of_Turn_On_And_Off_Left_Turn_Signal = 0;  // previous state of the button

const int Button_Hazard_Lights_Signal = 5;
int Counter_Turn_On_And_Off_Hazard_Lights_Signal = 0;        // counter for the number of button presses
int State_Of_Turn_On_And_Off_Hazard_Lights_Signal = 0;    // current state of the button
int Last_State_Of_Turn_On_And_Off_Hazard_Lights_Signal = 0;  // previous state of the button



byte neopix_gamma[] = 
{
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
 215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 
};
int bright_long_light = 255;
int bright_lights = 170;
int bright_turn_lights_and_hazards = 200;
void setup()
{
  #if defined (__AVR_ATtiny85__)
    if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  short_lights_of_truck.setBrightness(bright_lights);
  short_lights_of_truck.begin();
  short_lights_of_truck.show();
  back_lights_of_truck.setBrightness(bright_lights);
  back_lights_of_truck.begin();
  back_lights_of_truck.show();
  long_lights_of_truck.setBrightness(bright_long_light);
  long_lights_of_truck.begin();
  long_lights_of_truck.show();
  left_turn_signal_of_truck.setBrightness(bright_turn_lights_and_hazards);
  left_turn_signal_of_truck.begin();
  left_turn_signal_of_truck.show();
  right_turn_signal_of_truck.setBrightness(bright_turn_lights_and_hazards);
  right_turn_signal_of_truck.begin();
  right_turn_signal_of_truck.show();
  trailer_side_lights_of_truck.setBrightness(bright_lights);
  trailer_side_lights_of_truck.begin();
  trailer_side_lights_of_truck.show();
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void Long_Lights(uint32_t color)
{
 int i = 0;
 for(int j = 255; j >= 0; j--)
 {
  for(; i < long_lights_of_truck.numPixels(); i++)
  {
   long_lights_of_truck.setPixelColor(i,color);
  }
  long_lights_of_truck.show();
 }
}

void Main_Lights(uint32_t front,uint32_t rear,uint32_t trailer_side)
{
  int color_front = 0;
  int color_rear = 0;
  int color_side_trailer = 0;
  for(int j = 255; j >= 0; j--)
  {
   for(; color_front < short_lights_of_truck.numPixels(); color_front++)
   {
    short_lights_of_truck.setPixelColor(color_front,front);
   }
  }
  for(int j = 255; j >= 0; j--)
  {
   for(; color_rear < back_lights_of_truck.numPixels(); color_rear++)
   {
    back_lights_of_truck.setPixelColor(color_rear,rear);
   } 
  }
  for(int j = 255; j >= 0; j--)
  {
    for(; color_side_trailer < trailer_side_lights_of_truck.numPixels(); color_side_trailer++)
    {
      trailer_side_lights_of_truck.setPixelColor(color_side_trailer,trailer_side);
    }
  }
  short_lights_of_truck.show();
  back_lights_of_truck.show();
  trailer_side_lights_of_truck.show();
}

void Left_Turn_Signal(uint32_t left)
{
 int left_turn = 0;
 for(int j = 255; j >= 0; j--)
 {
  for(; left_turn < left_turn_signal_of_truck.numPixels(); left_turn++)
  {
   left_turn_signal_of_truck.setPixelColor(left_turn,left);
  }
 }
 left_turn_signal_of_truck.show();
}

void Right_Turn_Signal(uint32_t right)
{
 int right_turn = 0;
 for(int j = 255; j >= 0; j--)
 {
  for(; right_turn < right_turn_signal_of_truck.numPixels(); right_turn++)
  {
   right_turn_signal_of_truck.setPixelColor(right_turn,right);
  }
 }
 right_turn_signal_of_truck.show();
}

void Hazards_Lights(uint32_t left,uint32_t right) 
{
 uint16_t left_color = 0;
 uint16_t right_color = 0;
 for(int j = 255; j >= 0 ; j--)
 {
  for(; left_color < left_turn_signal_of_truck.numPixels(); left_color++) 
  {
   left_turn_signal_of_truck.setPixelColor(left_color, left);
  }       
 }
 for(int j = 255; j >= 0 ; j--)
 {
  for(; right_color < right_turn_signal_of_truck.numPixels(); right_color++) 
  {   
   right_turn_signal_of_truck.setPixelColor(right_color, right);
  }          
 }
 left_turn_signal_of_truck.show();
 right_turn_signal_of_truck.show();
}

void loop()
{
 State_Of_Turn_On_And_Off_Long_Lights = digitalRead(Button_Long_Lights);
 if(State_Of_Turn_On_And_Off_Long_Lights != Last_State_Of_Turn_On_And_Off_Long_Lights) 
 {
  if(State_Of_Turn_On_And_Off_Long_Lights == HIGH) 
  {
   Counter_Turn_On_And_Off_Long_Lights++;
   if(Counter_Turn_On_And_Off_Long_Lights % 2 != 0 && Counter_Turn_On_And_Off_Main_Lights % 2 == 0)
   {
    Long_Lights(long_lights_of_truck.Color(0,0,0));
   }else
   if(Counter_Turn_On_And_Off_Long_Lights % 2 != 0)
   {
    delay(250);
    Long_Lights(long_lights_of_truck.Color(255,255,255));
   }else
   if(Counter_Turn_On_And_Off_Long_Lights % 2 == 0)
   {
    delay(250);
    Long_Lights(long_lights_of_truck.Color(0,0,0));
   }
  }
 }
  
 State_Of_Turn_On_And_Off_Main_Lights = digitalRead(Button_Main_Lights);
 if(State_Of_Turn_On_And_Off_Main_Lights != Last_State_Of_Turn_On_And_Off_Main_Lights) 
 {
  if(State_Of_Turn_On_And_Off_Main_Lights == HIGH) 
  {
   Counter_Turn_On_And_Off_Main_Lights++;
   if(Counter_Turn_On_And_Off_Main_Lights % 2 != 0)
   {
    delay(220);
    Main_Lights(short_lights_of_truck.Color(255,255,255),back_lights_of_truck.Color(255,0,0),trailer_side_lights_of_truck.Color(255,75,0));
   }else
   if(Counter_Turn_On_And_Off_Main_Lights % 2 == 0)
   {
    delay(220);
    Main_Lights(short_lights_of_truck.Color(0,0,0),back_lights_of_truck.Color(0,0,0),trailer_side_lights_of_truck.Color(0,0,0));
   }
   if(Counter_Turn_On_And_Off_Main_Lights % 2 == 0 && Counter_Turn_On_And_Off_Long_Lights % 2 != 0)
   {
    Long_Lights(long_lights_of_truck.Color(0,0,0));
    Main_Lights(short_lights_of_truck.Color(0,0,0),back_lights_of_truck.Color(0,0,0),trailer_side_lights_of_truck.Color(0,0,0));
   }
   if(Counter_Turn_On_And_Off_Main_Lights % 2 != 0 && Counter_Turn_On_And_Off_Long_Lights % 2 != 0)
   {
    Long_Lights(long_lights_of_truck.Color(255,255,255));
    Main_Lights(short_lights_of_truck.Color(255,255,255),back_lights_of_truck.Color(255,0,0),trailer_side_lights_of_truck.Color(255,75,0));
   }
  }
 }

 State_Of_Turn_On_And_Off_Right_Turn_Signal = digitalRead(Button_Right_Turn_Signal);
 if(State_Of_Turn_On_And_Off_Right_Turn_Signal != Last_State_Of_Turn_On_And_Off_Right_Turn_Signal) 
 {
  if(State_Of_Turn_On_And_Off_Right_Turn_Signal == HIGH) 
  {
   Counter_Turn_On_And_Off_Right_Turn_Signal++;
  }
 }
 if(Counter_Turn_On_And_Off_Right_Turn_Signal % 2 != 0 && Counter_Turn_On_And_Off_Hazard_Lights_Signal % 2 == 0)
 {
  Counter_Turn_On_And_Off_Left_Turn_Signal = 0;
  delay(20);
  Right_Turn_Signal(right_turn_signal_of_truck.Color(255,75,0));
  delay(380);
  Right_Turn_Signal(right_turn_signal_of_truck.Color(0,0,0));  
 }
 if(Counter_Turn_On_And_Off_Right_Turn_Signal % 2 == 0 || Counter_Turn_On_And_Off_Left_Turn_Signal % 2 != 0)
 {
  Right_Turn_Signal(right_turn_signal_of_truck.Color(0,0,0));
  delay(190);
 }

 State_Of_Turn_On_And_Off_Left_Turn_Signal = digitalRead(Button_Left_Turn_Signal);
 if(State_Of_Turn_On_And_Off_Left_Turn_Signal != Last_State_Of_Turn_On_And_Off_Left_Turn_Signal) 
 {
  if(State_Of_Turn_On_And_Off_Left_Turn_Signal == HIGH) 
  {
   Counter_Turn_On_And_Off_Left_Turn_Signal++;
  }
 }
 if(Counter_Turn_On_And_Off_Left_Turn_Signal % 2 != 0 && Counter_Turn_On_And_Off_Hazard_Lights_Signal % 2 == 0)
 {
  Counter_Turn_On_And_Off_Right_Turn_Signal = 0;
  delay(20);
  Left_Turn_Signal(left_turn_signal_of_truck.Color(255,75,0));
  delay(380);
  Left_Turn_Signal(left_turn_signal_of_truck.Color(0,0,0));
 }
 if(Counter_Turn_On_And_Off_Left_Turn_Signal % 2 == 0 || Counter_Turn_On_And_Off_Right_Turn_Signal % 2 != 0)
 {
  Left_Turn_Signal(left_turn_signal_of_truck.Color(0,0,0));
  delay(190);
 }

 State_Of_Turn_On_And_Off_Hazard_Lights_Signal = digitalRead(Button_Hazard_Lights_Signal);
 if(State_Of_Turn_On_And_Off_Hazard_Lights_Signal != Last_State_Of_Turn_On_And_Off_Hazard_Lights_Signal) 
 {
  if(State_Of_Turn_On_And_Off_Hazard_Lights_Signal == HIGH) 
  {
   Counter_Turn_On_And_Off_Hazard_Lights_Signal++;
  }
 }
 if(Counter_Turn_On_And_Off_Hazard_Lights_Signal % 2 != 0 && Counter_Turn_On_And_Off_Left_Turn_Signal % 2 != 0)
 {
  delay(180);
  Hazards_Lights(left_turn_signal_of_truck.Color(255,75,0),right_turn_signal_of_truck.Color(255,75,0));
  Hazards_Lights(left_turn_signal_of_truck.Color(0,0,0),right_turn_signal_of_truck.Color(0,0,0)); 
 }
 if(Counter_Turn_On_And_Off_Hazard_Lights_Signal % 2 != 0 && Counter_Turn_On_And_Off_Right_Turn_Signal % 2 != 0)
 {
  delay(180);
  Hazards_Lights(left_turn_signal_of_truck.Color(255,75,0),right_turn_signal_of_truck.Color(255,75,0));
  Hazards_Lights(left_turn_signal_of_truck.Color(0,0,0),right_turn_signal_of_truck.Color(0,0,0)); 
 }
 if(Counter_Turn_On_And_Off_Hazard_Lights_Signal % 2 != 0)
 {
  delay(30);
  Hazards_Lights(left_turn_signal_of_truck.Color(255,75,0),right_turn_signal_of_truck.Color(255,75,0));
  delay(380);
  Hazards_Lights(left_turn_signal_of_truck.Color(0,0,0),right_turn_signal_of_truck.Color(0,0,0)); 
 }
 if(Counter_Turn_On_And_Off_Hazard_Lights_Signal % 2 == 0)
 {
  Hazards_Lights(left_turn_signal_of_truck.Color(0,0,0),right_turn_signal_of_truck.Color(0,0,0)); 
  delay(190);
 }
 if(irrecv.decode(&results))
 {
  if(results.value == 0xBB1 || results.value == 0x3B1)
  {
   count_remote_control_short_lights++;
   if(count_remote_control_short_lights % 2 != 0 && count_remote_control_long_lights % 2 == 0)
   {
    count_remote_control_long_lights = 0;
    delay(50);
    Main_Lights(short_lights_of_truck.Color(255,255,255),back_lights_of_truck.Color(255,0,0),trailer_side_lights_of_truck.Color(255,75,0));
   }else
   if(count_remote_control_short_lights % 2 != 0 && count_remote_control_long_lights % 2 != 0)
   {
    Main_Lights(short_lights_of_truck.Color(255,255,255),back_lights_of_truck.Color(255,0,0),trailer_side_lights_of_truck.Color(255,75,0));
    Long_Lights(long_lights_of_truck.Color(255,255,255));
   }else
   {
    delay(50);
    Main_Lights(short_lights_of_truck.Color(0,0,0),back_lights_of_truck.Color(0,0,0),trailer_side_lights_of_truck.Color(0,0,0));
   }
   if(count_remote_control_short_lights % 2 == 0 && count_remote_control_long_lights % 2 != 0)
   {
     count_remote_control_long_lights = 1;
     Main_Lights(short_lights_of_truck.Color(0,0,0),back_lights_of_truck.Color(0,0,0),trailer_side_lights_of_truck.Color(0,0,0));
     Long_Lights(long_lights_of_truck.Color(0,0,0));          
   }
  }
  if(results.value == 0xBBA || results.value == 0x3BA)
  {
   count_remote_control_long_lights++;
   if(count_remote_control_long_lights % 2 != 0 && count_remote_control_short_lights % 2 != 0)
   {
    delay(50);
    Long_Lights(long_lights_of_truck.Color(255,255,255));
   }else
   if(count_remote_control_short_lights % 2 == 0)
   {
    count_remote_control_long_lights = 0;
    delay(50);
    Long_Lights(long_lights_of_truck.Color(0,0,0));   
   }
   if(count_remote_control_short_lights % 2 != 0 && count_remote_control_long_lights % 2 == 0)
   {
    count_remote_control_long_lights = 0;
    delay(50);
    Long_Lights(long_lights_of_truck.Color(0,0,0));   
   }
   if(count_remote_control_short_lights % 2 != 0 && count_remote_control_long_lights % 2 != 0)
   {
    count_remote_control_long_lights = 1;
    delay(50);
    Long_Lights(long_lights_of_truck.Color(255,255,255));  
   }
  }
  if(results.value == 0xB96 || results.value == 0x396)
  {
   count_remote_control_left_turn_signal++;
   Counter_Turn_On_And_Off_Left_Turn_Signal++;
   count_remote_control_right_turn_signal = 0;
   Counter_Turn_On_And_Off_Right_Turn_Signal = 0;    
  }
  if(results.value == 0xBB2 || results.value == 0x3B2)
  {
   count_remote_control_hazard_lights++;
   Counter_Turn_On_And_Off_Hazard_Lights_Signal++;
   if(count_remote_control_hazard_lights % 2 != 0 && count_remote_control_left_turn_signal % 2 != 0)
   {
    previous_left = 1;
    count_remote_control_left_turn_signal = 0;
    Counter_Turn_On_And_Off_Left_Turn_Signal = 0;     
   }else
   if(count_remote_control_hazard_lights % 2 != 0 && count_remote_control_right_turn_signal % 2 != 0)
   {
    previous_right = 1;
    count_remote_control_right_turn_signal = 0;
    previous_left = 0;
    Counter_Turn_On_And_Off_Right_Turn_Signal = 0; 
   }else
   if(count_remote_control_hazard_lights % 2 == 0 && previous_left % 2 != 0)
   {
     count_remote_control_left_turn_signal = 1;
     Counter_Turn_On_And_Off_Left_Turn_Signal = 1;      
   }else
   if(count_remote_control_hazard_lights % 2 == 0 && previous_right % 2 != 0)
   {
     count_remote_control_right_turn_signal = 1; 
     count_remote_control_left_turn_signal = 0;
     Counter_Turn_On_And_Off_Right_Turn_Signal = 1; 
   }else
   if(count_remote_control_left_turn_signal % 2 == 0)
   {
    previous_left = 0;
    previous_right = 0;
    count_remote_control_right_turn_signal = 0;
   }else
   if(count_remote_control_right_turn_signal % 2 == 0)
   {
    previous_right = 0;
    count_remote_control_right_turn_signal = 0;
   }
  }
  if(results.value == 0xB90 || results.value == 0x390)
  {
   count_remote_control_right_turn_signal++;
   count_remote_control_left_turn_signal = 0;
   Counter_Turn_On_And_Off_Right_Turn_Signal++;
   Counter_Turn_On_And_Off_Left_Turn_Signal = 0;        
  }
   irrecv.resume();
  }
  /*
  if(count_remote_control_left_turn_signal % 2 != 0 && count_remote_control_hazard_lights % 2 == 0)
  {
   Left_Turn_Signal(left_turn_signal_of_truck.Color(255,75,0));
   delay(390);
   Left_Turn_Signal(left_turn_signal_of_truck.Color(0,0,0));
   Right_Turn_Signal(right_turn_signal_of_truck.Color(0,0,0));  
   if(count_remote_control_right_turn_signal == 2)
   {
    Right_Turn_Signal(right_turn_signal_of_truck.Color(0,0,0));
   }
  }
  if(count_remote_control_right_turn_signal % 2 != 0)
  {
   Right_Turn_Signal(right_turn_signal_of_truck.Color(255,75,0));
   delay(390);
   Right_Turn_Signal(right_turn_signal_of_truck.Color(0,0,0));
   Left_Turn_Signal(left_turn_signal_of_truck.Color(0,0,0));
   if(count_remote_control_left_turn_signal == 2)
   {
    Left_Turn_Signal(left_turn_signal_of_truck.Color(0,0,0));
   }
  }
  //if(count_remote_control_hazard_lights % 2 != 0)
  {
   //Hazards_Lights(left_turn_signal_of_truck.Color(255,75,0),right_turn_signal_of_truck.Color(255,75,0));
   //delay(380);
   //Hazards_Lights(left_turn_signal_of_truck.Color(0,0,0),right_turn_signal_of_truck.Color(0,0,0)); 
  }
  if(count_remote_control_hazard_lights % 2 != 0)
  {
   Hazards_Lights(left_turn_signal_of_truck.Color(255,75,0),right_turn_signal_of_truck.Color(255,75,0));
   delay(300);
   Hazards_Lights(left_turn_signal_of_truck.Color(0,0,0),right_turn_signal_of_truck.Color(0,0,0)); 
  }
  //COMPAREMENT FOR BOTH PUSHED REMOTE OR TACTILE BUTTON FOR LONG LIGHTS
  if(Counter_Turn_On_And_Off_Long_Lights % 2 != 0 && count_remote_control_long_lights % 2 != 0)
  {
   Long_Lights(long_lights_of_truck.Color(0,0,0));
   Counter_Turn_On_And_Off_Long_Lights = 0;
   count_remote_control_long_lights = 0;
  }
  if(Counter_Turn_On_And_Off_Long_Lights % 2 != 0 && count_remote_control_long_lights % 2 == 0)
  {
   Long_Lights(long_lights_of_truck.Color(255,255,255));
   Counter_Turn_On_And_Off_Long_Lights = 1; 
  }
  //COMPAREMENT FOR BOTH PUSHED REMOTE OR TACTILE BUTTON FOR MAIN LIGHTS
  if(Counter_Turn_On_And_Off_Main_Lights % 2 != 0 && count_remote_control_short_lights % 2 != 0)
  {
   Main_Lights(short_lights_of_truck.Color(0,0,0),back_lights_of_truck.Color(0,0,0),trailer_side_lights_of_truck.Color(0,0,0));
   Counter_Turn_On_And_Off_Main_Lights = 0;
   count_remote_control_short_lights = 0;
  }
  if(Counter_Turn_On_And_Off_Main_Lights % 2 != 0 && count_remote_control_short_lights % 2 == 0)
  {
   Main_Lights(short_lights_of_truck.Color(255,255,255),back_lights_of_truck.Color(255,0,0),trailer_side_lights_of_truck.Color(255,75,0));
   Counter_Turn_On_And_Off_Main_Lights = 1; 
  }
  //COMPAREMENT FOR BOTH PUSHED REMOTE OR TACTILE BUTTON FOR LEFT TURN SIGNAL
  if(Counter_Turn_On_And_Off_Left_Turn_Signal % 2 != 0 && count_remote_control_left_turn_signal % 2 != 0)
  {
   //Left_Turn_Signal(left_turn_signal_of_truck.Color(0,0,0));
   Counter_Turn_On_And_Off_Left_Turn_Signal = 0;
   count_remote_control_left_turn_signal = 0;
  }
  */
}
