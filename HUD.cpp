/*
 * This file implement display of the HUD in game
*/

#include "RickArdurous.h"
#include "SpriteData.h"
#include "HUD.h"
#include "Rick.h"

void HUD::Update()
{
	// clear the top area where HUD will be drawn
	arduboy.fillRect(0,0, WIDTH, 6, BLACK);
	arduboy.drawFastHLine(0, 5, WIDTH, WHITE);
	
	//draw each sprites from the HUD
	arduboy.drawBitmap(2, 0, SpriteData::HUDHeart, SpriteData::HUD_SPRITE_WIDTH, SpriteData::HUD_SPRITE_HEIGHT, WHITE);
	arduboy.drawBitmap(12, 0, SpriteData::Numbers[Rick::LifeCount], SpriteData::NUMBERS_SPRITE_WIDTH, SpriteData::NUMBERS_SPRITE_HEIGHT, WHITE);
	
	arduboy.drawBitmap(30, 0, SpriteData::HUDStatuette, SpriteData::HUD_SPRITE_WIDTH, SpriteData::HUD_SPRITE_HEIGHT, WHITE);
	arduboy.drawBitmap(40, 0, SpriteData::Numbers[Rick::StatuetteCount], SpriteData::NUMBERS_SPRITE_WIDTH, SpriteData::NUMBERS_SPRITE_HEIGHT, WHITE);
	arduboy.drawBitmap(46, 0, SpriteData::Numbers[Rick::MAX_STATUETTE_COUNT], SpriteData::NUMBERS_SPRITE_WIDTH, SpriteData::NUMBERS_SPRITE_HEIGHT, WHITE);

	arduboy.drawBitmap(80, 0, SpriteData::HUDBullet, SpriteData::HUD_BULLET_SPRITE_WIDTH, SpriteData::HUD_SPRITE_HEIGHT, WHITE);
	arduboy.drawBitmap(90, 0, SpriteData::Numbers[Rick::BulletCount], SpriteData::NUMBERS_SPRITE_WIDTH, SpriteData::NUMBERS_SPRITE_HEIGHT, WHITE);

	arduboy.drawBitmap(100, 0, SpriteData::HUDDynamite, SpriteData::HUD_SPRITE_WIDTH, SpriteData::HUD_SPRITE_HEIGHT, WHITE);
	arduboy.drawBitmap(110, 0, SpriteData::Numbers[Rick::DynamiteCount], SpriteData::NUMBERS_SPRITE_WIDTH, SpriteData::NUMBERS_SPRITE_HEIGHT, WHITE);
}