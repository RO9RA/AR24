#include <LedControlMS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define NBR_MTX 1
#define LIFE 8
LedControl lc = LedControl(4,3,2,NBR_MTX);
const int tact1 = 8, potent = A3, ledpin = 11, ledpin2 =10 , buzz = 9;
int ran, al =0, j = 0, al2 =0, start = 0, life = 0, word_chose;
int what=0, used = 0, count = 0, count_cpy =0;

String Word[3] = {"BOX", "DUST","MATRIX"};
int used2[26]={0};

byte hang_man[] =
{
  B00011000,
  B00111100,
  B00011000,
  B01111110,
  B00011000,
  B00011000,
  B00100100,
  B01000010
};

void Hang_man(int life)
{
  for(int i = 0; i<life; i++)
    lc.setRow(0,i,hang_man[i]);  
}

void setup() {
  randomSeed ( analogRead ( 0 ) );
  // put your setup code here, to run once:
  pinMode(ledpin,OUTPUT);
  pinMode(ledpin2,OUTPUT);
  pinMode(tact1, INPUT_PULLUP);// tact 1
  pinMode(buzz,OUTPUT);
  lcd.init();
  lcd.clear();
  lcd.backlight();

  for(int i =0; i<NBR_MTX; i++)
  {
      lc.shutdown(i,false);
      lc.setIntensity(i,8);
      lc.clearDisplay(i);
      
      delay(100);
  }
  lc.clearAll();
}

void loop() 
{
  al = analogRead(potent);
  al2 = map(al,0,1010,65,90);
  if(al2-1>=65)
  {
    lcd.setCursor(0,1);
    lcd.write(al2-1);  
  }
  else
  {
   lcd.setCursor(0,1);
   lcd.print(" ");  
  }
  lcd.setCursor(2,1);
  lcd.write(91);
  lcd.setCursor(3,1);
  lcd.write(al2);
  if(al2+1<=90)
  {
    lcd.setCursor(6,1);
    lcd.write(al2+1);  
  }
  else
  {
   lcd.setCursor(6,1);
   lcd.print(" ");  
  }
  lcd.setCursor(4,1);
  lcd.write(93);
  lcd. setCursor(9,1);
  lcd.print("LIFE: ");
  lcd.setCursor(15,1);
  lcd.print(LIFE - life);
  
  if(digitalRead(tact1) == LOW)
  {
      used = al2;
      if(used2[used-65] != 1)
      {
        count_cpy = count;
        for(int i = 0; i<Word[word_chose].length(); i++)
        {
          if(Word[word_chose][i] == used)//Green led 제어 입력.
          {
           tone(buzz,523,300);
           delay(500);
           tone(buzz,587,300);
           delay(500);
           tone(buzz,659,300);
           delay(300);
           analogWrite(ledpin,250);
           for(int i =250; i>=0; i-=5)
           {
            analogWrite(ledpin,i);
            delay(10);
           }
           used2[used-65] = 1;
           lcd.setCursor(3,1);
           lcd.print("o");
           delay(1000);
           lcd.setCursor(3,1);
           lcd.print(" ");
           lcd.setCursor(10+i,0);
           lcd.write(used);
           
           count++;
          }  
        }  
        if(count == count_cpy)//Red led 제어 입력.
        {
          life++;
          tone(buzz,454,300);
          delay(500);
          analogWrite(ledpin2,250);
          for(int i = 250; i>=0; i-=5)
          {
            analogWrite(ledpin2,i);
            delay(10);
          }
          lcd.setCursor(3,1);
          lcd.print("x");
          delay(1000);
          lcd.setCursor(8,1);
          lcd.print("  "); 
          Hang_man(life);
        }
      }
      else
      {
        lcd.setCursor(3,1);
        lcd.print("x");  
        delay(1000);
        lcd.setCursor(8,1);
        lcd.print(" ");          
      }
      if(LIFE - life == 0)
      {
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Game Over");
        start = 0;
        delay(5000);  
      }
      if(count == Word[word_chose].length())
      {
        lcd.clear();
        lcd.setCursor(3,1);
        lcd.print("you Win");
        for(int i =0; i<Word[word_chose].length(); i++)//문자 확인 함수 로 변경 .
        {
         lcd.setCursor(0+i,0);    
         lcd.print(Word[word_chose][i]);     
        }  
        lcd.setCursor(7,0);
        lcd.print("complete");
        start = 0;
        delay(5000);   
      }
  }

  if(start == 0)
  {
    word_chose = random(3);
    count = 0;
    life = 0;
    lc.clearAll();
    for(int i =0; i<26; i++)
       used2[i]=0;
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("what is : ");
    for(int i =0; i<Word[word_chose].length(); i++)//문자 확인 함수 로 변경 .
    {  
      lcd.setCursor(10+i,0);
      lcd.print("_");    
    }  

    start = 1;
  } 
}
