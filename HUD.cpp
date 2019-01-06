/*
 * This file implement display of the HUD in game
*/

#include "RickArdurous.h"
#include "SpriteData.h"
#include "HUD.h"
#include "Rick.h"
namespace HUD
{
	const unsigned char LIFE_POS = 3;
	const unsigned char BULLET_POS = 32;
	const unsigned char DYNAMITE_POS = 64;
	const unsigned char STATUETTE_POS = 95;
	const unsigned char GAP_BETWEEN_LOGO_AND_NUMBER = 3;
	
	unsigned char drawNumber(unsigned char posX, unsigned char num);
}

void HUD::Update()
{
	// clear the top area where HUD will be drawn
	arduboy.fillRect(0,0, WIDTH, 6, BLACK);
	//arduboy.drawFastHLine(0, 5, WIDTH, WHITE);
	
	// draw each sprites from the HUD
	// draw the life count
	arduboy.drawBitmap(LIFE_POS, 0, SpriteData::HUDHeart, SpriteData::HUD_SPRITE_WIDTH, SpriteData::HUD_SPRITE_HEIGHT, WHITE);
	arduboy.drawBitmap(LIFE_POS + SpriteData::HUD_SPRITE_WIDTH + GAP_BETWEEN_LOGO_AND_NUMBER, 0, SpriteData::Numbers[Rick::LifeCount], SpriteData::NUMBERS_SPRITE_WIDTH, SpriteData::NUMBERS_SPRITE_HEIGHT, WHITE);
	
	// draw the bullet count
	arduboy.drawBitmap(BULLET_POS, 0, SpriteData::HUDBullet, SpriteData::HUD_BULLET_SPRITE_WIDTH, SpriteData::HUD_SPRITE_HEIGHT, WHITE);
	arduboy.drawBitmap(BULLET_POS + SpriteData::HUD_BULLET_SPRITE_WIDTH + GAP_BETWEEN_LOGO_AND_NUMBER, 0, SpriteData::Numbers[Rick::BulletCount], SpriteData::NUMBERS_SPRITE_WIDTH, SpriteData::NUMBERS_SPRITE_HEIGHT, WHITE);

	// draw the dynamite count
	arduboy.drawBitmap(DYNAMITE_POS, 0, SpriteData::HUDDynamite, SpriteData::HUD_SPRITE_WIDTH, SpriteData::HUD_SPRITE_HEIGHT, WHITE);
	arduboy.drawBitmap(DYNAMITE_POS + SpriteData::HUD_SPRITE_WIDTH + GAP_BETWEEN_LOGO_AND_NUMBER, 0, SpriteData::Numbers[Rick::DynamiteCount], SpriteData::NUMBERS_SPRITE_WIDTH, SpriteData::NUMBERS_SPRITE_HEIGHT, WHITE);
	
	// draw the statuette count
	arduboy.drawBitmap(STATUETTE_POS, 0, SpriteData::HUDStatuette, SpriteData::HUD_SPRITE_WIDTH, SpriteData::HUD_SPRITE_HEIGHT, WHITE);
	unsigned char posX = drawNumber(STATUETTE_POS + SpriteData::HUD_SPRITE_WIDTH + GAP_BETWEEN_LOGO_AND_NUMBER, Rick::StatuetteCount);
	arduboy.drawBitmap(posX + 1, 0, SpriteData::HUDSlash, SpriteData::HUD_SLASH_SPRITE_WIDTH, SpriteData::NUMBERS_SPRITE_HEIGHT, WHITE);
	drawNumber(posX + SpriteData::HUD_SLASH_SPRITE_WIDTH + 3, Rick::MAX_STATUETTE_COUNT);
}

unsigned char HUD::drawNumber(unsigned char posX, unsigned char num)
{
	// count how many character we will need to draw the number, and init the x position
	unsigned char digitCount = /*(num >= 100) ? 3 : */ ((num >= 10) ? 2 : 1);
	unsigned char lastPos = posX + (digitCount * (SpriteData::NUMBERS_SPRITE_WIDTH + 1));
	unsigned char x = lastPos;
	// draw all the needed chars
	for (unsigned char i = 0; i < digitCount; ++i)
	{
		// shift the position
		x -= SpriteData::NUMBERS_SPRITE_WIDTH + 1;
		// draw the modulo
		arduboy.drawBitmap(x, 0, SpriteData::Numbers[num % 10], SpriteData::NUMBERS_SPRITE_WIDTH, SpriteData::NUMBERS_SPRITE_HEIGHT, WHITE);
		// divide the num to draw the next number
		num = num / 10;
	}
	return lastPos;
}