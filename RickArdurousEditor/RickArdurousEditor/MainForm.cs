using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RickArdurousEditor
{
	public partial class MainForm : Form
	{
		private int mCurrentSelectedSpriteId = 0;

		#region init
		public MainForm()
		{
			InitializeComponent();
			// init the sprite tool box
			redrawSpriteToolbox(0,0);
		}

		private void redrawSpriteToolbox(int selectedSpriteX, int selectedSpriteY)
		{
			Bitmap originalImage = new Bitmap(Application.StartupPath + @"\..\..\..\..\image\Walls.png");
			Bitmap spritesImage = new Bitmap(PictureBoxSprites.Width, PictureBoxSprites.Height);
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
			Pen selectedSpritePen = new Pen(Color.Red, 3);
			gc.DrawRectangle(selectedSpritePen, selectedSpriteX * width, selectedSpriteY * height, width, height);

			// set the strech image in the picture box
			PictureBoxSprites.Image = spritesImage;
		}
		#endregion

		#region menu event
		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.Close();
		}
		#endregion

		#region edition event
		private void PictureBoxSprites_MouseClick(object sender, MouseEventArgs e)
		{
			int spriteX = e.Location.X / (PictureBoxSprites.Image.Width / 2);
			int spriteY = e.Location.Y / (PictureBoxSprites.Image.Height / 8);
			redrawSpriteToolbox(spriteX, spriteY);
			// memorise the new selected sprite id
			mCurrentSelectedSpriteId = spriteY + (8 * spriteX);
		}
		#endregion
	}
}
