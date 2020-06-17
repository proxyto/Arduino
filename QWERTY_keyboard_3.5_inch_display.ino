#include <MCUFRIEND_kbv.h> 
#include <Adafruit_GFX.h>    
#include <TouchScreen.h>

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
#define GRAY 0x8410

MCUFRIEND_kbv tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364);

boolean key_board = true;
boolean buttonKeyboard = false;
boolean close_keyboard = false;
boolean dot = false;
boolean comma = false;
boolean symbols_button = false;
boolean caps_button = false;
int sym = 0;
int pos = 39;
int count_caps = 0;

char alphabet[26] = { 'a','b',
                      'c','d',
                      'e','f',
                      'g','h',
                      'i','j',
                      'k','l',
                      'm','n',
                      'o','p',
                      'q','r',
                      's','t',
                      'u','v',
                      'w','x',
                      'y','z'
                     };

char CAPS_letters[26] = { 'A','B',
                          'C','D',
                          'E','F',
                          'G','H',
                          'I','J',
                          'K','L',
                          'M','N',
                          'O','P',
                          'Q','R',
                          'S','T',
                          'U','V',
                          'W','X',
                          'Y','Z'
                        };                     
                     
char symbols[3] = {'.', ',', ' '};
char numbers[10] = {'1','2','3','4','5','6','7','8','9','0'};

char additional_symbols[] = {'+','x','=','/','_','!','@','#','$','%','^','&','*','(',')',
                            '-','\'','"',':',';',',','?'};
char pound_sign = 156;
                            
void setup() 
{
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(0x9486);
  Home_Screen(); 
}

void Cursor()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.fillRect(78,4,1,20,BLUE);
  delay(500);
  tft.fillRect(78,4,1,20,WHITE);
  delay(500);
}

void Search_Bar()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.fillCircle(34,14,12,WHITE);
  tft.fillRect(37,2,400,25,WHITE);
  tft.fillCircle(434,14,12,WHITE);
  tft.drawLine(50,15,55,20,BLUE);
  tft.drawLine(49,16,54,21,BLUE);
  tft.drawLine(50,16,54,21,BLUE);
  tft.drawLine(51,16,54,21,BLUE);
  tft.drawLine(52,16,54,21,BLUE);
  tft.fillCircle(45,11,6,BLUE);
  tft.fillCircle(45,11,4,WHITE);
  tft.setCursor(60,7);
  tft.setTextSize(2);
  tft.setTextColor(GRAY);
  tft.print("Search...");
}

void Empty_Search_Bar()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.fillCircle(34,14,12,WHITE);
  tft.fillRect(37,2,400,25,WHITE);
  tft.fillCircle(434,14,12,WHITE);
}

void Home_Screen()
{ 
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  Search_Bar();
}

void Hide_Keyboard()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  tft.setRotation(1);
  tft.fillRect(0,27,480,320,BLACK);
  Search_Bar();
}

void Line_For_Digits_Of_Keyboard()
{
  tft.fillRect(0,76,44,44,WHITE);
  tft.fillRect(48,76,44,44,WHITE);
  tft.fillRect(96,76,44,44,WHITE);
  tft.fillRect(144,76,44,44,WHITE);
  tft.fillRect(192,76,44,44,WHITE);
  tft.fillRect(240,76,44,44,WHITE);
  tft.fillRect(288,76,44,44,WHITE);
  tft.fillRect(336,76,44,44,WHITE);
  tft.fillRect(384,76,44,44,WHITE);
  tft.fillRect(432,76,44,44,WHITE);
}

void First_Line_For_Letters_Of_Keyboard()
{
  tft.fillRect(0,125,44,44,WHITE);
  tft.fillRect(48,125,44,44,WHITE);
  tft.fillRect(96,125,44,44,WHITE);
  tft.fillRect(144,125,44,44,WHITE);
  tft.fillRect(192,125,44,44,WHITE);
  tft.fillRect(240,125,44,44,WHITE);
  tft.fillRect(288,125,44,44,WHITE);
  tft.fillRect(336,125,44,44,WHITE);
  tft.fillRect(384,125,44,44,WHITE);
  tft.fillRect(432,125,44,44,WHITE);
}

void Second_Line_For_Letters_Of_Keyboard()
{
  tft.fillRect(24,174,44,44,WHITE);
  tft.fillRect(72,174,44,44,WHITE);
  tft.fillRect(120,174,44,44,WHITE);
  tft.fillRect(168,174,44,44,WHITE);
  tft.fillRect(216,174,44,44,WHITE);
  tft.fillRect(264,174,44,44,WHITE);
  tft.fillRect(312,174,44,44,WHITE);
  tft.fillRect(360,174,44,44,WHITE);
  tft.fillRect(408,174,44,44,WHITE);
}

void Third_Line_For_Letters_Of_Keyboard()
{
  tft.fillRect(72,223,44,44,WHITE);
  tft.fillRect(120,223,44,44,WHITE);
  tft.fillRect(168,223,44,44,WHITE);
  tft.fillRect(216,223,44,44,WHITE);
  tft.fillRect(264,223,44,44,WHITE);
  tft.fillRect(312,223,44,44,WHITE);
  tft.fillRect(360,223,44,44,WHITE);
}

void Other_Buttons_Of_Keyboard()
{
  //FOR CAPS LETTERS
  tft.fillRect(0,223,61,44,WHITE);
  tft.fillTriangle(12,243,29,225,46,243,BLACK);
  tft.fillRect(24,243,12,17,BLACK);
  //FOR DELETE(BACKSPACE)
  tft.fillRect(417,223,61,44,WHITE);
  tft.fillTriangle(446,228,429,244,446,260,BLACK);
  tft.fillRect(447,228,30,32,BLACK);
  //FOR COMMA
  tft.fillRect(72,272,44,44,WHITE);
  //FOR SPACE
  tft.fillRect(120,272,236,44,WHITE);
  //FOR DOT
  tft.fillRect(360,272,44,44,WHITE);
  tft.fillCircle(381,310,3,BLACK);
  //FOR ENTER
  tft.fillRect(408,272,70,44,WHITE);
  tft.fillTriangle(431,278,414,294,431,310,BLACK);
  tft.fillRect(431,288,35,12,BLACK);
  tft.fillRect(455,275,11,14,BLACK);
  //FOR SYMBOLS
  tft.fillRect(0,272,67,44,WHITE);
}

void Second_Line_Additional_Symbols()
{
  tft.fillRect(0,174,44,44,WHITE);
  tft.fillRect(48,174,44,44,WHITE);
  tft.fillRect(96,174,44,44,WHITE);
  tft.fillRect(144,174,44,44,WHITE);
  tft.fillRect(192,174,44,44,WHITE);
  tft.fillRect(240,174,44,44,WHITE);
  tft.fillRect(288,174,44,44,WHITE);
  tft.fillRect(336,174,44,44,WHITE);
  tft.fillRect(384,174,44,44,WHITE);
  tft.fillRect(432,174,44,44,WHITE);
}

void Additional_Symbols()
{
  pinMode(XM,OUTPUT);
  pinMode(YP,OUTPUT);
  tft.fillRect(0,27,480,320,BLACK);
  tft.setRotation(1);
  //Empty_Search_Bar();
  Line_For_Digits_Of_Keyboard();
  First_Line_For_Letters_Of_Keyboard();
  Second_Line_Additional_Symbols();
  Third_Line_For_Letters_Of_Keyboard();
  Other_Buttons_Of_Keyboard();
  Digits();
  Symbols();
}

