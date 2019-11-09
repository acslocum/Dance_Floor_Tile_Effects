#include "floor.h"

//assumes a square layout
  
  int Floor::SQUARE_X_OFFSET[9] = {0,0,0,5,5,5,10,10,10};
  int Floor::SQUARE_Y_OFFSET[9] = {0,5,10,10,5,0,0,5,10};

  
  Floor::Floor(int totalRopeLength, int widthInSq, int *orientation, int dataPin, int clockPin) {
    //x,y origin coordinates of each square


    length = totalRopeLength;
    widthInSquares = widthInSq;
    initMatrix(orientation);
    //strip = Adafruit_WS2801(length, dataPin, clockPin);
  } 
  
  void Floor::setPixelColor(int x, int y, uint32_t color) {
    int location = lookup(x,y);
    //strip.setPixelColor(location,color);
  }
  
  uint32_t Floor::getPixelColor(int x, int y) {
    return 0; //strip.getPixelColor(lookup(x,y));
  }
  
  int Floor::lookup(int x, int y) {
    int WIDTH=SINGLE_SQUARE_WIDTH*widthInSquares;
    return index[x+WIDTH*y];
  }
  
  void Floor::set(int x, int y, int value) {
    int WIDTH=SINGLE_SQUARE_WIDTH*widthInSquares;
    index[x+WIDTH*y] = value;
  }
  
  void Floor::printGrid() {
    Serial.println("grid:");
    for(int i=0;i<15;++i) {
      if(i<10)
        Serial.print(" ");
      Serial.print(i);
      Serial.print(": ");
      for(int j=0;j<15;++j) {
        int value = lookup(j,i);
        if(value<10)
          Serial.print(" ");
        if(value<100)
          Serial.print(" ");
        Serial.print(value);
        Serial.print(" ");
      } 
      Serial.println("");
    }
  }

  
  void Floor::initMatrix(int *orientation) {
    allocateIndexMatrix();
    int squareCount = length/SINGLE_STRIP_LENGTH;
    for(int i=0;i< squareCount;++i) {
      setIndices(i,orientation[i]); 
    }
    //setIndices(0,2);
  }
  
  void Floor::allocateIndexMatrix() {
    index = new int [length];
    for(int i=0;i<(length);++i) {
      index[i] = -1; 
    }
  }
  
  void Floor::setIndices(int squareNum, int orientation) {
    int offset = squareNum*25;
    if(orientation == RIGHT) {
      fillRight(squareNum, offset); 
    } else if(orientation == DOWN) {
      fillDown(squareNum, offset);
    } else if(orientation == LEFT) {
      fillLeft(squareNum, offset);
    } else {
      fillUp(squareNum, offset); 
    }
  }
  
  void Floor::fillRight(int squareNum, int offset) {//4
    //0: 20 21 22 23 24
    //1: 19 18 17 16 15
    //2: 10 11 12 13 14
    //3:  9  8  7  6  5
    //4:  0  1  2  3  4
    for(int y=0;y<SINGLE_SQUARE_WIDTH;++y) {
       for(int x=0;x<SINGLE_SQUARE_WIDTH;++x) {
         int value=0;
         if(y%2==0) {//even row
           value = x + (4-y)*SINGLE_SQUARE_WIDTH; //fill right
         } else {//odd row
           value = (4-x) + (4-y)*SINGLE_SQUARE_WIDTH; // fill left
         }
         set(x+SQUARE_X_OFFSET[squareNum], y+SQUARE_Y_OFFSET[squareNum], value+offset);
       } 
    }
  }
  
  void Floor::fillDown(int squareNum, int offset) {//1
    //0  9 10 19 20
    //1  8 11 18 21
    //2  7 12 17 22
    //3  6 13 16 23
    //4  5 14 15 24
    for(int y=0;y<SINGLE_SQUARE_WIDTH;++y) {
       for(int x=0;x<SINGLE_SQUARE_WIDTH;++x) {
         int value=0;
         if(x%2==0) { //even column
           value = y + x*SINGLE_SQUARE_WIDTH; //fill down
         } else { //odd column
           value = (4-y) + x*SINGLE_SQUARE_WIDTH;//fill up
         }
         set(x+SQUARE_X_OFFSET[squareNum], y+SQUARE_Y_OFFSET[squareNum], value+offset);
       } 
    }
  }
  
  void Floor::fillLeft(int squareNum, int offset) {//2
    //4  3  2  1  0
    //5  6  7  8  9
    //14 13 12 11 10
    //15 16 17 18 19
    //24 23 22 21 20
    for(int y=0;y<SINGLE_SQUARE_WIDTH;++y) {
       for(int x=0;x<SINGLE_SQUARE_WIDTH;++x) {
         int value=0;
         if(y%2==0) {//even row
           value = (4-x) + y*SINGLE_SQUARE_WIDTH; //fill left
         } else {//odd row
           value = x + y*SINGLE_SQUARE_WIDTH; //fill right
         }
         set(x+SQUARE_X_OFFSET[squareNum], y+SQUARE_Y_OFFSET[squareNum], value+offset);
       } 
    }
    
  }
  
  void Floor::fillUp(int squareNum, int offset) {//3
    //24 15 14  5  4
    //23 16 13  6  3
    //22 17 12  7  2
    //21 18 11  8  1
    //20 19 10  9  0
    for(int y=0;y<SINGLE_SQUARE_WIDTH;++y) {
       for(int x=0;x<SINGLE_SQUARE_WIDTH;++x) {
         int value=0;
         if(x%2==0) { //even column
           value = (4-y) + (4-x)*SINGLE_SQUARE_WIDTH;//fill up
         } else { //odd column
           value = y + (4-x)*SINGLE_SQUARE_WIDTH; //fill down
         }
         set(x+SQUARE_X_OFFSET[squareNum], y+SQUARE_Y_OFFSET[squareNum], value+offset);
       } 
    }
  }

