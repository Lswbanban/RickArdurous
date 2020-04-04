using System;
using System.Drawing;
using System.IO;
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
		private Bitmap[] mWallSpritesMirrored = new Bitmap[WALL_SPRITE_COUNT];

		private Pen mPuzzleScreenSeparatorLinePen = new Pen(Color.CornflowerBlue, 2);

		#region get/set
		private int mDrawSpriteWidth = 32;
		public int DrawSpriteWidth
		{
			get { return mDrawSpriteWidth; }
			set
			{
				mDrawSpriteWidth = value;
				if (mDrawSpriteWidth < 2)
					mDrawSpriteWidth = 2;
			}
		}

		private int mDrawSpriteHeight = 32;
		public int DrawSpriteHeight
		{
			get { return mDrawSpriteHeight; }
			set
			{
				mDrawSpriteHeight = value;
				if (mDrawSpriteHeight < 2)
					mDrawSpriteHeight = 2;
			}
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

		#region init
		public MapData()
		{
			InitWallSpriteImages();
			ClearLevel();
			mLevel[1, 1] = 5;
			mLevel[3, 1] = 7;

			mLevel[23, 3] = 6;
			mLevel[23, 4] = 8;

		}

		private Bitmap GetSprite(Bitmap originalImage, int x, int y, bool isMirrored)
		{
			Bitmap sprite = new Bitmap(8, 8);
			Graphics gc = Graphics.FromImage(sprite);
			gc.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			gc.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.None;
			if (isMirrored)
			{
				gc.TranslateTransform(8, 0);
				gc.ScaleTransform(-1, 1);
			}
			gc.DrawImage(originalImage, new Rectangle(0, 0, 8, 8), new Rectangle(x * 8, y * 8, 8, 8), GraphicsUnit.Pixel);
			return sprite;
		}

		private void InitWallSpriteImages()
		{
			Bitmap originalImage = new Bitmap(Application.StartupPath + @"\..\..\..\..\image\Walls.png");
			for (int y = 0; y < 8; ++y)
				for (int x = 0; x < 2; ++x)
				{
					int spriteId = y + (x * 8);
					mWallSprites[spriteId] = GetSprite(originalImage, x, y, false);
					mWallSpritesMirrored[spriteId] = GetSprite(originalImage, x, y, true);
				}
		}
		#endregion

		#region read/write
		private void WriteHeader(StreamWriter writer)
		{
			writer.WriteLine("/*");
			writer.WriteLine(" * This is a generated file, use the Editor to modify it.");
			writer.WriteLine(" */");
			writer.WriteLine();
			writer.WriteLine("#include \"MapData.h\"");
			writer.WriteLine("#include \"SpriteData.h\"");
			writer.WriteLine("#include \"MapManager.h\"");
			writer.WriteLine("#include \"ArrowLauncher.h\"");
			writer.WriteLine("#include \"Spike.h\"");
			writer.WriteLine("#include \"Statuette.h\"");
			writer.WriteLine("#include \"Dynamite.h\"");
			writer.WriteLine("#include \"DynamiteCrate.h\"");
			writer.WriteLine("#include \"BulletCrate.h\"");
			writer.WriteLine("#include \"Enemy.h\"");
			writer.WriteLine("#include \"DestroyableBlock.h\"");
			writer.WriteLine("#include \"Stalactite.h\"");
			writer.WriteLine("#include \"Stalagmite.h\"");
			writer.WriteLine("#include <avr/pgmspace.h>");
			writer.WriteLine();
			writer.WriteLine("#define ID(id1,id2) ((id1<< 4) | id2)");
			writer.WriteLine();
		}

		private void WriteLevelId(StreamWriter writer, byte id, bool isWritingHighBit)
		{
			if (isWritingHighBit)
				writer.Write("ID(" + id.ToString() + ",");
			else
				writer.Write(id.ToString() + "),");
		}

		private void WriteLevelData(StreamWriter writer)
		{
			writer.WriteLine("const unsigned char MapManager::Level[] PROGMEM = {");
			for (int y = 0; y < 16; ++y)
			{
				writer.Write("\t");
				bool shouldCountSpace = false;
				bool isWritingHighBit = true;
				byte spaceCounter = 1;
				for (int x = 0; x < 32; ++x)
				{
					byte id = mLevel[x, y];
					if (shouldCountSpace)
					{
						if (id == (byte)WallId.NOTHING)
						{
							spaceCounter++;
							if (spaceCounter < 15)
							{
								continue;
							}
							else
							{
								WriteLevelId(writer, spaceCounter, isWritingHighBit);
								isWritingHighBit = !isWritingHighBit;
								WriteLevelId(writer, (byte)WallId.NOTHING, isWritingHighBit);
								isWritingHighBit = !isWritingHighBit;
								spaceCounter = 1;
								continue;
							}
						}
						else
						{
							WriteLevelId(writer, spaceCounter, isWritingHighBit);
							isWritingHighBit = !isWritingHighBit;
							shouldCountSpace = false;							
						}
					}
					else if (id == (byte)WallId.NOTHING)
					{
						shouldCountSpace = true;
					}
					WriteLevelId(writer, id, isWritingHighBit);
					isWritingHighBit = !isWritingHighBit;
				}
				writer.WriteLine();
			}
			writer.WriteLine("};");
			writer.WriteLine();
		}

		public void Save(string fileName)
		{
			StreamWriter writer = new StreamWriter(fileName, false, System.Text.Encoding.UTF8);
			WriteHeader(writer);
			WriteLevelData(writer);
			writer.Flush();
			writer.Close();
		}
		#endregion

		#region util function
		public void ClampCoordinatesInsideLevel(ref Point coord)
		{
			coord.X = Math.Max(Math.Min(coord.X, LEVEL_WIDTH), 0);
			coord.Y = Math.Max(Math.Min(coord.Y, LEVEL_HEIGHT), 0);
		}

		public Point GetSpriteCoordFromScreenCoord(Point cameraLocation, Point screenLocation)
		{
			// iterate from the camera position, until we reach the correct screen coordinate in x
			int mapX = cameraLocation.X - 1;
			int screenX = 0;
			while (screenX <= screenLocation.X)
			{
				mapX++;
				screenX += DrawSpriteWidth;
				if ((mapX % ARDUBOY_PUZZLE_SCREEN_WIDTH) == 0)
					screenX += (int)mPuzzleScreenSeparatorLinePen.Width;
			}
			// and in y
			int mapY = cameraLocation.Y - 1;
			int screenY = 0;
			while (screenY <= screenLocation.Y)
			{
				mapY++;
				screenY += DrawSpriteHeight;
				if ((mapY % ARDUBOY_PUZZLE_SCREEN_HEIGHT) == 0)
					screenY += (int)mPuzzleScreenSeparatorLinePen.Width;
			}
			// return the point computed
			return new Point(mapX, mapY);
		}
		#endregion

		#region map edition
		public void ClearLevel()
		{
			for (int x = 0; x < LEVEL_WIDTH; ++x)
				for (int y = 0; y < LEVEL_HEIGHT; ++y)
					mLevel[x, y] = (byte)WallId.NOTHING;
		}

		public void SetSpriteId(Point coord, byte id)
		{
			if ((coord.X >= 0) && (coord.X < LEVEL_WIDTH) && (coord.Y >= 0) && (coord.Y < LEVEL_HEIGHT))
				mLevel[coord.X, coord.Y] = id;
		}
		#endregion

		#region draw
		public void redraw(Graphics gc, int width, int height, int cameraX, int cameraY)
		{
			// set the drawing mode
			gc.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			gc.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;

			// compute the number of puzzle screens that can be displayed in the available space
			int horizontalPuzzleScreenCount = width / DrawSpriteWidth / ARDUBOY_PUZZLE_SCREEN_WIDTH;
			int verticalPuzzleScreenCount = height / DrawSpriteWidth / ARDUBOY_PUZZLE_SCREEN_WIDTH;

			// compute the number of sprite that we can draw on the available space
			int availableSpriteCountX = 1 + ((width - ((int)mPuzzleScreenSeparatorLinePen.Width * horizontalPuzzleScreenCount)) / DrawSpriteWidth);
			int availableSpriteCountY = 1 + ((height - ((int)mPuzzleScreenSeparatorLinePen.Width * verticalPuzzleScreenCount)) / DrawSpriteHeight);

			// compute the last sprite to be drawn
			Point endCamera = new Point(cameraX + availableSpriteCountX, cameraY + availableSpriteCountY);
			ClampCoordinatesInsideLevel(ref endCamera);

			// avoid to start drawing too close to the end
			int maxCameraX = endCamera.X - availableSpriteCountX;
			if (cameraX > maxCameraX)
				cameraX = maxCameraX;
			int maxCameraY = endCamera.Y - availableSpriteCountY;
			if (cameraY > maxCameraY)
				cameraY = maxCameraY;
			Point startCamera = new Point(cameraX, cameraY);
			ClampCoordinatesInsideLevel(ref startCamera);

			// compute the width and height of the lines
			availableSpriteCountX = endCamera.X - startCamera.X;
			int lineWidth = Math.Min(width, (DrawSpriteWidth * availableSpriteCountX) + ((int)mPuzzleScreenSeparatorLinePen.Width * (availableSpriteCountX / ARDUBOY_PUZZLE_SCREEN_WIDTH)));
			availableSpriteCountY = endCamera.Y - startCamera.Y;
			int lineHeight = Math.Min(height, (DrawSpriteHeight * availableSpriteCountY) + ((int)mPuzzleScreenSeparatorLinePen.Width * (availableSpriteCountY / ARDUBOY_PUZZLE_SCREEN_HEIGHT)));

			// clear the image
			gc.Clear(Color.Black);

			// count the lines
			int horizontalLinesCount = 0;
			int halfPenWidth = (int)(mPuzzleScreenSeparatorLinePen.Width / 2);

			// draw all the sprites
			for (int y = startCamera.Y; y < endCamera.Y; ++y)
			{
				int yPixel = ((y - startCamera.Y) * DrawSpriteHeight) + horizontalLinesCount;
				// draw the puzzle screen lines
				if ((y % ARDUBOY_PUZZLE_SCREEN_HEIGHT) == 0)
				{
					gc.DrawLine(mPuzzleScreenSeparatorLinePen, 0, yPixel + halfPenWidth, lineWidth, yPixel + halfPenWidth);
					horizontalLinesCount += (int)mPuzzleScreenSeparatorLinePen.Width;
					yPixel += (int)mPuzzleScreenSeparatorLinePen.Width;
				}
				int verticalLinesCount = 0;
				for (int x = startCamera.X; x < endCamera.X; ++x)
				{
					int xPixel = ((x - startCamera.X) * DrawSpriteWidth) + verticalLinesCount;
					// draw the puzzle screen lines
					if ((x % ARDUBOY_PUZZLE_SCREEN_WIDTH) == 0)
					{
						// draw the vertical line only one time
						if (y == startCamera.Y)
							gc.DrawLine(mPuzzleScreenSeparatorLinePen, xPixel + halfPenWidth, 0, xPixel + halfPenWidth, lineHeight);
						verticalLinesCount += (int)mPuzzleScreenSeparatorLinePen.Width;
						xPixel += (int)mPuzzleScreenSeparatorLinePen.Width;
					}

					byte spriteId = mLevel[x, y];
					byte previousSpriteId = mLevel[Math.Max(x - 1, 0), y];
					bool isMirror = false;
					if (spriteId <= (int)WallId.ROCK_GROUND)
						isMirror = ((x * y) % 2) == 1;
					else if (spriteId == (int)WallId.STAIR)
						isMirror = (previousSpriteId == (int)WallId.NOTHING);
					else if ((spriteId == (int)WallId.BIG_STATUE_TOP) || (spriteId == (int)WallId.BIG_STATUE_BOTTOM))
						isMirror = (previousSpriteId == spriteId);

					// draw the sprites
					if (isMirror)
						gc.DrawImage(mWallSpritesMirrored[spriteId], xPixel, yPixel, DrawSpriteWidth, DrawSpriteHeight);
					else
						gc.DrawImage(mWallSprites[spriteId], xPixel, yPixel, DrawSpriteWidth, DrawSpriteHeight);
				}
				// draw the last line if needed
				if (endCamera.X == LEVEL_WIDTH)
				{
					int xPixel = ((endCamera.X - startCamera.X) * DrawSpriteWidth) + verticalLinesCount;
					gc.DrawLine(mPuzzleScreenSeparatorLinePen, xPixel + halfPenWidth, 0, xPixel + halfPenWidth, lineHeight);
				}
			}
			// draw the last line if needed
			if (endCamera.Y == LEVEL_HEIGHT)
			{
				int yPixel = ((endCamera.Y - startCamera.Y) * DrawSpriteHeight) + horizontalLinesCount;
				gc.DrawLine(mPuzzleScreenSeparatorLinePen, 0, yPixel + halfPenWidth, lineWidth, yPixel + halfPenWidth);
			}
		}
		#endregion
	}
}
