/*
 * This file contains an extension of the Arduboy class
 */

#include "RickArdurous.h"
#include "CustomArduboy.h"

unsigned int CustomArduboy::drawBitmapExtended(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color, bool mirrorX)
{
  // no need to draw at all if we're offscreen
  if (x+w < 0 || x > WIDTH-1 || y+h < 0 || y > HEIGHT-1)
    return false;

  int yOffset = abs(y) % 8;
  int sRow = y >> 3;
  if (y < 0) {
    sRow--;
    yOffset = 8 - yOffset;
  }
  int yOffsetComplement = 8-yOffset;
  int rows = h >> 3;
  if (h%8!=0) rows++;
  // compute the start and end X (clamp if outside the screen)
  int startX = (x<0) ? -x : 0;
  int endX = (x+w > (WIDTH-1)) ? WIDTH-x : w;
  // a flag to check if there is white pixels under the drawn pixels of the bitmap
  unsigned int collisionDetected = 0;
  // iterate on the rows
  for (int a = 0; a < rows; a++) {
    int bRow = sRow + a;
    if (bRow > (HEIGHT/8)-1) break;
    if (bRow > -2) {
      // inverse the horizontal iteration inside the bitmap if we are mirrored on x
      int iCol = startX;
      int iColDirection = 1;
      if (mirrorX) {
        iCol = w-1-startX;
        iColDirection = -1;
      }
      int bRowShift = bRow*WIDTH;
      int nextBRowShift = (bRow+1)*WIDTH;
      for (int xCol = startX; xCol < endX; xCol++, iCol += iColDirection) {
        int currentX = x + xCol;
        uint8_t unshiftedByteToWrite = pgm_read_byte(bitmap+(a*w)+iCol);
        if (bRow >= 0) {
          int bufferPosition = bRowShift + currentX;
          uint8_t byteToWrite = unshiftedByteToWrite << yOffset;
		  if ((sBuffer[bufferPosition] & byteToWrite) != 0)
			collisionDetected |= 1 << iCol;
          if (color == WHITE)
            sBuffer[bufferPosition] |= byteToWrite;
          else if (color == BLACK)
            sBuffer[bufferPosition] &= ~byteToWrite;
          else if (color == INVERT)
            sBuffer[bufferPosition] ^= byteToWrite;
        }
        if (yOffset && bRow<(HEIGHT/8)-1) {
          int bufferPosition = nextBRowShift + currentX;
          uint8_t byteToWrite = unshiftedByteToWrite >> yOffsetComplement;
		  if ((sBuffer[bufferPosition] & byteToWrite) != 0)
			collisionDetected |= 1 << iCol;
          if (color == WHITE)
            sBuffer[bufferPosition] |= byteToWrite;
          else if (color == BLACK)
            sBuffer[bufferPosition] &= ~byteToWrite;
          else if (color == INVERT)
            sBuffer[bufferPosition] ^= byteToWrite;
        }
      }
    }
  }
  
  return collisionDetected;
}

unsigned int CustomArduboy::CheckWhitePixelsInRow(uint8_t x, uint8_t row, uint8_t w)
{
	unsigned int collisionDetected = 0;
	int startX = (row*WIDTH) + x;
	for (int i = 0; i < w; ++i)
		if (sBuffer[startX + i])
			collisionDetected |= 1 << i;
  return collisionDetected;
}

