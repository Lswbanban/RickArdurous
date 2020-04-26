using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;

namespace RickArdurousEditor
{
	class Map
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
		public Map()
		{
			InitWallSpriteImages();
			Reset();
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

		List<Items.Item.Type>[] mSimilarTypes = new List<Items.Item.Type>[]
				{   new List<Items.Item.Type>(new Items.Item.Type[] { Items.Item.Type.GRAAL } ),
					new List<Items.Item.Type>(new Items.Item.Type[] { Items.Item.Type.HORIZONTAL_SPIKE, Items.Item.Type.VERTICAL_SPIKE } ),
					new List<Items.Item.Type>(new Items.Item.Type[] { Items.Item.Type.MUMMY, Items.Item.Type.SKELETON, Items.Item.Type.SCORPION }),
				};

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
			writer.WriteLine("#include \"Graal.h\"");
			writer.WriteLine("#include \"BulletCrate.h\"");
			writer.WriteLine("#include \"Enemy.h\"");
			writer.WriteLine("#include \"DestroyableBlock.h\"");
			writer.WriteLine("#include \"Stalactite.h\"");
			writer.WriteLine("#include \"Stalagmite.h\"");
			writer.WriteLine("#include \"Progress.h\"");
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
			List<int> lineIndex = new List<int>(endY - startY + 2);
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

			// add the index of the first id of the last line
			lineIndex.Add(idCount);

			// write the line index array
			writer.Write("const unsigned int MapManager::LevelLineIndex[] PROGMEM = {");
			foreach (int index in lineIndex)
				writer.Write(index.ToString() + ",");
			writer.WriteLine("};");
			writer.WriteLine();

			// write the level size
			writer.WriteLine("const unsigned char MapManager::LEVEL_WIDTH = " + (endX - startX + 1).ToString() + ";");
			writer.WriteLine("const unsigned char MapManager::LEVEL_HEIGHT = " + (endY - startY + 1).ToString() + ";");
			writer.WriteLine();
		}

		private int GetPuzzleScreenIdFromGameWorldCoord(int x, int y)
		{
			return ((y / (ARDUBOY_PUZZLE_SCREEN_HEIGHT * WALL_SPRITE_HEIGHT)) * (LEVEL_WIDTH / ARDUBOY_PUZZLE_SCREEN_WIDTH)) + (x / (ARDUBOY_PUZZLE_SCREEN_WIDTH * WALL_SPRITE_WIDTH));
		}

		private void GetPuzzleScreenCoordFromGameWorldCoord(int x, int y, out int screenX, out int screenY)
		{
			screenX = (x / (ARDUBOY_PUZZLE_SCREEN_WIDTH * WALL_SPRITE_WIDTH)) * ARDUBOY_PUZZLE_SCREEN_WIDTH;
			screenY = (y / (ARDUBOY_PUZZLE_SCREEN_HEIGHT * WALL_SPRITE_HEIGHT)) * ARDUBOY_PUZZLE_SCREEN_HEIGHT;
		}

		private int GetMaxItemCount(List<Items.Item.Type> itemTypes)
		{
			int[] maxCountPerSreen = new int[(LEVEL_WIDTH / ARDUBOY_PUZZLE_SCREEN_WIDTH) * (LEVEL_HEIGHT /ARDUBOY_PUZZLE_SCREEN_HEIGHT)];

			// iterate on the list of all the item of the specified type
			foreach (Items.Item.Type itemType in itemTypes)
				if (mItems.ContainsKey(itemType))
					foreach (Items.Item item in mItems[itemType])
						maxCountPerSreen[GetPuzzleScreenIdFromGameWorldCoord(item.X, item.Y)]++;

			// then iterate on the max count to find the highest
			int maxCount = 0;
			foreach (int count in maxCountPerSreen)
				if (maxCount < count)
					maxCount = count;

			// return the max found
			return maxCount;
		}

		private void WriteItemInstances(StreamWriter writer)
		{
			for (int i = 0; i < mSimilarTypes.Length; ++i)
			{
				// get the max number of instances that we need 
				int maxItemCount = GetMaxItemCount(mSimilarTypes[i]);
				for (int j = 1; j <= maxItemCount; ++j)
					Items.Item.WriteInstance(writer, mSimilarTypes[i][0], j);
			}
		}

