#include <LedControlMS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define NBR_MTX 1 
#define LIFE 8

byte Hang_man[] = 
{
  B00011000,
  B00111100,
  B00011000,
  B11111111,
  B00011000,
  B00011000,
  B00100100,
  B01000010
};

String quiz[] = {"CLEAR","BOX","DUST"};

LedControl lc = LedControl(4,3,2,NBR_MTX);
LiquidCrystal_I2C lcd(0x27,16,2);

const int led_G =11, led_R = 10;
const int tact = 8;
const int buzz = 9;
const int alphabet = A3;
int wrong = 0;
int correct = 0;
int used_alphabet[26] = {0,};
int choose_word = 0;
int start = 0;

void setup() {
  Serial.begin(9600);  
  randomSeed(analogRead(0));
  choose_word = random(0,4);

  // put your setup code here, to run once:
  for(int i =0; i<NBR_MTX; i++)
  {
      lc.shutdown(i,false);
      lc.setIntensity(i,8);
      lc.clearDisplay(i);  

      delay(100);
  }

  lcd.init();
  lcd.clear();
  lcd.backlight();

  pinMode(led_G,OUTPUT);
  pinMode(led_R,OUTPUT);
  pinMode(tact,INPUT_PULLUP);
  pinMode(buzz,OUTPUT);

}

void loop() {
  
  String quiz_word =  quiz[choose_word];
  int alphabet_choose = 0;
  int quiz_word_length = quiz_word.length();

  int abcValue = analogRead(alphabet);
  int alphabet_num = map(abcValue,0,1023,65,90);

  Serial.print(digitalRead(buzz));
  Serial.print(" ");
  Serial.print(alphabet_num);
  Serial.print(" ");
  Serial.println(abcValue);

  if(start == 0)
  {
   display_print(alphabet_num, quiz_word_length);  
   start = 1;
  }

  
  lcd.setCursor(15,1);
  lcd.print(LIFE - wrong);

  lcd.setCursor(0,1); 
  if(alphabet_num > 65)
    lcd.write(alphabet_num-1);
  else
    lcd.print(" ");

  lcd.setCursor(3,1);
  lcd.write(alphabet_num);

  lcd.setCursor(6,1);
  if(alphabet_num < 90)
    lcd.write(alphabet_num+1);
  else
    lcd.print(" ");

  
  if(digitalRead(tact) == LOW)
  {
    alphabet_choose = 1; 
    delay(500);
  }

  if(alphabet_choose == 1)
  {
      game_control(quiz_word, alphabet_num , quiz_word_length);
      draw_matrix();
  }
  if(check_word(quiz_word))
  {
    lcd.clear();
    lcd.setCursor(4,0); 
    lcd.print("You Win!");
    delay(1000);
    reset_game();
  }

  if(wrong == LIFE)
  {
    lcd.clear();
    lcd.setCursor(3,0); 
    lcd.print("Game Over!");
    delay(1000);
    reset_game();
  }
}

void display_print(int alphabet_num, int quiz_word_length)
{
  lcd.setCursor(2,1);
  lcd.print("[");
  lcd.setCursor(4,1);
  lcd.print("]");
  
  lcd.setCursor(0,0);
  lcd.print("what is : ");

  for(int i =0; i < quiz_word_length; i++)
  {
    lcd.setCursor(10+i,0);
    lcd.print("_");  
  }

  lcd.setCursor(9,1);
  lcd.print("LIFE: ");
}

void game_control(String quiz_word, int alphabet_num ,int quiz_word_length)
{
  int How = 0;
  
  if(used_alphabet[alphabet_num - 65] != 1)
  {
    for(int i = 0; i < quiz_word_length; i++)
    {
      if(quiz_word[i] == alphabet_num)
      {
        used_alphabet[alphabet_num-65] = 1;
        lcd.setCursor(10+i,0);
        lcd.write(alphabet_num);

        tone(buzz,523,100);
        delay(200);
        tone(buzz,587,200);
        delay(200);
        tone(buzz,659,200);
        digitalWrite(led_G, HIGH);
        delay(500);
        digitalWrite(led_G,LOW);
        correct ++;
        How = 1;
      } 
    }
    
    if(How == 0)
    {
      used_alphabet[alphabet_num-65] = 1;
      tone(buzz,659,200);
      delay(200);
      tone(buzz,659);
      delay(200);
      noTone(buzz);
      digitalWrite(led_R, HIGH);
      delay(500);
      digitalWrite(led_R,LOW);
      wrong++; 
    } 
  }
}

bool check_word(String quiz_word)
{
    if(quiz_word.length() == correct)
      return true;
    else
      return false;
}


void draw_matrix()
{
  if(wrong > 0)
  {
    for(int i = 0; i <= wrong -1; i++)
      lc.setRow(0,i,Hang_man[i]);   
  }
}

void reset_game()
{
  choose_word = random(0,4);
  correct = 0;
  wrong = 0; 
  for(int i = 0; i < 26; i++)
    used_alphabet[i] = 0;

  for(int i =0; i<NBR_MTX; i++)
  {
      lc.shutdown(i,false);
      lc.setIntensity(i,8);
      lc.clearDisplay(i);  

      delay(100);
  }

  start = 0;
}
