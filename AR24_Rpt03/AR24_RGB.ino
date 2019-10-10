const int ledR = 3;
const int ledG = 5;
const int ledB = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ledOutput(255,0,0);
  delay(1000);
  ledOutput(0,255,0);
  delay(1000);
  ledOutput(0,0,255);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

for(int i=0; i<=255;++i)
{
  ledOutput(255,i,0);
  delay(10); 
}

for(int i=0; i<=255;++i)
{
  ledOutput(0,255,i);
  delay(10); 
}

for(int i=0; i<=255;++i)
{
  ledOutput(i,0,255);
  delay(10); 
}

for(int i=0; i<=255;++i)
{
  ledOutput(i,255,255);
  delay(10); 
}

for(int i=0; i<=255;++i)
{
  ledOutput(255,i,255);
  delay(10); 
}

  for(int i=0; i<=255;++i)
{
  ledOutput(255,255,i); 
  if(i == 0)
  {
    Serial.println(i);
    delay(100000);
  }
   else
    delay(10);
   
}

}

void ledOutput (int Red, int Green, int Blue)
{
  analogWrite(ledR,Red);
  analogWrite(ledG,Green);
  analogWrite(ledB,Blue);   
}
