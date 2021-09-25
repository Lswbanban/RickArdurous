using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RickArdurousEditor
{
	public partial class MainForm : Form
	{
		private enum EditAction
		{
			MOVE_ITEM,
			ADJUST_SENSOR,
		}

		private Map mMap = new Map();

		// current selection
		private byte mCurrentSelectedSpriteId = 0;
		private Items.Item mCurrentSelectedItem = null;
		private Point mCurrentSelectedItemGrabDelta;

		// the coordinates of the current part of the level which is visible
		private Point mMapCamera;
		private Point mLastMouseDownMapCamera;

		// variable for mouse events
		private EditAction mCurrentEditAction = EditAction.MOVE_ITEM;
		private Point mLastMouseDownPosition;
		private Point mLastMouseMovePosition;

		private Pen mSelectedSpritePen = new Pen(Color.Yellow, 3);

		#region init
		public MainForm()
		{
			InitializeComponent();
			// init the sprite tool box
			RedrawWallSpriteToolbox(0, 0);
			RedrawItemsSpriteToolbox(-1, -1);
			// init the level image
			RedrawLevel();
		}

		private void RedrawWallSpriteToolbox(int selectedSpriteX, int selectedSpriteY)
		{
			Bitmap originalImage = ImageProvider.GetWallSpriteImage();
			Bitmap spritesImage = new Bitmap(PictureBoxWallSprites.Width, PictureBoxWallSprites.Height);
			Graphics gc = Graphics.FromImage(spritesImage);
			gc.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			gc.DrawImage(originalImage, 0, 0, spritesImage.Width, spritesImage.Height);

			// create a pen for drawing lines to split the sprites
			Pen linePen = new Pen(Color.Blue, 2);
			int width = spritesImage.Width / 2;
			int height = spritesImage.Height / 8;
			gc.DrawLine(linePen, new Point(width, 0), new Point(width, spritesImage.Height));
			for (int i = 0; i < 8; ++i)
				gc.DrawLine(linePen, new Point(0, height * i), new Point(spritesImage.Width, height * i));

			// draw the selected sprite
			if (selectedSpriteX >= 0)
				gc.DrawRectangle(mSelectedSpritePen, selectedSpriteX * width, selectedSpriteY * height, width, height);

			// set the strech image in the picture box
			PictureBoxWallSprites.Image = spritesImage;
		}

		private void RedrawItemsSpriteToolbox(int selectedItemX, int selectedItemY)
		{
			Bitmap originalImage = ImageProvider.GetItemsSpriteImage();
			Bitmap spritesImage = new Bitmap(PictureBoxItems.Width, PictureBoxItems.Height);
			Graphics gc = Graphics.FromImage(spritesImage);
			gc.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			gc.DrawImage(originalImage, 0, 0, spritesImage.Width, spritesImage.Height);

			// create a pen for drawing lines to split the sprites
			Pen linePen = new Pen(Color.Blue, 2);
			int width = spritesImage.Width / 2;
			int height = spritesImage.Height / 8;
			gc.DrawLine(linePen, new Point(width, 0), new Point(width, spritesImage.Height));
			for (int i = 0; i < 8; ++i)
				gc.DrawLine(linePen, new Point(0, height * i), new Point(spritesImage.Width, height * i));

			// draw the selected sprite
			if (selectedItemX >= 0)
				gc.DrawRectangle(mSelectedSpritePen, selectedItemX * width, selectedItemY * height, width, height);

			// set the strech image in the picture box
			PictureBoxItems.Image = spritesImage;
		}

		private void RedrawLevel()
		{
			// create image
			if (PictureBoxLevel.Image == null)
				PictureBoxLevel.Image = new Bitmap(PictureBoxLevel.Width, PictureBoxLevel.Height);
			Graphics gc = Graphics.FromImage(PictureBoxLevel.Image);
			// ask the map to redraw it
			mMap.Redraw(gc, PictureBoxLevel.Image.Width, PictureBoxLevel.Image.Height, mMapCamera.X, mMapCamera.Y, mCurrentSelectedItem);
			// and ask to refraw
			PictureBoxLevel.Refresh();
		}

		private void PanLevelCamera(Point newMousePosition)
		{
			Point mouseMove = new Point(mLastMouseDownPosition.X - newMousePosition.X, mLastMouseDownPosition.Y - newMousePosition.Y);
			mMapCamera.X = mLastMouseDownMapCamera.X + (mouseMove.X / mMap.DrawSpriteWidth);
			mMapCamera.Y = mLastMouseDownMapCamera.Y + (mouseMove.Y / mMap.DrawSpriteHeight);
			// clamp the coordinate inside the level
			mMap.ClampCoordinatesInsideLevel(ref mMapCamera);

			// redraw the level
			RedrawLevel();
		}
		#endregion

		#region menu event
		private string getConstVariableFileName(string mapDataFileName)
		{
			FileInfo fileInfo = new FileInfo(mapDataFileName);
			return fileInfo.Name.Remove(fileInfo.Name.IndexOf(fileInfo.Extension)) + "ConstVariables.h";
		}

		private void openToolStripMenuItem_Click(object sender, EventArgs e)
		{
			string folder = Application.StartupPath + Properties.Settings.Default.GameRelativePath;
			string fileToOpen = @"MapData.cpp";
			mMap.Load(folder + fileToOpen);
			RedrawLevel();
		}

		private void saveToolStripMenuItem_Click(object sender, EventArgs e)
		{
			string folder = Application.StartupPath + Properties.Settings.Default.GameRelativePath;
			string fileToSave = @"MapData.cpp";
			mMap.Save(folder + fileToSave, folder + getConstVariableFileName(fileToSave));
		}

		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.Close();
		}
		#endregion

		#region toolbar events
		private void toolStripButtonMirrorItem_Click(object sender, EventArgs e)
		{
			if (mCurrentSelectedItem != null)
			{
				mCurrentSelectedItem.Mirror();
				RedrawLevel();
			}
		}
		private void toolStripButtonDeleteItem_Click(object sender, EventArgs e)
		{
			DeleteCurrentSelectedItem();
		}

		private void toolStripButtonRespawnPointType_Click(object sender, EventArgs e)
		{
			if ((mCurrentSelectedItem != null) && (mCurrentSelectedItem.ItemType == Items.Item.Type.RICK))
			{
				if (mCurrentSelectedItem.RickRespawnType == Items.Item.RespawnType.NORMAL)
					mCurrentSelectedItem.RickRespawnType = Items.Item.RespawnType.START;
				else
					mCurrentSelectedItem.RickRespawnType = Items.Item.RespawnType.NORMAL;
				RedrawLevel();
			}
		}

		private void toolStripButtonShowPuzzlePath_CheckedChanged(object sender, EventArgs e)
		{
			// set the flag on the map
			mMap.IsPuzzlePathDrawn = toolStripButtonShowPuzzlePath.Checked;
			// then redraw the map
			RedrawLevel();
		}
		#endregion

		#region edition event

		private void DeleteCurrentSelectedItem()
		{
			if (mCurrentSelectedItem != null)
			{
				mMap.RemoveItem(mCurrentSelectedItem);
				mCurrentSelectedItem = null;
				RedrawLevel();
			}
		}

		private void PictureBoxSprites_MouseClick(object sender, MouseEventArgs e)
		{
			int spriteX = e.Location.X / (PictureBoxWallSprites.Image.Width / 2);
			int spriteY = e.Location.Y / (PictureBoxWallSprites.Image.Height / 8);
			RedrawWallSpriteToolbox(spriteX, spriteY);
			RedrawItemsSpriteToolbox(-1, -1);
			// memorise the new selected sprite id
			mCurrentSelectedSpriteId = (byte)(spriteY + (8 * spriteX));
		}

		private void PictureBoxItems_MouseClick(object sender, MouseEventArgs e)
		{
			int spriteX = e.Location.X / (PictureBoxItems.Image.Width / 2);
			int spriteY = e.Location.Y / (PictureBoxItems.Image.Height / 8);
			RedrawWallSpriteToolbox(-1, -1);
			RedrawItemsSpriteToolbox(spriteX, spriteY);
			// memorise the new selected sprite id
			mCurrentSelectedSpriteId = (byte)(16 + spriteY + (8 * spriteX));
		}

		private void PictureBoxLevel_SizeChanged(object sender, EventArgs e)
		{
			// delete the image so that a new one can be recreated with the new size
			PictureBoxLevel.Image = null;
			RedrawLevel();
		}

		private void PictureBoxLevel_MouseEnter(object sender, EventArgs e)
		{
			PictureBoxLevel.Focus();
		}

		private Point ConvertMouseCoordToLevelCoord(Point mouseCoord)
		{
			return new Point((mMapCamera.X * Map.WALL_SPRITE_WIDTH) + (mouseCoord.X / mMap.PixelSize), (mMapCamera.Y * Map.WALL_SPRITE_HEIGHT) + (mouseCoord.Y / mMap.PixelSize));
		}

		private void PictureBoxLevel_MouseDown(object sender, MouseEventArgs e)
		{
			mLastMouseDownPosition = e.Location;
			mLastMouseMovePosition = e.Location;
			mLastMouseDownMapCamera = mMapCamera;

			switch (e.Button)
			{
				case MouseButtons.Left:
					Point mouseInLevelCoord = ConvertMouseCoordToLevelCoord(e.Location);

					// check if there is an arrow launcher selected
					if ((mCurrentSelectedItem != null) && (mCurrentSelectedItem.IsCoordOnMySensorExtrimity(mouseInLevelCoord, 2)))
					{
						mCurrentEditAction = EditAction.ADJUST_SENSOR;
					}
					else
					{
						mCurrentEditAction = EditAction.MOVE_ITEM;
						mCurrentSelectedItem = mMap.GetItemAt(mouseInLevelCoord);
						if (mCurrentSelectedItem != null)
							mCurrentSelectedItemGrabDelta = new Point(mCurrentSelectedItem.X - mouseInLevelCoord.X, mCurrentSelectedItem.Y - mouseInLevelCoord.Y);
					}
					break;
			}
		}

		private void PictureBoxLevel_MouseMove(object sender, MouseEventArgs e)
		{
			// change the cursor, if we move hover a sensor
			if ((mCurrentSelectedItem != null) && (mCurrentSelectedItem.IsCoordOnMySensorExtrimity(ConvertMouseCoordToLevelCoord(e.Location), 2)))
				this.Cursor = Cursors.VSplit;
			else
				this.Cursor = Cursors.Default;

			switch (e.Button)
			{
				case MouseButtons.Left:
					if (mCurrentSelectedItem != null)
					{
						Point newLocation = ConvertMouseCoordToLevelCoord(e.Location);
						switch (mCurrentEditAction)
						{
							case EditAction.MOVE_ITEM:
								newLocation.X += mCurrentSelectedItemGrabDelta.X;
								newLocation.Y += mCurrentSelectedItemGrabDelta.Y;
								mCurrentSelectedItem.Move(newLocation);
								break;
							case EditAction.ADJUST_SENSOR:
								Point mouseDownInLevelCoord = ConvertMouseCoordToLevelCoord(mLastMouseMovePosition);
								int diff = newLocation.X - mouseDownInLevelCoord.X;
								if (mCurrentSelectedItem.IsMirror)
									mCurrentSelectedItem.SensorDistance -= diff;
								else
									mCurrentSelectedItem.SensorDistance += diff;
								break;
						}
						RedrawLevel();
					}
					break;
				case MouseButtons.Middle:
					PanLevelCamera(e.Location);
					break;
			}
			mLastMouseMovePosition = e.Location;
		}

		private void PictureBoxLevel_MouseUp(object sender, MouseEventArgs e)
		{
			switch (e.Button)
			{
				case MouseButtons.Left:
					try
					{
						if (mCurrentSelectedSpriteId >= 16)
						{
							if (mCurrentSelectedItem == null)
							{
								mCurrentSelectedItem = mMap.AddItem((Items.Item.Type)(mCurrentSelectedSpriteId - 16), false, ConvertMouseCoordToLevelCoord(e.Location));								
							}
							else if (mCurrentEditAction == EditAction.ADJUST_SENSOR)
							{
								Point mouseDownInLevelCoord = ConvertMouseCoordToLevelCoord(mLastMouseMovePosition);
								Point newLocation = ConvertMouseCoordToLevelCoord(e.Location);
								int diff = newLocation.X - mouseDownInLevelCoord.X;
								if (mCurrentSelectedItem.IsMirror)
									mCurrentSelectedItem.SensorDistance -= diff;
								else
									mCurrentSelectedItem.SensorDistance += diff;
							}
						}
					}
					catch (MapSaveException)
					{
					}
					RedrawLevel();
					break;

				case MouseButtons.Middle:
					PanLevelCamera(e.Location);
					break;

				case MouseButtons.Right:
					if (mCurrentSelectedSpriteId < 16)
						mMap.SetSpriteId(mMap.GetSpriteCoordFromScreenCoord(mMapCamera, e.Location), mCurrentSelectedSpriteId);
					RedrawLevel();
					break;
			}
		}

		private void PictureBoxLevel_MouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			int spriteSizeChange = (e.Delta / 100);
			mMap.PixelSize = mMap.PixelSize + spriteSizeChange;
			RedrawLevel();
		}

		private void MainForm_KeyUp(object sender, KeyEventArgs e)
		{
			if ((mCurrentSelectedItem != null) && ((e.KeyCode == Keys.Delete) || (e.KeyCode == Keys.Back)))
				DeleteCurrentSelectedItem();
		}
		#endregion

		#region Log

		public enum LogLevel
		{
			NORMAL,
			GOOD,
			WARNING,
			ERROR,
		}

		public static void LogMessage(string message, LogLevel level)
		{
			// get the main form
			MainForm mainForm = Application.OpenForms[0] as MainForm;
			// add the message in the list of string
			List<string> existingMessages = new List<string>(mainForm.textBoxLog.Lines);
			existingMessages.Add(message);
			mainForm.textBoxLog.Lines = existingMessages.ToArray();
		}
		#endregion
	}
}
