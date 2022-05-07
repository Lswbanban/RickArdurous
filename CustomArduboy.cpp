/*
 * This file contains an extension of the Arduboy class
 */

#include "RickArdurous.h"
#include "CustomArduboy.h"
#include "Arduboy_glcdfont.c"

#ifndef USE_ARDUBOY2

Arduboy::Arduboy()
{
  // frame management
  frameCount = 0;
  nextFrameStart = 0;
  post_render = false;
  // init not necessary, will be reset after first use
  // lastFrameStart
  // lastFrameDurationMs

  // font rendering  
  //cursor_x = 0;
  //cursor_y = 0;
}

// this is pusposely duplicated (without logo) so that
// whichever is actually used is linked and the one
// that is not is gone without wasting any space in flash
void Arduboy::beginNoLogo()
{
  boot(); // required

  // Audio
  tunes.initChannel(PIN_SPEAKER_1, 0);
  tunes.initChannel(PIN_SPEAKER_2, 1);
  audio.begin();
}

/* Frame management */

bool Arduboy::everyXFrames(uint8_t frames)
{
  return frameCount % frames == 0;
}

bool Arduboy::nextFrame()
{
  long now = millis();
  uint8_t remaining;

  // post render
  if (post_render)
  {
	#ifdef PROFILING
    lastFrameDurationMs = now - lastFrameStart;
	#endif
    frameCount++;
    post_render = false;
  }

  // if it's not time for the next frame yet
  if (now < nextFrameStart)
  {
    remaining = nextFrameStart - now;
    // if we have more than 1ms to spare, lets sleep
    // we should be woken up by timer0 every 1ms, so this should be ok
    if (remaining > 1)
      idle();
    return false;
  }

  // pre-render

  // technically next frame should be last frame + each frame but if we're
  // running a slow render we would constnatly be behind the clock
  // keep an eye on this and see how it works.  If it works well the
  // lastFrameStart variable could be eliminated completely
  nextFrameStart = now + eachFrameMillis;
  lastFrameStart = now;
  post_render = true;
  return post_render;
}

#ifdef PROFILING
int Arduboy::cpuLoad()
{
  return lastFrameDurationMs*100 / eachFrameMillis;
}
#endif

void Arduboy::initRandomSeed()
{
  power_adc_enable(); // ADC on
  randomSeed(~rawADC(ADC_TEMP) * ~rawADC(ADC_VOLTAGE) * ~micros() + micros());
  power_adc_disable(); // ADC off
}

uint16_t Arduboy::rawADC(byte adc_bits)
{
  ADMUX = adc_bits;
  // we also need MUX5 for temperature check
  if (adc_bits == ADC_TEMP) {
    ADCSRB = _BV(MUX5);
  }

  delay(2); // Wait for ADMUX setting to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  return ADC;
}

/* Graphics */


void Arduboy::drawPixel(uint8_t x, uint8_t y, uint8_t color)
{
  // draw the pixel at the correct place
  uint8_t row = y / 8;
  if (color)
  {
    sBuffer[(row*WIDTH) + x] |=   _BV(y % 8);
  }
  else
  {
    sBuffer[(row*WIDTH) + x] &= ~ _BV(y % 8);
  }
}

uint8_t Arduboy::getPixel(uint8_t x, uint8_t y)
{
  uint8_t row = y / 8;
  uint8_t bit_position = y % 8;
  return (sBuffer[(row*WIDTH) + x] & _BV(bit_position)) >> bit_position;
}

void Arduboy::drawFastHLine(uint8_t x, uint8_t y, uint8_t w, uint8_t color)
{
	// compute the end
	uint8_t end = x+w;
	
	// check if pixel is inside the screen to avoid patching the memory
	if ((end > WIDTH) || (y >= HEIGHT))
		return;
	
	// draw all the pixels of the line
	for (uint8_t a = x; a < end; a++)
		drawPixel(a,y,color);
}

void Arduboy::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
	// stupidest version - update in subclasses if desired!
	uint8_t end = y+h;
	for (uint8_t i = y; i < end; ++i)
		drawFastHLine(x, i, w, color);
}

