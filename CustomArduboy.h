#ifndef _CUSTOM_ARDUBOY_H_
#define _CUSTOM_ARDUBOY_H_

#include <Arduboy.h>

const uint8_t TRANSPARENT = 3;

class CustomArduboy : public Arduboy
{
public:
	unsigned int drawBitmapExtended(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color, bool mirrorX);
	bool CheckWhitePixelsInRow(uint8_t x, uint8_t y, uint8_t w);
};

#endif