  const int ledA = 3;
  const int ledB = 5;
  const int ledC = 6;
  const int ledD = 9;
  const int ledtest = 11;

  int dimTime = 20;

int number = 1;
boolean flag = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
dimLed(ledA);

dimLed(ledB);

dimLed(ledC);

dimLed(ledD);

}

void dimLed(int led)
{
   for(int fadeValue =0; fadeValue <=255; fadeValue +=5)
{
  analogWrite(led,fadeValue);
  delay(dimTime);  
}

for(int fadeValue =255; fadeValue >=0; fadeValue -=5)
{
  analogWrite(led,fadeValue);
  delay(dimTime); 
 }
 }





