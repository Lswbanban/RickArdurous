using System;
using System.Drawing;
using System.Windows.Forms;

namespace RickArdurousEditor
{
	class MapData
	{
		private const int ARDUBOY_PUZZLE_SCREEN_WIDTH = 16;
		private const int ARDUBOY_PUZZLE_SCREEN_HEIGHT = 8;
		private const int LEVEL_WIDTH = 256;
		private const int LEVEL_HEIGHT = 256;
		private byte[,] mLevel = new byte[LEVEL_WIDTH, LEVEL_HEIGHT];

		private const int WALL_SPRITE_COUNT = 16;
		private Bitmap[] mWallSprites = new Bitmap[WALL_SPRITE_COUNT];

		private Pen mPuzzleScreenSeparatorLinePen = new Pen(Color.Green, 2);

		#region get/set
		public int DrawSpriteWidth
		{
			get { return 32; }
		}

		public int DrawSpriteHeight
		{
			get { return 32; }
		}
		#endregion

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

			mLevel[23, 3] = 6;
			mLevel[23, 4] = 8;

		}

		public void ClearLevel()
		{
			for (int x = 0; x < LEVEL_WIDTH; ++x)
				for (int y = 0; y < LEVEL_HEIGHT; ++y)
					mLevel[x, y] = (byte)WallId.NOTHING;
		}

		public void ClampCoordinatesInsideLevel(ref Point coord)
		{
			coord.X = Math.Max(Math.Min(coord.X, LEVEL_WIDTH), 0);
			coord.Y = Math.Max(Math.Min(coord.Y, LEVEL_HEIGHT), 0);
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

		public void redraw(Graphics gc, int width, int height, int cameraX, int cameraY)
		{
			// set the drawing mode
			gc.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			gc.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;

			// compute the last sprite to be drawn
			int endCameraX = cameraX + ((width - ((int)mPuzzleScreenSeparatorLinePen.Width * (LEVEL_WIDTH / ARDUBOY_PUZZLE_SCREEN_WIDTH))) / DrawSpriteWidth);
			int endCameraY = cameraY + ((height - ((int)mPuzzleScreenSeparatorLinePen.Width * (LEVEL_HEIGHT / ARDUBOY_PUZZLE_SCREEN_HEIGHT))) / DrawSpriteHeight);

			// count the lines
			int horizontalLinesCount = 0;

			// draw all the sprites
			for (int y = cameraY; y < endCameraY; ++y)
			{
				int yPixel = ((y - cameraY) * DrawSpriteHeight) + horizontalLinesCount;
				// draw the puzzle screen lines
				if ((y % ARDUBOY_PUZZLE_SCREEN_HEIGHT) == 0)
				{
					int halfPenWidth = (int)(mPuzzleScreenSeparatorLinePen.Width / 2);
					gc.DrawLine(mPuzzleScreenSeparatorLinePen, 0, yPixel + halfPenWidth, width, yPixel + halfPenWidth);
					horizontalLinesCount += (int)mPuzzleScreenSeparatorLinePen.Width;
					yPixel += (int)mPuzzleScreenSeparatorLinePen.Width;
				}
				int verticalLinesCount = 0;
				for (int x = cameraX; x < endCameraX; ++x)
				{
					int xPixel = ((x - cameraX) * DrawSpriteWidth) + verticalLinesCount;
					// draw the puzzle screen lines
					if ((x % ARDUBOY_PUZZLE_SCREEN_WIDTH) == 0)
					{
						// draw the vertical line only one time
						if (y == 0)
						{
							int halfPenWidth = (int)(mPuzzleScreenSeparatorLinePen.Width / 2);
							gc.DrawLine(mPuzzleScreenSeparatorLinePen, xPixel + halfPenWidth, 0, xPixel + halfPenWidth, height);
						}
						verticalLinesCount += (int)mPuzzleScreenSeparatorLinePen.Width;
						xPixel += (int)mPuzzleScreenSeparatorLinePen.Width;
					}
					// draw the sprites
					gc.DrawImage(mWallSprites[mLevel[x, y]], xPixel, yPixel, DrawSpriteWidth, DrawSpriteHeight);
				}
			}
		}
	}
}
