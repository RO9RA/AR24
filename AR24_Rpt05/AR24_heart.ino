#include "LedControlMS.h"

#define NBR_MTX 1 //number of matrices attached is one

LedControl lc=LedControl(4,3,2, NBR_MTX);//

unsigned long delayTime=1200;  // Delay between Frames

// Put values in arrays
byte invader1a[] =
{
  B00100100, // Second frame of invader #1
  B01011010,
  B10000001,
  B10000001, 
  B01000010,
  B00100100,
  B00011000,
  B00000000
};

byte invader1b[] =
{
  B00100100, // Second frame of invader #1
  B01111110,
  B11111111,
  B11111111, 
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

void setup()
{
      lc.shutdown(0,false);
    // Wake up displays
//  lc.shutdown(1,false);
  lc.setIntensity(0,5);
    // Set intensity levels
//  lc.setIntensity(1,5);
  lc.clearDisplay(0);
    // Clear Displays
//  lc.clearDisplay(1);
}


//  Take values in Arrays and Display them
void sinvader1a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,invader1a[i]);
  }
}

void sinvader1b()
{
  for (int i = 0; i < 8; i++)
  {
     lc.setRow(0,i,invader1b[i]);
  }
}

void loop()
{
// Put #1 frame on both Display
    
    delay(delayTime);
    sinvader1a();
    delay(delayTime);


// Put #2 frame on both Display
    
    delay(delayTime);
    sinvader1b();
    delay(delayTime);

}
