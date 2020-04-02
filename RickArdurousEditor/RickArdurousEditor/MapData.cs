using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RickArdurousEditor
{
	class MapData
	{
		const int LEVEL_WIDTH = 16;
		const int LEVEL_HEIGHT = 32;
		private byte[,] mLevel = new byte[LEVEL_WIDTH, LEVEL_HEIGHT];

		const int WALL_SPRITE_COUNT = 16;
		private Bitmap[] mWallSprites = new Bitmap[WALL_SPRITE_COUNT];

		private enum WallId
		{
			BLOCK_16_8_RIGHT = 0,
			ROCK,
			ROCK_2,
			ROCK_GROUND,
			STAIR,
			BLOCK_8_8,
			BLOCK_8_8_SPLIT,
			SMALL_STATUE,
			BIG_STATUE_TOP,
			BIG_STATUE_BOTTOM,
			PLATFORM,
			LADDER,
			PLATFORM_WITH_LADDER,
			ARROW_LAUNCHER,
			DESTROYABLE_BLOCK,
			NOTHING = 15,
		};

		public MapData()
		{
			InitWallSpriteImages();
			ClearLevel();
			mLevel[1, 1] = 5;
			mLevel[3, 1] = 7;
		}

		public void ClearLevel()
		{
			for (int x = 0; x < LEVEL_WIDTH; ++x)
				for (int y = 0; y < LEVEL_HEIGHT; ++y)
					mLevel[x, y] = (byte)WallId.NOTHING;
		}

		private void InitWallSpriteImages()
		{
			Bitmap originalImage = new Bitmap(Application.StartupPath + @"\..\..\..\..\image\Walls.png");
			for (int y = 0; y < 8; ++y)
				for (int x = 0; x < 2; ++x)
				{
					Bitmap sprite = new Bitmap(8, 8);
					Graphics gc = Graphics.FromImage(sprite);
					gc.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
					gc.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.None;
					gc.DrawImage(originalImage, new Rectangle(0, 0, 8, 8), new Rectangle(x * 8, y * 8, 8, 8), GraphicsUnit.Pixel);
					mWallSprites[y + (x * 8)] = sprite;
				}
		}

		public void redraw(Graphics gc, int width, int height)
		{
			// set the drawing mode
			gc.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			gc.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.None;

			// compute the size of the sprite
			int spriteWidth = width / LEVEL_WIDTH;
			int spriteHeight = height / LEVEL_HEIGHT;

			// draw all the sprites
			for (int x = 0; x < LEVEL_WIDTH; ++x)
				for (int y = 0; y < LEVEL_HEIGHT; ++y)
					gc.DrawImage(mWallSprites[mLevel[x,y]], (x * spriteWidth), (y * spriteHeight), spriteWidth, spriteHeight);
		}
	}
}