void Symbols()
{
  pinMode(XM,OUTPUT);
  pinMode(YP,OUTPUT);
  tft.setRotation(1);
  tft.setCursor(451,231);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("x");
  tft.setCursor(59,225);
  tft.setTextSize(1);
  tft.setTextColor(BLACK);
  tft.print(",");
  tft.setCursor(7,283);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("ABC");
  tft.setCursor(14,137);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("+");
  tft.setCursor(62,134);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("x");
  tft.setCursor(113,130);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print(".");
  tft.setCursor(111,137);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("-");
  tft.setCursor(113,141);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print(".");
  tft.setCursor(159,137);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("=");
  tft.setCursor(206,137);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("/");
  tft.setCursor(254,139);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("_");
  tft.setCursor(299,137);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("C");
  tft.setCursor(299,140);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("=");
  tft.setCursor(350,137);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print(pound_sign);
  tft.setCursor(398,137);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("Y");
  tft.setCursor(398,141);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("=");
  tft.setCursor(446,137);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("W");
  tft.setCursor(433,147);
  tft.setTextSize(1);
  tft.setTextColor(BLACK);
  tft.print("-------");

  tft.setCursor(12,183);
  tft.setTextSize(4);
  tft.setTextColor(BLACK);
  tft.print("!");
  tft.setCursor(62,187);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("@");
  tft.setCursor(110,187);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("#");
  tft.setCursor(157,187);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("$");
  tft.setCursor(204,187);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("%");
  tft.setCursor(254,184);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("^");
  tft.setCursor(303,186);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("&");
  tft.setCursor(351,184);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("*");
  tft.setCursor(398,187);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("(");
  tft.setCursor(449,187);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print(")");

  tft.setCursor(87,237);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("-");
  tft.setCursor(134,232);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("'");
  tft.setCursor(184,232);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("\"");
  tft.setCursor(226,228);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(":");
  tft.setCursor(275,230);
  tft.setTextSize(4);
  tft.setTextColor(BLACK);
  tft.print(";");
  tft.setCursor(324,241);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print(",");
  tft.setCursor(373,237);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("?");
  tft.setCursor(87,291);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print(",");
  
  tft.fillRect(0,223,61,44,WHITE);
  tft.setCursor(1,235);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("1/2");
}

void Keyboard_Activated()
{
  pinMode(XM,OUTPUT);
  pinMode(YP,OUTPUT);
  tft.setRotation(1);
  Empty_Search_Bar();
  
  //LINE FOR DIGITS
  Line_For_Digits_Of_Keyboard();
  
  //FIRST LINE OF LETTERS
  First_Line_For_Letters_Of_Keyboard();

  //SECOND LINE OF LETTERS
  Second_Line_For_Letters_Of_Keyboard();

  //THIRD LINE OF LETTERS
  Third_Line_For_Letters_Of_Keyboard();

  //OTHER BUTTONS
  Other_Buttons_Of_Keyboard();
  Digits();
  Letters();
}

void CAPS_Keyboard_Activated()
{
  pinMode(XM,OUTPUT);
  pinMode(YP,OUTPUT);
  tft.setRotation(1);
  tft.fillRect(0,27,480,320,BLACK);
  
  //LINE FOR DIGITS
  Line_For_Digits_Of_Keyboard();
  
  //FIRST LINE OF LETTERS
  First_Line_For_Letters_Of_Keyboard();

  //SECOND LINE OF LETTERS
  Second_Line_For_Letters_Of_Keyboard();

  //THIRD LINE OF LETTERS
  Third_Line_For_Letters_Of_Keyboard();

  //OTHER BUTTONS
  Other_Buttons_Of_Keyboard();
  Digits();
  CAPS_Letters();
}

void Safe_Search_Bar()
{
  pinMode(XM,OUTPUT);
  pinMode(YP,OUTPUT);
  tft.setRotation(1);
  
  //LINE FOR DIGITS
  Line_For_Digits_Of_Keyboard();
  
  //FIRST LINE OF LETTERS
  First_Line_For_Letters_Of_Keyboard();

  //SECOND LINE OF LETTERS
  Second_Line_For_Letters_Of_Keyboard();

  //THIRD LINE OF LETTERS
  Third_Line_For_Letters_Of_Keyboard();

  //OTHER BUTTONS
  Other_Buttons_Of_Keyboard();
  Digits();
  Letters();
}

void Digits()
{
  pinMode(XM,OUTPUT);
  pinMode(YP,OUTPUT);
  tft.setRotation(1);
  tft.setCursor(15,88);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("1");
  tft.setCursor(63,88);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("2");
  tft.setCursor(111,89);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("3");
  tft.setCursor(159,89);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("4");
  tft.setCursor(207,89);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("5");
  tft.setCursor(255,89);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("6");
  tft.setCursor(303,89);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("7");
  tft.setCursor(351,89);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("8");
  tft.setCursor(399,89);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("9");
  tft.setCursor(447,89);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("0");
}