void Arduboy::fillScreen(uint8_t color)
{
  // C version : 
  //
  // if (color) color = 0xFF;  //change any nonzero argument to b11111111 and insert into screen array.
  // for(int16_t i=0; i<1024; i++)  { sBuffer[i] = color; }  //sBuffer = (128*64) = 8192/8 = 1024 bytes. 
  
  asm volatile
  (
    // load color value into r27
    "mov r27, %1 \n\t"
    // if value is zero, skip assigning to 0xff
    "cpse r27, __zero_reg__ \n\t"
    "ldi r27, 0xff \n\t"
    // load sBuffer pointer into Z
    "movw  r30, %0\n\t"
    // counter = 0
    "clr __tmp_reg__ \n\t"
    "loopto:   \n\t"
    // (4x) push zero into screen buffer,
    // then increment buffer position
    "st Z+, r27 \n\t"
    "st Z+, r27 \n\t"
    "st Z+, r27 \n\t"
    "st Z+, r27 \n\t"
    // increase counter
    "inc __tmp_reg__ \n\t"
    // repeat for 256 loops
    // (until counter rolls over back to 0)
    "brne loopto \n\t"
    // input: sBuffer, color
    // modified: Z (r30, r31), r27
    :
    : "r" (sBuffer), "r" (color)
    : "r30", "r31", "r27"
  );
}

void Arduboy::drawChar(uint8_t x, uint8_t y, unsigned char c, uint8_t color, uint8_t bg)
{
	// remove the drawing of the background (not used in this game)
	//boolean draw_background = bg != color;

	// the first 32 char as been removed from the font array
	c -= 32;

	for (int8_t i=0; i<6; i++ )
	{
		uint8_t line;
		if (i == 5)
		{
			line = 0x0;
		}
		else
		{
			line = pgm_read_byte(font+(c*5)+i);
		}

		for (int8_t j = 0; j<8; j++)
		{
			/*
			uint8_t draw_color = (line & 0x1) ? color : bg;
			if (draw_color || draw_background)
			{
				drawPixel(x + i, y + j, draw_color);
			}
			*/
			
			if (line & 0x1)
				drawPixel(x + i, y + j, color);
			
			line >>= 1;
		}
	}
}

void Arduboy::setCursor(uint8_t x, uint8_t y)
{
  cursor_x = x;
  cursor_y = y;
}

size_t Arduboy::write(uint8_t c)
{
  drawChar(cursor_x, cursor_y, c, 1, 0);
  cursor_x += 6;
}

void Arduboy::display()
{
  this->paintScreen(sBuffer);
}

unsigned char* Arduboy::getBuffer()
{
  return sBuffer;
}

#endif // USE_ARDUBOY2

unsigned int CustomArduboy::drawBitmapExtended(int8_t x, int8_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color, bool mirrorX)
{
	// no need to draw at all if we're offscreen
	if (x+w < 0 /*|| x > WIDTH-1*/ || y+h < 0 || y > HEIGHT-1)
		return 0;

	unsigned char yOffset = abs(y) % 8;
	char bufferRow = y / 8;
	if (y < 0)
	{
		bufferRow--;
		yOffset = 8 - yOffset;
	}
	unsigned char yOffsetComplement = 8 - yOffset;
	unsigned char bitmapRows = h / 8;
	if (h%8 != 0)
		bitmapRows++;
	// compute the start and end X (clamp if outside the screen)
	char startX = (x<0) ? -x : 0;
	char endX = (WIDTH-x < w) ? WIDTH-x : w;
	// a flag to check if there is white pixels under the drawn pixels of the bitmap
	unsigned int collisionDetected = 0;
	// iterate on the bitmapRows
	for (unsigned char a = 0; a < bitmapRows; ++a)
	{
		if (bufferRow > (HEIGHT/8)-1)
			break;
		if (bufferRow > -2)
		{
			// inverse the horizontal iteration inside the bitmap if we are mirrored on x
			char iCol = startX;
			char iColDirection = 1;
			if (mirrorX)
			{
				iCol = w-1-startX;
				iColDirection = -1;
			}
			int bRowShift = bufferRow*WIDTH;
			int nextBRowShift = (bufferRow+1)*WIDTH;
			for (char xCol = startX; xCol < endX; xCol++, iCol += iColDirection)
			{
				char currentX = x + xCol;
				uint8_t unshiftedByteToWrite = pgm_read_byte(bitmap+(a*w)+iCol);
				if (bufferRow >= 0)
				{
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
				if (yOffset && bufferRow<(HEIGHT/8)-1)
				{
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
		bufferRow++;
	}
	return collisionDetected;
}

bool CustomArduboy::CheckWhitePixelsInRow(uint8_t x, uint8_t y, uint8_t w)
{
	// need to check the y, because sometimes this function can be called with a y outside the screen
	if (y < HEIGHT)
	{
		unsigned char row = y / 8;
		unsigned char yLineToCheck = 1 << (y % 8);
		int startX = (row*WIDTH) + x;
		unsigned char* localBuffer = &(sBuffer[startX]);
		for (unsigned char i = 0; i < w; ++i)
			if (localBuffer[i] & yLineToCheck)
				return true;
	}
	return false;
}