		private List<Items.Item> GetItemsOnScreen(int left, int top)
		{
			List<Items.Item> result = new List<Items.Item>();
			// convert the scren coord to game world coord
			int leftX = left * WALL_SPRITE_WIDTH;
			int rightX = (left + ARDUBOY_PUZZLE_SCREEN_WIDTH ) * WALL_SPRITE_WIDTH;
			int topX = top * WALL_SPRITE_HEIGHT;
			int bottomX  = (top + ARDUBOY_PUZZLE_SCREEN_HEIGHT) * WALL_SPRITE_HEIGHT;
			// iterate on all items to find those inside the screen
			foreach (List<Items.Item> itemList in mItems.Values)
				foreach (Items.Item item in itemList)
					if (item.IsInPuzzleScreen(leftX, topX, rightX, bottomX))
						result.Add(item);
			// return the list
			return result;
		}

		private int IncreaseItemCounterAndGetId(ref int[] itemCount, Items.Item item)
		{
			// search in which Similar Item group the specified item belongs to
			for (int i = 0; i < mSimilarTypes.Length; ++i)
				if (mSimilarTypes[i].Contains(item.ItemType))
				{
					// increase the counter
					itemCount[i]++;
					return itemCount[i];
				}
			return 0;
		}

		private void WriteInitFunctionForOneScreen(StreamWriter writer, int screenId, int screenLeft, int screenTop)
		{
			// get all the items on the specified screen
			List<Items.Item> itemsOnScreen = GetItemsOnScreen(screenLeft, screenTop);

			// declare an array to count the items per type for the current screen
			int[] itemCount = new int[mSimilarTypes.Length];

			// begin of the init function
			writer.WriteLine();
			writer.WriteLine("void InitScreen" + screenId.ToString() + "(bool shouldRespawn)");
			writer.WriteLine("{");

			// add the items in the map manager
			writer.WriteLine("\t// Add a checkpoint if we need to");
			foreach (Items.Item item in itemsOnScreen)
				item.WriteCheckpoint(writer, IncreaseItemCounterAndGetId(ref itemCount, item));
			writer.WriteLine();

			// reset the item count array
			Array.Clear(itemCount, 0, itemCount.Length);

			// init the position of the item
			writer.WriteLine("\t// init all the item of the current puzzle screen");
			foreach (Items.Item item in itemsOnScreen)
				item.WriteInit(writer, IncreaseItemCounterAndGetId(ref itemCount, item));

			// finish the init function
			writer.WriteLine("}");
		}

		private bool IsAPuzzleScreenExit(byte wallId)
		{
			return (wallId >= (byte)WallId.DESTROYABLE_BLOCK) || (wallId == (byte)WallId.LADDER) || (wallId == (byte)WallId.PLATFORM_WITH_LADDER);
		}

		private bool GetStartOrEndPuzzleScreenCoordinates(bool isStart, out int screenX, out int screenY)
		{
			// default value if we didn't find the special respawn point
			screenX = 0;
			screenY = 0;

			// configure the type of item to search (either RICK for start or GRAAL for end)
			Items.Item.Type itemTypeToSearch = isStart ? Items.Item.Type.RICK : Items.Item.Type.GRAAL;

			// search in the rick item the one that match the specified parameter
			if (mItems.ContainsKey(itemTypeToSearch))
				foreach (Items.Item respawnItem in mItems[itemTypeToSearch])
					if (!isStart || (respawnItem.RickRespawnType == Items.Item.RespawnType.START))
					{
						GetPuzzleScreenCoordFromGameWorldCoord(respawnItem.X, respawnItem.Y, out screenX, out screenY);
						return true;
					}
			return false;
		}

