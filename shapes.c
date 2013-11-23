#include "shapes.h"

void verticalLine(Adafruit_WS2801 strip, uint8_t x, uint8_t y1, uint8_t y2, uint32_t color) {
  int i=0;
  if(y1>y2) {//swap
    i = y1;
    y1 = y2;
    y2 = i;
  }
  for(i=y1;i<=y2;++i) {
    strip.setPixelColor(x,i,c);
  }
}

void horizontalLine(Adafruit_WS2801 strip, uint8_t y, uint8_t x1, uint8_t x2, uint32_t color) {
  int i=0;
  if (x1 > x2) { //swap
    i = x1;
    x1 = x2;
    x2 = i;
  }
  for(i=x1;i<=x2;++i) {
    strip.setPixelColor(i,y,c);
  }
}

void openRect(Adafruit_WS2801 strip, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint32_t color) {
  verticalLine(strip,x,y,y+height,c);
  verticallLine(strip,x+width,y,y+height,c);
  horizontalLine(strip,y,x,x+width,c);
  horizontalLine(strip,y+height,x,x+width,c);
}

void filledRect(Adafruit_WS2801 strip, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint32_t color) {
  for(int i=x; i<=(x+width); ++i) {
    for(int j=y; j<=(y+height);++j) {
      strip.setPixelColor(i,j,c);
    } 
  }
}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

byte unWheel(uint32_t color) {
  byte r = (byte)(color & 0xff);
  byte g = (byte)((color>>8) & 0xff);
  byte b = (byte)((color>>16) & 0xff);
  if(b==0) {
    return (byte)(r/3);
  } else if(g==0) {
    return (byte)(b/3+85);
  } else {
    return (byte)(g/3+170);
  }
}
