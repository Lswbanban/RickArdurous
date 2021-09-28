#ifndef _CUSTOM_ARDUBOY_H_
#define _CUSTOM_ARDUBOY_H_

#include "Arduboy_core.h"
#include <SPI.h>
#include <Print.h>
#include <limits.h>

/// Library version.
/**
 * A version number, 'x.y.z', is stored in the form xxyyzz,
 * where ((x * 10000) + (y * 100) + (z)),
 * resulting in 'xxxyyzz', with no leading zeros.
 */
#define ARDUBOY_LIB_VER 10101 // 1.1.1

// EEPROM settings
#define EEPROM_VERSION 0
#define EEPROM_BRIGHTNESS 1
#define EEPROM_AUDIO_ON_OFF 2

// we reserve the first 16 byte of EEPROM for system use
#define EEPROM_STORAGE_SPACE_START 16 // and onward

//#define PROFILING

// eeprom settings above are neded for audio
#include "Arduboy_audio.h"

// compare Vcc to 1.1 bandgap
#define ADC_VOLTAGE (_BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1))
// compare temperature to 2.5 internal reference and _BV(MUX5)
#define ADC_TEMP (_BV(REFS0) | _BV(REFS1) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0))

class Arduboy : public Print, public ArduboyCore
{
public:
  Arduboy();

  /// Initializes the hardware (but with no boot logo)
  void beginNoLogo();

  /// Clears display.
  void clear() { fillScreen(BLACK); }


  /// Copies the contents of the screen buffer to the screen.
  /**
   * X and Y positions on the display are from the top left corner, thus a Y of 64
   * is the bottom of the screen and an X of 128 is the right side of the screen.
   * "Color" or "value" means choosing whether a pixel is lit or not - if color is
   * 0, the pixel is off (black), if color is 1, the pixel is on (white).
   */
  void display();

  /// Sets a single pixel on the screen buffer to white or black.
  void drawPixel(uint8_t x, uint8_t y, uint8_t color);

  uint8_t getPixel(uint8_t x, uint8_t y);

  /// Draws vertical line.
  void drawFastVLine(uint8_t x, uint8_t y, uint8_t h, uint8_t color);

  /// Draws a horizontal line.
  void drawFastHLine(uint8_t x, uint8_t y, uint8_t w, uint8_t color);

  /// Draws a filled-in rectangle.
  void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);

  /// Fills the screen buffer with white or black.
  void fillScreen(uint8_t color);

  /// Draws an ASCII character at a point.
  void drawChar(uint8_t x, uint8_t y, unsigned char c, uint8_t color, uint8_t bg);

  /// Sets the location of the screen cursor.
  void setCursor(uint8_t x, uint8_t y);

  unsigned char* getBuffer();

  /// Writes a single ASCII character to the screen.
  virtual size_t write(uint8_t);
  
  /// Seeds the random number generator with entropy from the temperature, voltage reading, and microseconds since boot.
  /**
   * This method is still most effective when called semi-randomly such
   * as after a user hits a button to start a game or other semi-random
   * events
   */
  void initRandomSeed();

  ArduboyTunes tunes;
  ArduboyAudio audio;

  bool nextFrame();
  bool everyXFrames(uint8_t frames);
  
  /// Returns the load on the CPU as a percentage.
  /**
   * This is based on how much of the time your app is spends rendering
   * frames.  This number can be higher than 100 if your app is rendering
   * really slowly.
   */
#ifdef PROFILING
  int cpuLoad();
#endif

  static constexpr uint8_t eachFrameMillis = 16; // for a frame rate of 60 = 1000/60;
  uint16_t frameCount;
  long lastFrameStart;
  long nextFrameStart;
  bool post_render;

#ifdef PROFILING
  uint8_t lastFrameDurationMs;
#endif

  /// useful for getting raw approximate voltage values
  uint16_t rawADC(byte adc_bits);

protected:
  unsigned char sBuffer[(HEIGHT*WIDTH)/8];


// Adafruit stuff
protected:
  uint8_t cursor_x;
  uint8_t cursor_y;
};


const uint8_t TRANSPARENT = 3;

class CustomArduboy : public Arduboy
{
public:
	unsigned int drawBitmapExtended(int8_t x, int8_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color, bool mirrorX);
	bool CheckWhitePixelsInRow(uint8_t x, uint8_t y, uint8_t w);
	uint8_t GetCursorX() { return cursor_x; }
	uint8_t GetCursorY() { return cursor_y; }
};

#endif