		private int WriteInitFunctions(StreamWriter writer)
		{
			// get the coordinate of the start and End screen
			int startScreenX;
			int endScreenX;
			int startScreenY;
			int endScreenY;
			if (!GetStartOrEndPuzzleScreenCoordinates(true, out startScreenX, out startScreenY))
				throw new MapSaveException(Properties.Resources.ErrorNoStartPuzzleScreen, MainForm.LogLevel.ERROR);
			if (!GetStartOrEndPuzzleScreenCoordinates(false, out endScreenX, out endScreenY))
				throw new MapSaveException(Properties.Resources.ErrorNoEndPuzzleScreen, MainForm.LogLevel.ERROR);

			// declare a list for storing all the puzzle screen already exported
			List<Point> exportedPuzzleScreenCoord = new List<Point>();

			// init the current screen coord with the start one
			Point currentScreen = new Point(startScreenX, startScreenY);
			Point previousScreen = new Point(startScreenX, startScreenY);
			int screenId = 0;
			while ((currentScreen.X != endScreenX) || (currentScreen.Y != endScreenY))
			{
				// check if we didn't already exported the current puzzle screen, otherwise that means we have a cyclic path
				if (exportedPuzzleScreenCoord.Contains(currentScreen))
					throw new MapSaveException(Properties.Resources.ErrorCyclicPuzzlePathDetected, MainForm.LogLevel.ERROR);
				exportedPuzzleScreenCoord.Add(currentScreen);

				// write the init function of the current screen
				WriteInitFunctionForOneScreen(writer, screenId, currentScreen.X, currentScreen.Y);
				screenId++;

				// get the next screen coordinates above or below
				bool isExitFound = false;
				for (int x = currentScreen.X + 1; x < currentScreen.X + ARDUBOY_PUZZLE_SCREEN_WIDTH - 2; ++x)
				{
					if ((currentScreen.Y > 0) && 
						(currentScreen.Y - ARDUBOY_PUZZLE_SCREEN_HEIGHT != previousScreen.Y) &&
						IsAPuzzleScreenExit(mLevel[x, currentScreen.Y]))
					{
						previousScreen.Y = currentScreen.Y;
						currentScreen.Y -= ARDUBOY_PUZZLE_SCREEN_HEIGHT;
						isExitFound = true;
						break;
					}
					if ((currentScreen.Y < LEVEL_HEIGHT - ARDUBOY_PUZZLE_SCREEN_HEIGHT) &&
						(currentScreen.Y + ARDUBOY_PUZZLE_SCREEN_HEIGHT != previousScreen.Y) &&
						IsAPuzzleScreenExit(mLevel[x, currentScreen.Y + ARDUBOY_PUZZLE_SCREEN_HEIGHT - 1]))
					{
						previousScreen.Y = currentScreen.Y;
						currentScreen.Y += ARDUBOY_PUZZLE_SCREEN_HEIGHT;
						isExitFound = true;
						break;
					}
				}

				// get the next screen coordinates
				if (!isExitFound)
				{
					for (int y = currentScreen.Y + 1; y < currentScreen.Y + ARDUBOY_PUZZLE_SCREEN_HEIGHT - 2; ++y)
					{
						if ((currentScreen.X > 0) &&
							(currentScreen.X - ARDUBOY_PUZZLE_SCREEN_WIDTH != previousScreen.X) &&
							IsAPuzzleScreenExit(mLevel[currentScreen.X, y]))
						{
							previousScreen.X = currentScreen.X;
							currentScreen.X -= ARDUBOY_PUZZLE_SCREEN_WIDTH;
							isExitFound = true;
							break;
						}
						if ((currentScreen.X < LEVEL_WIDTH - ARDUBOY_PUZZLE_SCREEN_WIDTH) &&
							(currentScreen.X + ARDUBOY_PUZZLE_SCREEN_WIDTH != previousScreen.X) &&
							IsAPuzzleScreenExit(mLevel[currentScreen.X + ARDUBOY_PUZZLE_SCREEN_WIDTH - 1, y]))
						{
							previousScreen.X = currentScreen.X;
							currentScreen.X += ARDUBOY_PUZZLE_SCREEN_WIDTH;
							isExitFound = true;
							break;
						}
					}
				}

				// if we didn't found any exit, and didn't reach the last screen, we are in a dead end!
				if (!isExitFound && ((currentScreen.X != endScreenX) || (currentScreen.Y != endScreenY)))
					throw new MapSaveException(Properties.Resources.ErrorDeadEndNotExitFound, MainForm.LogLevel.ERROR, currentScreen.X.ToString(), currentScreen.Y.ToString());
			}
			// write the init function of the last screen
			WriteInitFunctionForOneScreen(writer, screenId, endScreenX, endScreenY);

			// return the number of screens
			return screenId + 1;
		}

		private void WriteInitFunctionArray(StreamWriter writer, int screenCount)
		{
			// write the array of init function
			writer.WriteLine();
			writer.WriteLine("// The array that contains all the items");
			writer.WriteLine("ItemInitFunction MapManager::ItemInitFunctions[] = {");
			writer.Write("\t");
			for (int i = 0; i < screenCount; ++i)
				writer.Write("&InitScreen" + i.ToString() + ", ");
			writer.WriteLine();
			writer.WriteLine("};");
			writer.WriteLine();

			// write the number of screen
			writer.WriteLine("// compute the number of items");
			writer.WriteLine("const unsigned char MapManager::PUZZLE_SCREEN_COUNT = sizeof(MapManager::ItemInitFunctions) / sizeof(ItemInitFunction);");
		}

		private void WriteProgressInitFunction(StreamWriter writer)
		{
			writer.WriteLine();
			writer.WriteLine("// this function is to init the progress of the living items in eeprom");
			writer.WriteLine("void MapManager::InitProgress()");
			writer.WriteLine("{");

			int instanceCount = 0;
			for (int i = 0; i < mSimilarTypes.Length; ++i)
			{
				// get the max number of instances that we need 
				int maxItemCount = GetMaxItemCount(mSimilarTypes[i]);
				for (int j = 1; j <= maxItemCount; ++j)
					if (Items.Item.WriteProgressInit(writer, mSimilarTypes[i][0], j, instanceCount))
						instanceCount++;
			}

			writer.WriteLine("}");
		}

