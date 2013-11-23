#ifndef SHAPES
#define SHAPES

#include "Adafruit_WS2801.h"

void horizontalLine(Adafruit_WS2801 strip, uint8_t x, uint8_t y1, uint8_t y2, uint32_t color);
void verticalLine(Adafruit_WS2801 strip, uint8_t y, uint8_t x1, uint8_t x2, uint32_t color);
void openRect(Adafruit_WS2801 strip, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint32_t color);
void filledRect(Adafruit_WS2801 strip, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint32_t color);
uint32_t Color(byte r, byte g, byte b);
uint32_t Wheel(byte WheelPos);
byte unWheel(uint32_t color);

#endif