void Letters()
{
  pinMode(XM,OUTPUT);
  pinMode(YP,OUTPUT);
  tft.setRotation(1);
  tft.setCursor(14,133);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("q");
  tft.setCursor(63,133);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("w");
  tft.setCursor(111,133);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("e");
  tft.setCursor(159,133);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("r");
  tft.setCursor(207,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("t");
  tft.setCursor(255,133);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("y");
  tft.setCursor(303,133);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("u");
  tft.setCursor(351,133);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("i");
  tft.setCursor(399,133);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("o");
  tft.setCursor(447,133);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("p");

  
  tft.setCursor(39,182);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("a");
  tft.setCursor(87,182);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("s");
  tft.setCursor(135,182);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("d");
  tft.setCursor(183,182);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("f");
  tft.setCursor(231,182);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("g");
  tft.setCursor(279,182);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("h");
  tft.setCursor(327,182);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("j");
  tft.setCursor(375,182);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("k");
  tft.setCursor(423,182);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("l");

  tft.setCursor(87,231);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("z");
  tft.setCursor(135,231);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("x");
  tft.setCursor(183,231);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("c");
  tft.setCursor(231,231);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("v");
  tft.setCursor(279,231);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("b");
  tft.setCursor(327,231);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("n");
  tft.setCursor(375,231);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("m");
  tft.setCursor(451,231);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("x");
  tft.setCursor(87,291);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print(",");
  tft.setCursor(7,283);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("!#1");
}

void CAPS_Letters()
{
  pinMode(XM,OUTPUT);
  pinMode(YP,OUTPUT);
  tft.setRotation(1);
  tft.setCursor(14,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("Q");
  tft.setCursor(63,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("W");
  tft.setCursor(111,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("E");
  tft.setCursor(159,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("R");
  tft.setCursor(207,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("T");
  tft.setCursor(255,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("Y");
  tft.setCursor(303,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("U");
  tft.setCursor(351,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("I");
  tft.setCursor(399,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("O");
  tft.setCursor(447,136);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("P");

  
  tft.setCursor(39,185);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("A");
  tft.setCursor(87,185);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("S");
  tft.setCursor(135,185);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("D");
  tft.setCursor(183,185);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("F");
  tft.setCursor(231,185);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("G");
  tft.setCursor(279,185);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("H");
  tft.setCursor(327,185);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("J");
  tft.setCursor(375,185);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("K");
  tft.setCursor(423,185);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("L");

  tft.setCursor(87,234);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("Z");
  tft.setCursor(135,234);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("X");
  tft.setCursor(183,234);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("C");
  tft.setCursor(231,234);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("V");
  tft.setCursor(279,234);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("B");
  tft.setCursor(327,234);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("N");
  tft.setCursor(375,234);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("M");
  tft.setCursor(451,234);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("x");
  tft.setCursor(87,291);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print(",");
  tft.setCursor(7,283);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("!#1");
}

void Symbol_Keyboard()
{
 TSPoint button = ts.getPoint();
  
 if(symbols_button == true)
 { 
  if(button.z > ts.pressureThreshhold && symbols_button == true);
  {
    button.x = map(button.x, TS_MINX, TS_MAXX , tft.height(),0);
    button.y = map(button.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = button.x;
    button.x = button.y;
    button.y = t;

    //DIGIT 1
    if(button.x < 18)
    {
    if(button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
       pos+=5;
       dot = false;
       comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[0]);
      }
    }
    }else
    if(button.x < 18 && button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
       pos+=5;
       dot = false;
       comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[0]);
      }
    }
    //DIGIT 2
    if(button.x > 29 && button.x < 70)
    {
     if(button.y >= 87 && button.y <= 122 && symbols_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[1]);
      }
     }
    }else
    if(button.x > 29 && button.x < 70 && button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[1]);
      }
    }
    //DIGIT 3
    if(button.x > 80 && button.x < 121)
    {
    if(button.y >= 87 && button.y <= 122 && symbols_button)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[2]);
      }
     }
    }else
    if(button.x > 80 && button.x < 121 && button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[2]);
      }
    }
    //DIGIT 4
    if(button.x > 136 && button.x < 173)
    {
    if(button.y >= 87 && button.y <= 122 && symbols_button)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[3]);
      }
     }
    }else
    if(button.x > 136 && button.x < 173 && button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[3]);
      }
    }
    //DIGIT 5
    if(button.x > 185 && button.x < 227)
    {
      if(button.y >= 87 && button.y <= 122 && symbols_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[4]);
      }
     }
    }else
    if(button.x > 185 && button.x < 227 && button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[4]);
      }
    }
    //DIGIT 6
    if(button.x > 240 && button.x < 285)
    {
      if(button.y >= 87 && button.y <= 122 && symbols_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[5]);
      }
     }
    }else
    if(button.x > 240 && button.x < 285 && button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[5]);
      }
    }
    //DIGIT 7
    if(button.x > 296 && button.x < 333)
    {
    if(button.y >= 87 && button.y <= 122 && symbols_button)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[6]);
      }
     }
    }else
    if(button.x > 296 && button.x < 333 && button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[6]);
      }
    }
    //DIGIT 8
    if(button.x > 353 && button.x < 393)
    {
      if(button.y >= 87 && button.y <= 122 && symbols_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[7]);
      }
     }
    }else
    if(button.x > 353 && button.x < 393 && button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[7]);
      }
    }
    //DIGIT 9
    if(button.x > 407 && button.x < 447)
    {
      if(button.y >= 87 && button.y <= 122 && symbols_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[8]);
      }
     }
    }else
    if(button.x > 407 && button.x < 447 && button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[8]);
      }
    }
    //DIGIT 0
    if(button.x > 460 && button.x < 500)
    {
      if(button.y >= 87 && button.y <= 122 && symbols_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[9]);
      }
     }
    }else
    if(button.x > 460 && button.x < 500 && button.y >= 87 && button.y <= 122 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[9]);
      }
    }

    //+ SIGN
    if(button.x < 18)
    {
    if(button.y >= 135 && button.y <= 168 && symbols_button)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setRotation(1);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[0]);
      }
    }
  }else
   if(button.x < 18 && button.y >= 135 && button.y <= 168 && symbols_button)
   {
     if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setRotation(1);
       tft.setCursor(pos,8);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(additional_symbols[0]);
      }
   }
   //X sign
   if(button.x > 29 && button.x < 70)
    {
     if(button.y >= 135 && button.y <= 168 && symbols_button)
     {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[1]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
     }
    }else
    if(button.x > 29 && button.x < 70 && button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[1]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    //DIVISION SIGN
    if(button.x > 80 && button.x < 121)
    {
     if(button.y >= 135 && button.y <= 168 && symbols_button)
     { 
      pos+=13;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,5);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(".");
      pos-=2;
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("-");
      pos+=2;
      tft.setCursor(pos,12);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(".");
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
     }
    }else
    if(button.x > 80 && button.x < 121 && button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=13;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,5);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(".");
      pos-=2;
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("-");
      pos+=2;
      tft.setCursor(pos,12);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(".");
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    //= SIGN
    if(button.x > 136 && button.x < 173)
    {
     if(button.y >= 135 && button.y <= 168 && symbols_button)
     {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[2]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
     }
    }else
    if(button.x > 136 && button.x < 173 && button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[2]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // / SIGN
    if(button.x > 185 && button.x < 227)
    {
     if(button.y >= 135 && button.y <= 168 && symbols_button)
     {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[3]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
     }
    }else
    if(button.x > 185 && button.x < 227 && button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[3]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // _ SIGN
    if(button.x > 240 && button.x < 285)
    {
    if(button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,11);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[4]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 240 && button.x < 285 && button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,11);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[4]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // EURO SIGN
    if(button.x > 296 && button.x < 333)
    {
     if(button.y >= 135 && button.y <= 168 && symbols_button)
     {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("C");
      tft.setCursor(pos,11);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print("=");
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
     }
    }else
    if(button.x > 296 && button.x < 333 && button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("C");
      tft.setCursor(pos,11);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print("=");
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // POUND SIGN
    if(button.x > 353 && button.x < 393)
    {
    if(button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(pound_sign);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 353 && button.x < 393 && button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(pound_sign);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // YEN SIGN
    if(button.x > 407 && button.x < 447)
    {
    if(button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("Y");
      tft.setCursor(pos,11);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("=");
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 407 && button.x < 447 && button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("Y");
      tft.setCursor(pos,11);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("=");
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // WON SIGN
    if(button.x > 460 && button.x < 500)
    {
    if(button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=17;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("W");
      pos-=5;
      tft.setCursor(pos,10);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("--");
      }
      pos+=11;
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 460 && button.x < 500 && button.y >= 135 && button.y <= 168 && symbols_button)
    {
      pos+=17;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("W");
      pos-=5;
      tft.setCursor(pos,10);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("--");
      }
      pos+=11;
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    } 
    // ! SIGN
    if(button.x < 18)
    {
    if(button.y >= 184 && button.y <= 218 && symbols_button)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setRotation(1);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[5]);
      }
    }
  }else
   if(button.x < 18 && button.y >= 184 && button.y <= 218 && symbols_button)
   {
     if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
     if(pos >= 425)
     {
      pos = 425;      
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(WHITE);
      tft.print(" ");
     }else
     { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setRotation(1);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[5]);
     }
   }
   // @ sign
   if(button.x > 29 && button.x < 70)
    {
     if(button.y >= 184 && button.y <= 218 && symbols_button)
     {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[6]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
     }
    }else
    if(button.x > 29 && button.x < 70 && button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[6]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // # SIGN
    if(button.x > 80 && button.x < 121)
    {
     if(button.y >= 184 && button.y <= 218 && symbols_button)
     { 
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[7]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
     }
    }else
    if(button.x > 80 && button.x < 121 && button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[7]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // $ SIGN
    if(button.x > 136 && button.x < 173)
    {
     if(button.y >= 184 && button.y <= 218 && symbols_button)
     {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[8]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
     }
    }else
    if(button.x > 136 && button.x < 173 && button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[8]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // % SIGN
    if(button.x > 185 && button.x < 227)
    {
     if(button.y >= 184 && button.y <= 218 && symbols_button)
     {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[9]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
     }
    }else
    if(button.x > 185 && button.x < 227 && button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[9]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // ^ SIGN
    if(button.x > 240 && button.x < 285)
    {
    if(button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,9);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[10]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 240 && button.x < 285 && button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,9);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[10]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // & SIGN
    if(button.x > 296 && button.x < 333)
    {
     if(button.y >= 184 && button.y <= 218 && symbols_button)
     {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[11]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
     }
    }else
    if(button.x > 296 && button.x < 333 && button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[11]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // * SIGN
    if(button.x > 353 && button.x < 393)
    {
    if(button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=11;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,9);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[12]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 353 && button.x < 393 && button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=11;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,9);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[12]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // ( SIGN
    if(button.x > 407 && button.x < 447)
    {
    if(button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[13]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 407 && button.x < 447 && button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[13]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // ) SIGN
    if(button.x > 460 && button.x < 500)
    {
    if(button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[14]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 460 && button.x < 500 && button.y >= 184 && button.y <= 218 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[14]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // - SIGN
    if(button.x > 55 && button.x < 95)
    {
    if(button.y >= 232 && button.y <= 264 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[15]);
      }
    }
    }else
    if(button.x > 55 && button.x < 95 && button.y >= 232 && button.y <= 264 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,8);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[15]);
      }
    }
    // ' SIGN
    if(button.x > 106 && button.x < 146)
    {
    if(button.y >= 232 && button.y <= 264 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[16]);
      }
    }
    }else
    if(button.x > 106 && button.x < 146 && button.y >= 232 && button.y <= 264 && symbols_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[16]);
      }
    }
     // " SIGN
    if(button.x > 160 && button.x < 200)
    {
    if(button.y >= 232 && button.y <= 264 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[17]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 160 && button.x < 200 && button.y >= 232 && button.y <= 264 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[17]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // : SIGN
    if(button.x > 213 && button.x < 253)
    {
    if(button.y >= 232 && button.y <= 264 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,7);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[18]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 213 && button.x < 253 && button.y >= 232 && button.y <= 264 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,7);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[18]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    // ; SIGN
    if(button.x > 271 && button.x < 311)
    {
    if(button.y >= 232 && button.y <= 264 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[19]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 271 && button.x < 311 && button.y >= 232 && button.y <= 264 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[19]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    //, SIGN
    if(button.x > 321 && button.x < 362)
    {
    if(button.y >= 232 && button.y <= 264 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,16);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[20]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 321 && button.x < 362 && button.y >= 232 && button.y <= 264 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,16);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[20]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
     // ? SIGN
    if(button.x > 378 && button.x < 418)
    {
    if(button.y >= 232 && button.y <= 264 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,7);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[21]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    }else
    if(button.x > 378 && button.x < 418 && button.y >= 232 && button.y <= 264 && symbols_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,7);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(additional_symbols[21]);
      }
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }
    }
    //RETURN TO LETTERS
  if(button.x < 45)
  {
   if(button.y > 276 && button.y < 320 && symbols_button)
   {
    delay(150);
    pinMode(XM,OUTPUT);
    pinMode(YP,OUTPUT);
    symbols_button = false;
    caps_button = false;
    count_caps = 0;
    tft.fillRect(0,27,480,320,BLACK);
    Safe_Search_Bar();
   }
  }else
   if(button.x < 45 && button.y > 276 && button.y < 320 && symbols_button)
   {
    delay(150);
    pinMode(XM,OUTPUT);
    pinMode(YP,OUTPUT);
    symbols_button = false;
    caps_button = false;
    count_caps = 0;
    tft.fillRect(0,27,480,320,BLACK);
    Safe_Search_Bar();
   }else
   //DOT
    if(button.x > 378 && button.x < 418)
    {
      if(button.y > 276 && button.y < 320  && buttonKeyboard)
      {
       delay(150);
       pos+=9;
       if(pos >= 425)
       {
        pos = 425;      
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,6);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(" ");
       }else
       {
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,13);
        tft.setTextSize(1);
        tft.setTextColor(BLACK);
        tft.print(symbols[0]);
        dot = true;
       }
      }else
      if(button.x > 378 && button.x < 418 && button.y > 276 && button.y < 320  && buttonKeyboard)
      {
       delay(150);
       pos+=9;
       if(pos >= 425)
       {
        pos = 425;      
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,6);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(" ");
       }else
       {
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,13);
        tft.setTextSize(1);
        tft.setTextColor(BLACK);
        tft.print(symbols[0]);
        dot = true;
       }
      }
    }
    //BACKSPACE
    if(button.x > 444 && button.x < 500)
    {
      if(button.y >= 232 && button.y <= 264)
      {
        if(pos <=39)
        {
          pos = 39;
        }else
        { 
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.fillRect(pos,2,12,25,WHITE);
         pos-=12;
        }
        if(pos >= 460)
        {
          pos = 380;
          delay(150);
          pinMode(XM,OUTPUT);
          pinMode(YP,OUTPUT);
          tft.fillRect(pos,2,12,25,WHITE);
          pos-=12;
        }
      }else
      if(button.x > 444 && button.x < 500 && button.y >= 232 && button.y <= 264)
      {
        if(pos <= 39)
        {
          pos = 39;
        }else
        {
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.fillRect(pos,2,12,25,WHITE);
         pos-=12;
        }
        if(pos >= 460)
        {
          pos = 380;
          delay(150);
          pinMode(XM,OUTPUT);
          pinMode(YP,OUTPUT);
          tft.fillRect(pos,2,12,25,WHITE);
          pos-=12;
        }
      }
    }
    //ENTER
    if(button.x > 432 && button.x < 500)
    {
      if(button.y > 276 && button.y < 320  && buttonKeyboard)
      {
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.fillCircle(20,50,10,GREEN);
      }else
      if(button.x > 432 && button.x < 500 && button.y > 276 && button.y < 320  && buttonKeyboard)
      {
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.fillCircle(20,50,10,GREEN);
      }
    }
    //COMMA
    if(button.x > 55 && button.x < 95)
    {
      if(button.y > 276 && button.y < 320  && buttonKeyboard)
      {
       pos+=9;
       if(pos >= 425)
       {
        pos = 425;      
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,6);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(" ");
       }else
       {
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,13);
        tft.setTextSize(1);
        tft.setTextColor(BLACK);
        tft.print(symbols[1]);
        comma = true;
       }
      }
    }else
    if(button.x > 55 && button.x < 95 && button.y > 276 && button.y < 320  && buttonKeyboard)
    {
      pos+=9;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);  
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,13);
       tft.setTextSize(1);
       tft.setTextColor(BLACK);
       tft.print(symbols[1]);
       comma = true;
      }
    }
    //SPACE
    if(button.x > 110 && button.x < 363)
    {
      if(button.y > 276 && button.y < 320 && buttonKeyboard)
      {
       pos+=12;
       if(pos >= 425)
       {
        pos = 425;      
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,6);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(" ");
       }else
       {
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,13);
        tft.setTextSize(1);
        tft.setTextColor(BLACK);
        tft.print(symbols[2]);
       }
    }else
    if(button.x > 110 && button.x < 363 && button.y > 276 && button.y < 320 && buttonKeyboard)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,13);
       tft.setTextSize(1);
       tft.setTextColor(BLACK);
       tft.print(symbols[2]);
      }
    }
   // HIDE KEYBOARD
    if(button.y > 40 && button.y < 78 || button.x < -10 && button.y < 35 || button.x > 472 && button.y < 35)
    {
      delay(100);
      close_keyboard = false;
      buttonKeyboard = false;
      symbols_button = false;
      key_board = true;
      pos = 39;
      Hide_Keyboard();  
    }
   }
  }
 }
}

