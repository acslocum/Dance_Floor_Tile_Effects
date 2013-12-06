#ifndef FLOOR
#define FLOOR
#include <Arduino.h>
//#include <Adafruit_WS2801.h>


const int RIGHT = 4; //rope heads right
const int DOWN = 1; //rope heads down
const int LEFT = 2; //rope heads left
const int UP = 3; //rope heads up

const int SINGLE_STRIP_LENGTH=25;
const int SINGLE_SQUARE_WIDTH=5;

class Floor {
  int length;
  int widthInSquares;


  //  1 6 7
  //  2 5 8
  //  3 4 9
  //x,y origin coordinates of each square
  static int SQUARE_X_OFFSET[9];
  static int SQUARE_Y_OFFSET[9];

  //Adafruit_WS2801 strip;
  int *index;

  public: 
    Floor(int totalRopeLength, int widthInSquares, int *orientation, int dataPin, int clockPin);
    void setPixelColor(int x, int y, uint32_t color);
    uint32_t getPixelColor(int x, int y);
    int lookup(int x, int y);
    void set(int x, int y, int value);
    void printGrid();
  private: 
    void fillRight(int squareNum, int offset);
    void fillDown(int squareNum, int offset);
    void fillLeft(int squareNum, int offset);
    void fillUp(int squareNum, int offset);
    void initMatrix(int *orientation);
    void allocateIndexMatrix();
    void setIndices(int squareNum, int orientation);
    
};
#endif