		public void Save(string fileName)
		{
			StreamWriter writer = new StreamWriter(fileName, false, System.Text.Encoding.UTF8);
			try
			{
				WriteHeader(writer);
				WriteLevelData(writer);
				WriteItemInstances(writer);
				int screenCount = WriteInitFunctions(writer);
				WriteInitFunctionArray(writer, screenCount);
				WriteProgressInitFunction(writer);
			}
			catch (MapSaveException)
			{
			}
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
				for (int t = 0; t < tokens.Length; ++t)
				{
					// get the current token
					string token = tokens[t];
					// check what it is
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
							// special case for the last id of the line, it may be just a padding value
							if ((t < tokens.Length - 1) || ((x % ARDUBOY_PUZZLE_SCREEN_WIDTH) != 0))
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

		private void ReadItemInit(StreamReader reader, string line)
		{
			const string propertyFlagType = "Item::PropertyFlags::";
			const string initFunctionName = ".Init(";
			string instanceName = line.Remove(line.IndexOf(initFunctionName)).Trim();
			string[] tokens = line.Substring(line.IndexOf(initFunctionName) + initFunctionName.Length).Split(new char[] { ',', ')', '|' });

			// declare some boolean variable to store the property flags
			bool isSpecial = false;
			bool isSpecial2 = false;
			bool isMirror = false;

			// parse the two coordinate of the checkpoint respawn
			int intValueIndex = 0;
			int[] intValues = new int[] { 0, 0, 0 };
			foreach (string token in tokens)
			{
				if ((intValueIndex < intValues.Length) && int.TryParse(token, out intValues[intValueIndex]))
				{
					intValueIndex++;
				}
				else if (token.Contains(propertyFlagType))
				{
					isSpecial = token.Contains("SPECIAL");
					isSpecial2 = token.Contains("SPECIAL_2");
					isMirror = token.Contains("MIRROR_X");
				}
			}

			// instantiate the correct item
			try
			{
				AddItem(Items.Item.GetInstanceTypeFromName(instanceName, isSpecial, isSpecial2), isMirror, new Point(intValues[0], intValues[1]));
			}
			catch (MapSaveException)
			{
				// ignore exception for example if there's more than one graal in the Map
			}
		}

		private void ReadCheckpointRespawn(StreamReader reader, string line)
		{
			const string checkpointFunctionName = "MemorizeCheckPoint(";
			string[] tokens = line.Substring(line.IndexOf(checkpointFunctionName) + checkpointFunctionName.Length).Split(new char[] { ',', ')' });

			// parse the two coordinate of the checkpoint respawn
			int coordIndex = 0;
			int[] coord = new int[]{ 0, 0 };
			foreach (string token in tokens)
				if (int.TryParse(token, out coord[coordIndex]))
				{
					coordIndex++;
					if (coordIndex >= coord.Length)
						break;
				}

			// instantiate a RICK item
			AddItem(Items.Item.Type.RICK, false, new Point(coord[0], coord[1]));
		}

		public void Load(string fileName)
		{
			// clear the level
			Reset();
			// and read the cpp file
			StreamReader reader = new StreamReader(fileName, System.Text.Encoding.UTF8);
			while (!reader.EndOfStream)
			{
				string line = reader.ReadLine();
				if (line.Contains("MapManager::Level[]"))
					ReadLevelData(reader);
				else if (line.Contains(".Init("))
					ReadItemInit(reader, line);
				else if (line.Contains("MemorizeCheckPoint"))
					ReadCheckpointRespawn(reader, line);
			}
			reader.Close();

			// set the first rick respawn type
			if (mItems.ContainsKey(Items.Item.Type.RICK))
			{
				List<Items.Item> respawnList = mItems[Items.Item.Type.RICK];
				if (respawnList.Count > 0)
					respawnList[0].RickRespawnType = Items.Item.RespawnType.START;
			}
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
		public void Reset()
		{
			// clear the level
			for (int x = 0; x < LEVEL_WIDTH; ++x)
				for (int y = 0; y < LEVEL_HEIGHT; ++y)
					mLevel[x, y] = (byte)WallId.NOTHING;

			// clear all the items
			mItems.Clear();
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

			// special case for the graal, there can be only one in the Map
			if ((itemType == Items.Item.Type.GRAAL) && (mItems[Items.Item.Type.GRAAL].Count == 1))
				throw new MapSaveException(Properties.Resources.ErrorMapCanOnlyHaveOneGraal, MainForm.LogLevel.WARNING);

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