void CAPS_Keyboard()
{
 TSPoint button = ts.getPoint();
  
 if(caps_button == true)
 { 
  if(button.z > ts.pressureThreshhold && caps_button == true);
  {
    button.x = map(button.x, TS_MINX, TS_MAXX , tft.height(),0);
    button.y = map(button.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = button.x;
    button.x = button.y;
    button.y = t;

    //DIGIT 1
    if(button.x < 18)
    {
    if(button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
       pos+=5;
       dot = false;
       comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[0]);
      }
    }
    }else
    if(button.x < 18 && button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
       pos+=5;
       dot = false;
       comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[0]);
      }
    }
    //DIGIT 2
    if(button.x > 29 && button.x < 70)
    {
     if(button.y >= 87 && button.y <= 122 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[1]);
      }
     }
    }else
    if(button.x > 29 && button.x < 70 && button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[1]);
      }
    }
    //DIGIT 3
    if(button.x > 80 && button.x < 121)
    {
    if(button.y >= 87 && button.y <= 122 && caps_button)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[2]);
      }
     }
    }else
    if(button.x > 80 && button.x < 121 && button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[2]);
      }
    }
    //DIGIT 4
    if(button.x > 136 && button.x < 173)
    {
    if(button.y >= 87 && button.y <= 122 && caps_button)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[3]);
      }
     }
    }else
    if(button.x > 136 && button.x < 173 && button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[3]);
      }
    }
    //DIGIT 5
    if(button.x > 185 && button.x < 227)
    {
      if(button.y >= 87 && button.y <= 122 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[4]);
      }
     }
    }else
    if(button.x > 185 && button.x < 227 && button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[4]);
      }
    }
    //DIGIT 6
    if(button.x > 240 && button.x < 285)
    {
      if(button.y >= 87 && button.y <= 122 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[5]);
      }
     }
    }else
    if(button.x > 240 && button.x < 285 && button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[5]);
      }
    }
    //DIGIT 7
    if(button.x > 296 && button.x < 333)
    {
    if(button.y >= 87 && button.y <= 122 && caps_button)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[6]);
      }
     }
    }else
    if(button.x > 296 && button.x < 333 && button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[6]);
      }
    }
    //DIGIT 8
    if(button.x > 353 && button.x < 393)
    {
      if(button.y >= 87 && button.y <= 122 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[7]);
      }
     }
    }else
    if(button.x > 353 && button.x < 393 && button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[7]);
      }
    }
    //DIGIT 9
    if(button.x > 407 && button.x < 447)
    {
      if(button.y >= 87 && button.y <= 122 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[8]);
      }
     }
    }else
    if(button.x > 407 && button.x < 447 && button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[8]);
      }
    }
    //DIGIT 0
    if(button.x > 460 && button.x < 500)
    {
      if(button.y >= 87 && button.y <= 122 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[9]);
      }
     }
    }else
    if(button.x > 460 && button.x < 500 && button.y >= 87 && button.y <= 122 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[9]);
      }
     }
     //Q letter
    if(button.x < 18)
    {
    if(button.y >= 135 && button.y <= 168 && caps_button)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setRotation(1);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[16]);
      }
    }
    }else
    if(button.x < 18 && button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setRotation(1);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[16]);
      }
    }
    //W letter
    if(button.x > 29 && button.x < 70)
    {
     if(button.y >= 135 && button.y <= 168 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[22]);
      }
     }
    }else
    if(button.x > 29 && button.x < 70 && button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[22]);
      }
    }
    //E letter
    if(button.x > 80 && button.x < 121)
    {
     if(button.y >= 135 && button.y <= 168 && caps_button)
     { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[4]);
      }
     }
    }else
    if(button.x > 80 && button.x < 121 && button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[4]);
      }
    }
    //R letter
    if(button.x > 136 && button.x < 173)
    {
     if(button.y >= 135 && button.y <= 168 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[17]);
      }
     }
    }else
    if(button.x > 136 && button.x < 173 && button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[17]);
      }
    }
    //T letter
    if(button.x > 185 && button.x < 227)
    {
     if(button.y >= 135 && button.y <= 168 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[19]);
      }
     }
    }else
    if(button.x > 185 && button.x < 227 && button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[19]);
      }
    }
    //Y letter
    if(button.x > 240 && button.x < 285)
    {
    if(button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[24]);
      }
    }
    }else
    if(button.x > 240 && button.x < 285 && button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[24]);
      }
    }
    //U letter
    if(button.x > 296 && button.x < 333)
    {
     if(button.y >= 135 && button.y <= 168 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      } 
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[20]);
      }
     }
    }else
    if(button.x > 296 && button.x < 333 && button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[20]);
      }
    }
    //I letter
    if(button.x > 353 && button.x < 393)
    {
    if(button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[8]);
      }
    }
    }else
    if(button.x > 353 && button.x < 393 && button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[8]);
      }
    }
    //O letter
    if(button.x > 407 && button.x < 447)
    {
    if(button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[14]);
      }
    }
    }else
    if(button.x > 407 && button.x < 447 && button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[14]);
      }
    }
    //P letter
    if(button.x > 460 && button.x < 500)
    {
    if(button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[15]);
      }
    }
    }else
    if(button.x > 460 && button.x < 500 && button.y >= 135 && button.y <= 168 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[15]);
      }
    } 
    //A letter
    if(button.x > 1 && button.x < 41)
    {
    if(button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[0]);
      }
    }
    }else
    if(button.x > -5 && button.x < 18 && button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[0]);
      }
    }
    //S letter
    if(button.x > 54 && button.x < 95)
    {
    if(button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[18]);
      }
    }
    }else
    if(button.x > 54 && button.x < 95 && button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[18]);
      }
    }
    //D letter
    if(button.x > 107 && button.x < 149)
    {
    if(button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[3]);
      }
    }
    }else
    if(button.x > 107 && button.x < 149 && button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[3]);
      }
    }
    //F letter
    if(button.x > 160 && button.x < 200)
    {
      if(button.y >= 183 && button.y <= 215 && caps_button)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[5]);
      }
    }
    }else
    if(button.x > 160 && button.x < 200 && button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[5]);
      }
    }
    //G letter
    if(button.x > 212 && button.x < 252)
    {
    if(button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[6]);
      }
    }
    }else
    if(button.x > 212 && button.x < 252 && button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[6]);
      }
    }
    //H letter
    if(button.x > 268 && button.x < 311)
    {
    if(button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[7]);
      }
    }
    }else
    if(button.x > 268 && button.x < 311 && button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[7]);
      }
    }
    //J letter
    if(button.x > 322 && button.x < 363)
    {
    if(button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[9]);
      }
    }
    }else
    if(button.x > 322 && button.x < 363 && button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[9]);
      }
    }
    //K letter
    if(button.x > 377 && button.x < 417)
    {
    if(button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[10]);
      }
    }
    }else
    if(button.x > 377 && button.x < 417 && button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[10]);
      }
    }
    //L letter
    if(button.x > 435 && button.x < 475)
    {
    if(button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[11]);
      }
    }
    }else
    if(button.x > 435 && button.x < 475 && button.y >= 183 && button.y <= 215 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[11]);
      }
    }
    //Z letter
    if(button.x > 55 && button.x < 95)
    {
    if(button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[25]);
      }
    }
    }else
    if(button.x > 55 && button.x < 95 && button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[25]);
      }
    }
    //X letter
    if(button.x > 106 && button.x < 146)
    {
    if(button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[23]);
      }
    }
    }else
    if(button.x > 106 && button.x < 146 && button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[23]);
      }
    }
    //C letter
    if(button.x > 160 && button.x < 200)
    {
    if(button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[2]);
      }
    }
    }else
    if(button.x > 160 && button.x < 200 && button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[2]);
      }
    }
    //V letter
    if(button.x > 213 && button.x < 253)
    {
    if(button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[21]);
      }
    }
    }else
    if(button.x > 213 && button.x < 253 && button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[21]);
      }
    }
    //B letter
    if(button.x > 271 && button.x < 311)
    {
    if(button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[1]);
      }
    }
    }else
    if(button.x > 271 && button.x < 311 && button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[1]);
      }
    }
    //N letter
    if(button.x > 321 && button.x < 362)
    {
    if(button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[13]);
      }
    }
    }else
    if(button.x > 321 && button.x < 362 && button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[13]);
      }
    }
    //M letter
    if(button.x > 378 && button.x < 418)
    {
    if(button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[12]);
      }
    }
    }else
    if(button.x > 378 && button.x < 418 && button.y >= 232 && button.y <= 264 && caps_button)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(CAPS_letters[12]);
      }
    }
    // HIDE KEYBOARD
    if(button.y > 40 && button.y < 78 || button.x < -10 && button.y < 35 || button.x > 472 && button.y < 35)
    {
      delay(100);
      close_keyboard = false;
      buttonKeyboard = false;
      caps_button = false;
      key_board = true;
      pos = 39;
      Hide_Keyboard();  
    }
    //DOT
    if(button.x > 378 && button.x < 418)
    {
      if(button.y > 276 && button.y < 320  && caps_button)
      {
       delay(150);
       pos+=9;
       if(pos >= 425)
       {
        pos = 425;      
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,6);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(" ");
       }else
       {
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,13);
        tft.setTextSize(1);
        tft.setTextColor(BLACK);
        tft.print(symbols[0]);
        dot = true;
       }
      }else
      if(button.x > 378 && button.x < 418 && button.y > 276 && button.y < 320  && caps_button)
      {
        delay(150);
        pos+=9;
        if(pos >= 425)
        {
         pos = 425;      
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.setCursor(pos,6);
         tft.setTextSize(2);
         tft.setTextColor(WHITE);
         tft.print(" ");
        }else
        {
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.setCursor(pos,13);
         tft.setTextSize(1);
         tft.setTextColor(BLACK);
         tft.print(symbols[0]);
         dot = true;
        }
      }
    }
    //BACKSPACE
    if(button.x > 444 && button.x < 500)
    {
      if(button.y >= 232 && button.y <= 264)
      {
       if(pos <=39)
        {
          pos = 39;
        }else
        { 
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.fillRect(pos,2,12,25,WHITE);
         pos-=12;
        }
        if(pos >= 460)
        {
          pos = 380;
          delay(150);
          pinMode(XM,OUTPUT);
          pinMode(YP,OUTPUT);
          tft.fillRect(pos,2,12,25,WHITE);
          pos-=12;
        }
      }else
      if(button.x > 444 && button.x < 500 && button.y >= 232 && button.y <= 264)
      {
        if(pos <= 39)
        {
          pos = 39;
        }else
        {
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.fillRect(pos,2,12,25,WHITE);
        pos-=12;
        }
        if(pos >= 460)
        {
          pos = 380;
          delay(150);
          pinMode(XM,OUTPUT);
          pinMode(YP,OUTPUT);
          tft.fillRect(pos,2,12,25,WHITE);
          pos-=12;
        }
      }
    }
    //ENTER
    if(button.x > 432 && button.x < 500)
    {
      if(button.y > 276 && button.y < 320 && caps_button)
      {
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.fillCircle(20,50,10,GREEN);
      }else
      if(button.x > 432 && button.x < 500 && button.y > 276 && button.y < 320 && caps_button)
      {
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.fillCircle(20,50,10,GREEN);
      }
    }
    //COMMA
    if(button.x > 55 && button.x < 95)
    {
      if(button.y > 276 && button.y < 320  && caps_button)
      {
        pos+=9;
        if(pos >= 425)
        {
         pos = 425;      
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.setCursor(pos,6);
         tft.setTextSize(2);
         tft.setTextColor(WHITE);
         tft.print(" ");
        }else
        {
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.setCursor(pos,13);
         tft.setTextSize(1);
         tft.setTextColor(BLACK);
         tft.print(symbols[1]);
         comma = true;
        }
      }
    }else
    if(button.x > 55 && button.x < 95 && button.y > 276 && button.y < 320  && caps_button)
    {
      pos+=9;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);  
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,13);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(symbols[1]);
      comma = true;
      }
    }
    //SPACE
    if(button.x > 110 && button.x < 363)
    {
      if(button.y > 276 && button.y < 320  && caps_button)
      {
        pos+=12;
        if(pos >= 425)
        {
         pos = 425;      
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.setCursor(pos,6);
         tft.setTextSize(2);
         tft.setTextColor(WHITE);
         tft.print(" ");
         }else
         {
          delay(150);
          pinMode(XM,OUTPUT);
          pinMode(YP,OUTPUT);
          tft.setCursor(pos,13);
          tft.setTextSize(1);
          tft.setTextColor(BLACK);
          tft.print(symbols[2]);
         }
      }
    }else
    if(button.x > 110 && button.x < 363 && button.y > 276 && button.y < 320 && caps_button)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,13);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(symbols[2]);
      }
    }
    //SPECIAL SYMBOLS
    if(button.x < 45)
    {
      if(button.y > 276 && button.y < 320 && caps_button)
      {
        delay(50);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        symbols_button = true;
        Additional_Symbols();
      }
    }else
    if(button.x < 45 && button.y > 276 && button.y < 320 && caps_button)
    {
      delay(50);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      symbols_button = true;
      Additional_Symbols();
    }
    //CAPS BUTTON (RETURN TO SMALL LETTERS)
    if(button.x < 35)
    {
      if(button.y >= 232 && button.y <= 264)
      {
        delay(150);
        count_caps++;
        if(count_caps % 2 == 0)
        {
         caps_button = false;
         tft.fillRect(0,27,480,320,BLACK);
         Safe_Search_Bar();
        }
      }
    }else
    if(button.x < 35 && button.y >= 232 && button.y <= 264)
    {
      delay(150);
      count_caps++;
      if(count_caps % 2 == 0)
      {
       caps_button = false;
       tft.fillRect(0,27,480,320,BLACK);
       Safe_Search_Bar();
      }
    }
    while(symbols_button == true)
    {
      Symbol_Keyboard();
    }
   }
 }
}

