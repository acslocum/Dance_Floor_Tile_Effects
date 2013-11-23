#include "SPI.h"
#include "Adafruit_WS2801.h"
#include "shapes.h"

/*****************************************************************************
Example sketch for driving Adafruit WS2801 pixels!


  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683

  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by David Kavanagh (dkavanagh@gmail.com).  
  BSD license, all text above must be included in any redistribution

*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
uint8_t dataPin  = 13;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 12;    // Green wire on Adafruit Pixels

uint16_t WIDTH=5;
uint16_t HEIGHT=5;

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels in a row and
// the second value to number of pixels in a column.
Adafruit_WS2801 strip = Adafruit_WS2801(WIDTH, HEIGHT, dataPin, clockPin);

void setup() {
    
  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
  randomSeed(analogRead(0));
}


void loop() {
  // Some example procedures showing how to display to the pixels
  //drawX(5, 5, 100);
  //drawLine(0,0,0,4,Wheel(random(256)),2000);
  
  bounce(5, 5, 50);
  lightup(5,5,Wheel(random(256)), 100);
  spiralIn(5,5,Wheel(random(256)),75);
  spiralOut(5,5,Wheel(random(256)),75);
  checkerboard(5, 5, Wheel(random(256)), Wheel(random(256)), 1000); 
  pulse(5,5, Wheel(random(256)), 50, 30);
  biDiaganolFill(5, 5, Wheel(random(256)), 100);
  drawRectangle(2, 2, 1, 1, Wheel(random(256)), 300);
  growSquares(5, 5, 300);
  diaganolFill(5,5,Wheel(random(256)), 300);
  slideOutLines(5,5,100);
  quadDiaganolFill(5,5,Wheel(random(256)), 200);
  expandingCorner(5,5,Wheel(random(256)), 75);
  randomCycle(256,50);
}

void expandingCorner(uint8_t w, uint8_t h, uint32_t c, uint16_t wait)
{
  int8_t i,x,y;
  for (i=0; i < w; i++)
  {
    for (x=0; x <=i; x++)
    {
      strip.setPixelColor(x,i,c);
      strip.setPixelColor(i,x,c);
    }
    strip.show();
    delay(wait);
  } 
}

void diaganolFill(uint8_t w, uint8_t h, uint32_t c, uint16_t wait)
{
  int8_t i,a,b;
  for (i=0; i < w; i++)
    {
      a = i;
      b = 0;
      while(b <= i)
        {
          //printf("a: %d, b: %d\n", a,b);
          strip.setPixelColor(a, b, c);                                       
          a--;
          b++;
        }
      strip.show();                                                           
      delay(wait);                                                            
    }

  for (i=1; i < w; i++)
  {
    a = i;
    b = w-1;
    while((b >= 0) && (a < w))
    {
      strip.setPixelColor(a, b, c);                                           
      //printf("a: %d, b: %d\n", a,b);
      a++;
      b--;
    }
    strip.show();                                                             
    delay(wait);                                                              
  }
}

void quadDiaganolFill(uint8_t w, uint8_t h, uint32_t c, uint16_t wait)
{
  int8_t i, a, b;
  for (i=0; i < w; i++)
  {
    a = i;
    b = 0;
    while(b <= i)
    {
      strip.setPixelColor(a, b, c);
      strip.setPixelColor(w-a-1, b, c);
      strip.setPixelColor(a, w-b-1, c);
      strip.setPixelColor(w-a-1, w-b-1, c);
      a--;
      b++;
    }
    strip.show();
    delay(wait);
  }
}

void slideOutLines(uint8_t w, uint8_t h, uint16_t wait)
{
  int8_t i;
  for (i=0; i < w/2+1; i++)
  {
    uint32_t c = Wheel(random(256));
    drawLine(0, i, w-1, i, c, 0);
    drawLine(0, w-i-1, w-1, w-i-1, c, 0);
    delay(wait);
  } 
}

void pulse(uint8_t w, uint8_t h, uint32_t c, uint8_t steps, uint16_t wait)
{
  uint8_t i,r,g,b;
  uint32_t color = c;
  b = color & 0xff;
  color = (color >> 8);
  g = color & 0xff;
  color = (color >> 8);
  r = color & 0xff;
  
  float intensity;
  for (i = steps; i > 0; i--)
  {
    intensity = i / (float)(steps);
    color = 0;
    color |= (uint32_t) (r * intensity);
    color = (color << 8);
    color |= (uint32_t) (g * intensity);
    color = (color << 8);
    color |= (uint32_t) (b * intensity);
    lightup(w,h,color,wait);
  }  
  for (i = 1; i <= steps; i++)
  {
    intensity = i / (float)(steps);
    color = 0;
    color |= (uint32_t) (r * intensity);
    color = (color << 8);
    color |= (uint32_t) (g * intensity);
    color = (color << 8);
    color |= (uint32_t) (b * intensity);
    lightup(w,h,color,wait);
  }   
}

void drawX(uint8_t w, uint8_t h, uint16_t wait) {
  uint16_t x, y;
  for (x=0; x<w; x++) {
    strip.setPixelColor(x, x, 255, 0, 0);
    strip.show();
    delay(wait);
  }
  for (y=0; y<h; y++) {
    strip.setPixelColor(w-1-y, y, 0, 0, 255);
    strip.show();
    delay(wait);
  }

}

void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint32_t c, uint16_t wait)
{
  uint8_t i;
  if (x1 == x2)
  {
    verticalLine(strip,x1,y1,y2,c);
  } else {
    horizontalLine(strip,y1,x1,x2,c);
  }
  strip.show();
  delay(wait);
}

void drawRectangle(uint8_t x1, uint8_t y1, uint8_t w, uint8_t h, uint32_t c, uint16_t wait)
{
  openRect(x1,y1,w,h,c);
  strip.show();
  delay(wait);
}

void growSquares(uint8_t w, uint8_t h, uint16_t wait)
{
  for (int i=0; i < 3; i++)
  {
    drawRectangle(i, i, w - 2*i, w - 2*i, Wheel(random(256)), wait);
  } 
  //delay(wait);
}

void biDiaganolFill(uint8_t w, uint8_t h, uint32_t c, uint16_t wait)
{
  int8_t a,b,i;
  for (i=0; i < w; i++)
  {
    a = i;
    b = 0;
    while(b <= i)
    {
      strip.setPixelColor(a, b, c);
      strip.setPixelColor(w-a-1, w-b-1, c);
      a--;
      b++;
    }
    strip.show();
    delay(wait);
  }
}

void spiralIn(uint8_t w, uint8_t h, uint32_t c, uint16_t wait)
{
  int8_t i, j, k;
  
  for (i = w - 1, j = 0; i >= 0; i--, j++)
  {
    for(k = j ; k < i; k++)
    {
      strip.setPixelColor(j, k, c);
      strip.show();
      delay(wait);
    }
    for(k = j ; k < i; k++) 
    {
      strip.setPixelColor(k, i, c);
      strip.show();
      delay(wait);
    }
    for (k = i; k > j; k--)
    {
      strip.setPixelColor(i, k, c);
      strip.show();
      delay(wait);
    }
    for (k = i; k > j; k--)
    {
      strip.setPixelColor(k, j, c);
      strip.show();
      delay(wait);
    }
  }
  // set central pixel if size is odd
  if (w % 2)
  {
      strip.setPixelColor(w/2, w/2, c);
      strip.show();
      delay(wait);    
  }
}

void spiralOut(uint8_t w, uint8_t h, uint32_t c, uint16_t wait)
{
  // (di, dj) is a vector - direction in which we move right now                
  int8_t di = 1;
  int8_t dj = 0;
  // length of current segment                                                  
  int8_t segment_length = 1;

  // current position (i, j) and how much of current segment we passed          
  int8_t i = 2;
  int8_t j = 2;
  int8_t segment_passed = 0;
  for (int8_t k = 0; k < w*h; ++k) 
  {
    //printf("%d, %d\n", i,j);
    strip.setPixelColor(i,j,c);
    // make a step, add 'direction' vector (di, dj) to current position (i, j)  
    i += di;
    j += dj;
    ++segment_passed;

    if (segment_passed == segment_length) 
    {
      // done with current segment                                              
      segment_passed = 0;

      // 'rotate' directions                                                    
      int8_t buffer = di;
      di = -dj;
      dj = buffer;

      // increase segment length if necessary                                   
      if (dj == 0) {
        ++segment_length;
      }
    }
    strip.show();
    delay(wait);
  }
}


void lightup(uint8_t w, uint8_t h, uint32_t c, uint16_t wait) 
{
  uint16_t x, y;
  for (x=0; x<w; x++) 
  {
    for (y=0; y<h; y++) 
    {
      strip.setPixelColor(x, y, c);
    }
  }
  strip.show();
  delay(wait);
}

void checkerboard(uint8_t w, uint8_t h, uint32_t c1, uint32_t c2, uint16_t wait) 
{
  uint16_t x, y;
  uint32_t color = c1;
  for (x=0; x<w; x++) 
  {
    for (y=0; y<h; y++) 
    {
      strip.setPixelColor(x, y, color);
      if (color == c1)
        color = c2;
      else
        color = c1;
    }
  }
  strip.show();
  delay(wait);
}

void bounce(uint8_t w, uint8_t h, uint16_t wait) 
{
  // clear tile first
  lightup(w, h, 0, 0);

  int16_t x = random(w); // starting x
  int16_t y = random(h); // starting y
  int8_t xdir = +1;
  int8_t ydir = -1;
  int j;
  for (j=0; j < 256; j++) 
  {
    x = random(w); // starting x
    y = random(h); // starting y
     x = x + xdir;
     y = y + ydir;
     if (x < 0) {
       x = -x;
       xdir = - xdir;
     }
     if (y < 0) {
       y = -y;
       ydir = - ydir;
     }
     if (x == w) {
       x = w-2;
       xdir = - xdir;
     }
     if (y == h) {
       y = h-2;
       ydir = - ydir;
     }
     strip.setPixelColor(x, y, Wheel(j));
     strip.show();
     delay(wait);
     strip.setPixelColor(x, y, 0, 0, 0);
  }
}

int randomCycle(int steps, uint16_t wait) {
  for(int i=0;i<WIDTH;++i) {
    for(int j=0;j<HEIGHT;++j) {
      strip.setPixelColor(i,j,Wheel(random(256)));
    } 
  }
  for(;steps>0;--steps) {
    for(int i=0;i<WIDTH;++i) {
      for(int j=0;j<HEIGHT;++j) {
        colorCycle(strip,i,j);
      }
    }
    strip.show();
    delay(wait);
  }
}

/* Helper functions */

void colorCycle(Adafruit_WS2801 strip, uint8_t x, uint8_t y) {
  uint16_t linearLocation = x + WIDTH*y;
  uint32_t color = strip.getPixelColor(linearLocation);
  byte wheelColor = unWheel(color);
  strip.setPixelColor(x,y,Wheel((wheelColor+1)%256));
}

