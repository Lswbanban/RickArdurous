using System;
using System.Collections.Generic;
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
		public const int WALL_SPRITE_WIDTH = 8;
		public const int WALL_SPRITE_HEIGHT = 8;
		private byte[,] mLevel = new byte[LEVEL_WIDTH, LEVEL_HEIGHT];

		// all the items in the level
		private Dictionary<Items.Item.Type, List<Items.Item>> mItems = new Dictionary<Items.Item.Type, List<Items.Item>>();

		private const int WALL_SPRITE_COUNT = 16;
		private Bitmap[] mWallSprites = new Bitmap[WALL_SPRITE_COUNT];
		private Bitmap[] mWallSpritesMirrored = new Bitmap[WALL_SPRITE_COUNT];

		private Pen mPuzzleScreenSeparatorLinePen = new Pen(Color.CornflowerBlue, 2);

		#region get/set
		public int DrawSpriteWidth
		{
			get { return WALL_SPRITE_WIDTH * mPixelSize; }
		}

		public int DrawSpriteHeight
		{
			get { return WALL_SPRITE_HEIGHT * mPixelSize; }
		}

		private int mPixelSize = 2;
		public int PixelSize
		{
			get { return mPixelSize; }
			set
			{
				mPixelSize = value;
				if (mPixelSize < 2)
					mPixelSize = 2;
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
			mLevel[15, 0] = 1;
			mLevel[1, 1] = 5;
			mLevel[3, 1] = 7;
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
			Bitmap originalImage = ImageProvider.GetWallSpriteImage();
			for (int y = 0; y < 8; ++y)
				for (int x = 0; x < 2; ++x)
				{
					int spriteId = y + (x * 8);
					mWallSprites[spriteId] = GetSprite(originalImage, x, y, false);
					mWallSpritesMirrored[spriteId] = GetSprite(originalImage, x, y, true);
				}
		}
		#endregion

		#region write
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

		private void WriteLevelId(StreamWriter writer, byte id, ref bool isWritingHighBit, ref int idCount)
		{
			if (isWritingHighBit)
			{
				writer.Write("ID(" + id.ToString() + ",");
				idCount++;
			}
			else
			{
				writer.Write(id.ToString() + "),");
			}
			// inverse the flag
			isWritingHighBit = !isWritingHighBit;
		}

		/// <summary>
		/// This function compute the bouding area of the level which countains something.
		/// It returns a bounding aligned on the puzzle screen.
		/// </summary>
		/// <param name="startX">the min x coord included</param>
		/// <param name="endX">the max x coord included</param>
		/// <param name="startY">the min y coord included</param>
		/// <param name="endY">the max y coord included</param>
		private void GetLevelBoundingBox(out int startX, out int endX, out int startY, out int endY)
		{
			// init the return values with the max and min values
			startX = LEVEL_WIDTH - 1;
			endX = 0;
			startY = LEVEL_HEIGHT - 1;
			endY = 0;
			// iterate on the whole level to find non emty cells
			for (int y = 0; y < LEVEL_HEIGHT; ++y)
				for (int x = 0; x < LEVEL_WIDTH; ++x)
					if (mLevel[x, y] != (byte)WallId.NOTHING)
					{
						// we found something, get the puzzle screen coord where is located the sprite
						int minScreenX = (x / ARDUBOY_PUZZLE_SCREEN_WIDTH) * ARDUBOY_PUZZLE_SCREEN_WIDTH;
						int maxScreenX = minScreenX + ARDUBOY_PUZZLE_SCREEN_WIDTH - 1;
						int minScreenY = (y / ARDUBOY_PUZZLE_SCREEN_HEIGHT) * ARDUBOY_PUZZLE_SCREEN_HEIGHT;
						int maxScreenY = minScreenY + ARDUBOY_PUZZLE_SCREEN_HEIGHT - 1;
						// check if we found a coordinate better that what we already found
						if (minScreenX < startX)
							startX = minScreenX;
						if (maxScreenX > endX)
							endX = maxScreenX;
						if (minScreenY < startY)
							startY = minScreenY;
						if (maxScreenY > endY)
							endY = maxScreenY;
					}
		}

		private void WriteLevelData(StreamWriter writer)
		{
			// get the bounding volume of the data to export
			int startX;
			int endX;
			int startY;
			int endY;
			GetLevelBoundingBox(out startX, out endX, out startY, out endY);

			// declare a list to store the index of each beggining of lines
			List<int> lineIndex = new List<int>(endY - startY + 1);
			int idCount = 0;

			writer.WriteLine("const unsigned char MapManager::Level[] PROGMEM = {");
			for (int y = startY; y <= endY; ++y)
			{
				// add the index of the first id of the line in the list
				lineIndex.Add(idCount);
				// start with a tab
				writer.Write("\t");
				bool shouldCountSpace = false;
				bool isWritingHighBit = true;
				byte spaceCounter = 1;
				for (int x = startX; x <= endX; ++x)
				{
					// get the current id
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
								WriteLevelId(writer, spaceCounter, ref isWritingHighBit, ref idCount);
								shouldCountSpace = false;
								spaceCounter = 1;
								continue;
							}
						}
						else
						{
							WriteLevelId(writer, spaceCounter, ref isWritingHighBit, ref idCount);
							shouldCountSpace = false;
							spaceCounter = 1;
						}
					}
					else if (id == (byte)WallId.NOTHING)
					{
						shouldCountSpace = true;
					}
					WriteLevelId(writer, id, ref isWritingHighBit, ref idCount);
				}
				// write the last low bit if we need to finish the line
				if (!isWritingHighBit)
				{
					if (shouldCountSpace)
						WriteLevelId(writer, spaceCounter, ref isWritingHighBit, ref idCount);
					else
						WriteLevelId(writer, 0, ref isWritingHighBit, ref idCount);
				}
				else if (shouldCountSpace)
				{
					// also if the last low bit was a space, write the space count in the next high and pad with a zero
					WriteLevelId(writer, spaceCounter, ref isWritingHighBit, ref idCount);
					WriteLevelId(writer, 0, ref isWritingHighBit, ref idCount);
				}
				writer.WriteLine();
			}
			writer.WriteLine("};");
			writer.WriteLine();

			// write the line index array
			writer.Write("const unsigned int MapManager::LevelLineIndex[] PROGMEM = {");
			foreach (int index in lineIndex)
				writer.Write(index.ToString() + ",");
			writer.WriteLine("};");
			writer.WriteLine();
		}

		private void WriteItemList(StreamWriter writer, List<Items.Item> itemList)
		{
			if (itemList.Count > 0)
			{
				int instanceCounter = 1;
				foreach (Items.Item item in itemList)
					item.WriteInstance(writer, instanceCounter++);
			}
		}

		private void WriteItems(StreamWriter writer)
		{
			// merge the two list of spikes
			List<Items.Item> spikeItemList = new List<Items.Item>();
			if (mItems.ContainsKey(Items.Item.Type.HORIZONTAL_SPIKE))
				spikeItemList.AddRange(mItems[Items.Item.Type.HORIZONTAL_SPIKE]);
			if (mItems.ContainsKey(Items.Item.Type.VERTICAL_SPIKE))
				spikeItemList.AddRange(mItems[Items.Item.Type.VERTICAL_SPIKE]);
			// if there is any spikes, write them
			WriteItemList(writer, spikeItemList);
		}

		public void Save(string fileName)
		{
			StreamWriter writer = new StreamWriter(fileName, false, System.Text.Encoding.UTF8);
			WriteHeader(writer);
			WriteLevelData(writer);
			WriteItems(writer);
			writer.Flush();
			writer.Close();
		}
		#endregion

		#region read
		private void ReadLevelData(StreamReader reader)
		{
			int x = 0;
			int y = 0;
			string line = reader.ReadLine();
			while (!reader.EndOfStream && !line.Contains("}"))
			{
				string[] tokens = line.Split(new string[] { "ID" }, StringSplitOptions.RemoveEmptyEntries);
				bool nextId1IsCount = false;
				foreach (string token in tokens)
				{
					if (token.StartsWith("("))
					{
						string[] ids = token.Split(new char[] { ',' });
						int id1 = int.Parse(ids[0].Substring(1));
						int id2 = int.Parse(ids[1].Remove(ids[1].IndexOf(')')));
						// check id1 first
						if (nextId1IsCount)
						{
							x += id1;
							nextId1IsCount = false;
						}
						else if (id1 == (int)WallId.NOTHING)
						{
							x += id2;
							continue;
						}
						else
						{
							mLevel[x, y] = (byte)id1;
							x++;
						}
						// check id2
						if (id2 == (int)WallId.NOTHING)
						{
							nextId1IsCount = true;
						}
						else
						{
							mLevel[x, y] = (byte)id2;
							x++;
						}
					}
				}
				// read the next line
				line = reader.ReadLine();
				y++;
				x = 0;
			}
		}

		public void Load(string fileName)
		{
			// clear the level
			ClearLevel();
			// and read the cpp file
			StreamReader reader = new StreamReader(fileName, System.Text.Encoding.UTF8);
			while (!reader.EndOfStream)
			{
				string line = reader.ReadLine();
				if (line.Contains("MapManager::Level[]"))
					ReadLevelData(reader);
			}
			reader.Close();
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

		public Items.Item GetItemAt(Point location)
		{
			foreach (List<Items.Item> itemList in mItems.Values)
				foreach (Items.Item item in itemList)
					if (item.IsUnder(location.X, location.Y))
						return item;
			return null;
		}

		public void AddItem(Items.Item.Type itemType, bool isMirrored, Point location)
		{
			// add the list of items of the specified type if not already in the dictionary
			if (!mItems.ContainsKey(itemType))
				mItems.Add(itemType, new List<Items.Item>());

			// add the item in the correct list
			mItems[itemType].Add(new Items.Item(itemType, isMirrored, location.X, location.Y));
		}

		public void RemoveItem(Items.Item itemToRemove)
		{
			if (mItems.ContainsKey(itemToRemove.ItemType))
				mItems[itemToRemove.ItemType].Remove(itemToRemove);
		}
		#endregion

		#region draw
		public void Redraw(Graphics gc, int width, int height, int cameraX, int cameraY, Items.Item selectedItem)
		{
			DrawLevelWalls(gc, width, height, cameraX, cameraY);
			DrawItems(gc, width, height, cameraX, cameraY, selectedItem);
		}

		private void DrawLevelWalls(Graphics gc, int width, int height, int cameraX, int cameraY)
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

		private void DrawItems(Graphics gc, int width, int height, int cameraX, int cameraY, Items.Item selectedItem)
		{
			// after drawing the map, move the compositing mode to sourc over, for the item to be drawn with transparency
			gc.CompositingMode = System.Drawing.Drawing2D.CompositingMode.SourceOver;
			// compute the camera position in game world coordinates
			int cameraXWorld = cameraX * WALL_SPRITE_WIDTH;
			int cameraYWorld = cameraY * WALL_SPRITE_HEIGHT;
			foreach (List<Items.Item> itemList in mItems.Values)
				foreach (Items.Item item in itemList)
					item.Draw(gc, mPixelSize, cameraXWorld, cameraYWorld, (selectedItem == item));
		}
		#endregion
	}
}