void loop()
{
  TSPoint show_kb = ts.getPoint();
  TSPoint button = ts.getPoint();
  TSPoint cl_kb = ts.getPoint();
  if(show_kb.z > ts.pressureThreshhold && key_board == true)
  {
    show_kb.x = map(show_kb.x, TS_MINX, TS_MAXX , tft.height(),0);
    show_kb.y = map(show_kb.y, TS_MAXY, TS_MINY,0, tft.width());
    int t = show_kb.x;
    show_kb.x = show_kb.y;
    show_kb.y = t;
    if(show_kb.x > -10 && show_kb.x < 472)
    {
      if(show_kb.y > 12 && show_kb.y < 33)
      {
        delay(100);
        Keyboard_Activated();
        buttonKeyboard = true;
        close_keyboard = true;
        key_board = false;
      }
    }else
    if(show_kb.x > -10 && show_kb.x < 472 && show_kb.y > 12 && show_kb.y < 33)
    {
      delay(100);
      Keyboard_Activated();
      buttonKeyboard = true;
      close_keyboard = true;
      key_board = false;
    }
  }
  
 if(buttonKeyboard == true)
 { 
  //Cursor();
  if(button.z > ts.pressureThreshhold && buttonKeyboard == true);
  {
    button.x = map(button.x, TS_MINX, TS_MAXX , tft.height(),0);
    button.y = map(button.y, TS_MAXY, TS_MINY, 0,tft.width());
    int t = button.x;
    button.x = button.y;
    button.y = t;

    //DIGIT 1
    if(button.x < 18)
    {
    if(button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
       pos+=5;
       dot = false;
       comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[0]);
      }
    }
    }else
    if(button.x < 18 && button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
       pos+=5;
       dot = false;
       comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[0]);
      }
    }
    //DIGIT 2
    if(button.x > 29 && button.x < 70)
    {
     if(button.y >= 87 && button.y <= 122 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[1]);
      }
     }
    }else
    if(button.x > 29 && button.x < 70 && button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(BLACK);
       tft.print(numbers[1]);
      }
    }
    //DIGIT 3
    if(button.x > 80 && button.x < 121)
    {
    if(button.y >= 87 && button.y <= 122 && buttonKeyboard)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[2]);
      }
     }
    }else
    if(button.x > 80 && button.x < 121 && button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[2]);
      }
    }
    //DIGIT 4
    if(button.x > 136 && button.x < 173)
    {
    if(button.y >= 87 && button.y <= 122 && buttonKeyboard)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[3]);
      }
     }
    }else
    if(button.x > 136 && button.x < 173 && button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[3]);
      }
    }
    //DIGIT 5
    if(button.x > 185 && button.x < 227)
    {
      if(button.y >= 87 && button.y <= 122 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[4]);
      }
     }
    }else
    if(button.x > 185 && button.x < 227 && button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[4]);
      }
    }
    //DIGIT 6
    if(button.x > 240 && button.x < 285)
    {
      if(button.y >= 87 && button.y <= 122 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[5]);
      }
     }
    }else
    if(button.x > 240 && button.x < 285 && button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[5]);
      }
    }
    //DIGIT 7
    if(button.x > 296 && button.x < 333)
    {
    if(button.y >= 87 && button.y <= 122 && buttonKeyboard)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[6]);
      }
     }
    }else
    if(button.x > 296 && button.x < 333 && button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[6]);
      }
    }
    //DIGIT 8
    if(button.x > 353 && button.x < 393)
    {
      if(button.y >= 87 && button.y <= 122 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[7]);
      }
     }
    }else
    if(button.x > 353 && button.x < 393 && button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[7]);
      }
    }
    //DIGIT 9
    if(button.x > 407 && button.x < 447)
    {
      if(button.y >= 87 && button.y <= 122 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[8]);
      }
     }
    }else
    if(button.x > 407 && button.x < 447 && button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[8]);
      }
    }
    //DIGIT 0
    if(button.x > 460 && button.x < 500)
    {
      if(button.y >= 87 && button.y <= 122 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[9]);
      }
     }
    }else
    if(button.x > 460 && button.x < 500 && button.y >= 87 && button.y <= 122 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(numbers[9]);
      }
    }

    
    //Q letter
    if(button.x < 18)
    {
    if(button.y >= 135 && button.y <= 168 && buttonKeyboard)
    { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setRotation(1);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[16]);
      }
    }
    }else
    if(button.x < 18 && button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setRotation(1);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[16]);
      }
    }
    //W letter
    if(button.x > 29 && button.x < 70)
    {
     if(button.y >= 135 && button.y <= 168 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[22]);
      }
     }
    }else
    if(button.x > 29 && button.x < 70 && button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[22]);
      }
    }
    //E letter
    if(button.x > 80 && button.x < 121)
    {
     if(button.y >= 135 && button.y <= 168 && buttonKeyboard)
     { 
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[4]);
      }
     }
    }else
    if(button.x > 80 && button.x < 121 && button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[4]);
      }
    }
    //R letter
    if(button.x > 136 && button.x < 173)
    {
     if(button.y >= 135 && button.y <= 168 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[17]);
      }
     }
    }else
    if(button.x > 136 && button.x < 173 && button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[17]);
      }
    }
    //T letter
    if(button.x > 185 && button.x < 227)
    {
     if(button.y >= 135 && button.y <= 168 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      { 
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[19]);
      }
     }
    }else
    if(button.x > 185 && button.x < 227 && button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[19]);
      }
    }
    //Y letter
    if(button.x > 240 && button.x < 285)
    {
    if(button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[24]);
      }
    }
    }else
    if(button.x > 240 && button.x < 285 && button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[24]);
      }
    }
    //U letter
    if(button.x > 296 && button.x < 333)
    {
     if(button.y >= 135 && button.y <= 168 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      } 
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[20]);
      }
     }
    }else
    if(button.x > 296 && button.x < 333 && button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[20]);
      }
    }
    //I letter
    if(button.x > 353 && button.x < 393)
    {
    if(button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[8]);
      }
    }
    }else
    if(button.x > 353 && button.x < 393 && button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[8]);
      }
    }
    //O letter
    if(button.x > 407 && button.x < 447)
    {
    if(button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[14]);
      }
    }
    }else
    if(button.x > 407 && button.x < 447 && button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[14]);
      }
    }
    //P letter
    if(button.x > 460 && button.x < 500)
    {
    if(button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[15]);
      }
    }
    }else
    if(button.x > 460 && button.x < 500 && button.y >= 135 && button.y <= 168 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[15]);
      }
    } 
    //A letter
    if(button.x > 1 && button.x < 41)
    {
    if(button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[0]);
      }
    }
    }else
    if(button.x > -5 && button.x < 18 && button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[0]);
      }
    }
    //S letter
    if(button.x > 54 && button.x < 95)
    {
    if(button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[18]);
      }
    }
    }else
    if(button.x > 54 && button.x < 95 && button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[18]);
      }
    }
    //D letter
    if(button.x > 107 && button.x < 149)
    {
    if(button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[3]);
      }
    }
    }else
    if(button.x > 107 && button.x < 149 && button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[3]);
      }
    }
    //F letter
    if(button.x > 160 && button.x < 200)
    {
      if(button.y >= 183 && button.y <= 215 && buttonKeyboard)
     {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[5]);
      }
    }
    }else
    if(button.x > 160 && button.x < 200 && button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[5]);
      }
    }
    //G letter
    if(button.x > 212 && button.x < 252)
    {
    if(button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[6]);
      }
    }
    }else
    if(button.x > 212 && button.x < 252 && button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[6]);
      }
    }
    //H letter
    if(button.x > 268 && button.x < 311)
    {
    if(button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[7]);
      }
    }
    }else
    if(button.x > 268 && button.x < 311 && button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[7]);
      }
    }
    //J letter
    if(button.x > 322 && button.x < 363)
    {
    if(button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[9]);
      }
    }
    }else
    if(button.x > 322 && button.x < 363 && button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[9]);
      }
    }
    //K letter
    if(button.x > 377 && button.x < 417)
    {
    if(button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[10]);
      }
    }
    }else
    if(button.x > 377 && button.x < 417 && button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[10]);
      }
    }
    //L letter
    if(button.x > 435 && button.x < 475)
    {
    if(button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[11]);
      }
    }
    }else
    if(button.x > 435 && button.x < 475 && button.y >= 183 && button.y <= 215 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[11]);
      }
    }
    //Z letter
    if(button.x > 55 && button.x < 95)
    {
    if(button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[25]);
      }
    }
    }else
    if(button.x > 55 && button.x < 95 && button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[25]);
      }
    }
    //X letter
    if(button.x > 106 && button.x < 146)
    {
    if(button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[23]);
      }
    }
    }else
    if(button.x > 106 && button.x < 146 && button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[23]);
      }
    }
    //C letter
    if(button.x > 160 && button.x < 200)
    {
    if(button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[2]);
      }
    }
    }else
    if(button.x > 160 && button.x < 200 && button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[2]);
      }
    }
    //V letter
    if(button.x > 213 && button.x < 253)
    {
    if(button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[21]);
      }
    }
    }else
    if(button.x > 213 && button.x < 253 && button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[21]);
      }
    }
    //B letter
    if(button.x > 271 && button.x < 311)
    {
    if(button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[1]);
      }
    }
    }else
    if(button.x > 271 && button.x < 311 && button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[1]);
      }
    }
    //N letter
    if(button.x > 321 && button.x < 362)
    {
    if(button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[13]);
      }
    }
    }else
    if(button.x > 321 && button.x < 362 && button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[13]);
      }
    }
    //M letter
    if(button.x > 378 && button.x < 418)
    {
    if(button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[12]);
      }
    }
    }else
    if(button.x > 378 && button.x < 418 && button.y >= 232 && button.y <= 264 && buttonKeyboard)
    {
      if(dot == true || comma == true)
      {
        pos+=5;
        dot = false;
        comma = false;
      }else
      {
        pos+=12;
      }
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,6);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(alphabet[12]);
      }
    }
    // HIDE KEYBOARD
    if(button.y > 40 && button.y < 78 || button.x < -10 && button.y < 35 || button.x > 472 && button.y < 35)
    {
      delay(100);
      close_keyboard = false;
      buttonKeyboard = false;
      key_board = true;
      pos = 39;
      Hide_Keyboard();  
    }
    //DOT
    if(button.x > 378 && button.x < 418)
    {
      if(button.y > 276 && button.y < 320  && buttonKeyboard)
      {
       delay(150);
       pos+=9;
       if(pos >= 425)
       {
        pos = 425;      
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,6);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(" ");
       }else
       {
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.setCursor(pos,13);
        tft.setTextSize(1);
        tft.setTextColor(BLACK);
        tft.print(symbols[0]);
        dot = true;
       }
      }else
      if(button.x > 378 && button.x < 418 && button.y > 276 && button.y < 320  && buttonKeyboard)
      {
        delay(150);
        pos+=9;
        if(pos >= 425)
        {
         pos = 425;      
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.setCursor(pos,6);
         tft.setTextSize(2);
         tft.setTextColor(WHITE);
         tft.print(" ");
        }else
        {
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.setCursor(pos,13);
         tft.setTextSize(1);
         tft.setTextColor(BLACK);
         tft.print(symbols[0]);
         dot = true;
        }
      }
    }
    //BACKSPACE
    if(button.x > 444 && button.x < 500)
    {
      if(button.y >= 232 && button.y <= 264)
      {
       if(pos <=39)
        {
          pos = 39;
        }else
        { 
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.fillRect(pos,2,12,25,WHITE);
         pos-=12;
        }
        if(pos >= 460)
        {
          pos = 380;
          delay(150);
          pinMode(XM,OUTPUT);
          pinMode(YP,OUTPUT);
          tft.fillRect(pos,2,12,25,WHITE);
          pos-=12;
        }
      }else
      if(button.x > 444 && button.x < 500 && button.y >= 232 && button.y <= 264)
      {
        if(pos <= 39)
        {
          pos = 39;
        }else
        {
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.fillRect(pos,2,12,25,WHITE);
        pos-=12;
        }
        if(pos >= 460)
        {
          pos = 380;
          delay(150);
          pinMode(XM,OUTPUT);
          pinMode(YP,OUTPUT);
          tft.fillRect(pos,2,12,25,WHITE);
          pos-=12;
        }
      }
    }
    //ENTER
    if(button.x > 432 && button.x < 500)
    {
      if(button.y > 276 && button.y < 320 && buttonKeyboard)
      {
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.fillCircle(20,50,10,GREEN);
      }else
      if(button.x > 432 && button.x < 500 && button.y > 276 && button.y < 320 && buttonKeyboard)
      {
        delay(150);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        tft.fillCircle(20,50,10,GREEN);
      }
    }
    //COMMA
    if(button.x > 55 && button.x < 95)
    {
      if(button.y > 276 && button.y < 320  && buttonKeyboard)
      {
        pos+=9;
        if(pos >= 425)
        {
         pos = 425;      
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.setCursor(pos,6);
         tft.setTextSize(2);
         tft.setTextColor(WHITE);
         tft.print(" ");
        }else
        {
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.setCursor(pos,13);
         tft.setTextSize(1);
         tft.setTextColor(BLACK);
         tft.print(symbols[1]);
         comma = true;
        }
      }
    }else
    if(button.x > 55 && button.x < 95 && button.y > 276 && button.y < 320  && buttonKeyboard)
    {
      pos+=9;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);  
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,13);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(symbols[1]);
      comma = true;
      }
    }
    //SPACE
    if(button.x > 110 && button.x < 363)
    {
      if(button.y > 276 && button.y < 320  && buttonKeyboard)
      {
        pos+=12;
        if(pos >= 425)
        {
         pos = 425;      
         delay(150);
         pinMode(XM,OUTPUT);
         pinMode(YP,OUTPUT);
         tft.setCursor(pos,6);
         tft.setTextSize(2);
         tft.setTextColor(WHITE);
         tft.print(" ");
         }else
         {
          delay(150);
          pinMode(XM,OUTPUT);
          pinMode(YP,OUTPUT);
          tft.setCursor(pos,13);
          tft.setTextSize(1);
          tft.setTextColor(BLACK);
          tft.print(symbols[2]);
         }
      }
    }else
    if(button.x > 110 && button.x < 363 && button.y > 276 && button.y < 320 && buttonKeyboard)
    {
      pos+=12;
      if(pos >= 425)
      {
       pos = 425;      
       delay(150);
       pinMode(XM,OUTPUT);
       pinMode(YP,OUTPUT);
       tft.setCursor(pos,6);
       tft.setTextSize(2);
       tft.setTextColor(WHITE);
       tft.print(" ");
      }else
      {
      delay(150);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      tft.setCursor(pos,13);
      tft.setTextSize(1);
      tft.setTextColor(BLACK);
      tft.print(symbols[2]);
      }
    }
    //SPECIAL SYMBOLS
    if(button.x < 45)
    {
      if(button.y > 276 && button.y < 320 && buttonKeyboard)
      {
        delay(50);
        pinMode(XM,OUTPUT);
        pinMode(YP,OUTPUT);
        symbols_button = true;
        Additional_Symbols();
      }
    }else
    if(button.x < 45 && button.y > 276 && button.y < 320 && buttonKeyboard)
    {
      delay(50);
      pinMode(XM,OUTPUT);
      pinMode(YP,OUTPUT);
      symbols_button = true;
      Additional_Symbols();
    }
    //CAPS BUTTON
    if(button.x < 35)
    {
      if(button.y >= 232 && button.y <= 264)
      {
        delay(150);
        count_caps++;
        if(count_caps % 2 != 0)
        {
         caps_button = true;
         count_caps = 1;
         CAPS_Keyboard_Activated();
         tft.fillTriangle(12,243,29,225,46,243,BLUE);
         tft.fillRect(24,243,12,17,BLUE);
        }else
        {
         Keyboard_Activated();
         tft.fillTriangle(12,243,29,225,46,243,BLACK);
         tft.fillRect(24,243,12,17,BLACK);
        }
      }
    }else
    if(button.x < 35 && button.y >= 232 && button.y <= 264)
    {
      delay(150);
      count_caps++;
      if(count_caps % 2 != 0)
      {
       caps_button = true;
       count_caps = 1;
       CAPS_Keyboard_Activated();
       tft.fillTriangle(12,243,29,225,46,243,BLUE);
       tft.fillRect(24,243,12,17,BLUE);
      }else
      {
       Keyboard_Activated();
       tft.fillTriangle(12,243,29,225,46,243,BLACK);
       tft.fillRect(24,243,12,17,BLACK);
      }
    }
    while(symbols_button == true)
    {
      Symbol_Keyboard();
    }
    while(caps_button == true)
    {
      CAPS_Keyboard();
    }
  }  
 }
}
