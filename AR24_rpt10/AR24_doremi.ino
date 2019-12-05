int buzzerPin = 9;
const int tact1 = 7,tact2 = 6,tact3 = 5, tact4 = 4, tact5 = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, OUTPUT);
  pinMode(tact1,INPUT_PULLUP);
  pinMode(tact2,INPUT_PULLUP);
  pinMode(tact3,INPUT_PULLUP);
  pinMode(tact4,INPUT_PULLUP);
  pinMode(tact5,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(tact1) == LOW)
  {
    tone(buzzerPin,262,1000);
    noTone(buzzerPin);
  }
    if(digitalRead(tact2) == LOW)
  {
    tone(buzzerPin,294,1000);
    noTone(buzzerPin);
  }
    if(digitalRead(tact3) == LOW)
  {
    tone(buzzerPin,330,1000);
    noTone(buzzerPin);
  }
    if(digitalRead(tact4) == LOW)
  {
    tone(buzzerPin,349,1000);
    noTone(buzzerPin);
  }
    if(digitalRead(tact5) == LOW)
  {
    tone(buzzerPin,392,1000);
    noTone(buzzerPin);
  }
}
