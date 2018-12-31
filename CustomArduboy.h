#ifndef _CUSTOM_ARDUBOY_H_
#define _CUSTOM_ARDUBOY_H_

#include <Arduboy.h>

class CustomArduboy : public Arduboy
{
public:
	bool drawBitmapExtended(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color, bool mirrorX);
};

#endif