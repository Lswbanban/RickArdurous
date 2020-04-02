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
		#region init
		public MainForm()
		{
			InitializeComponent();
			// init the sprite tool box
			InitSpriteToolbox();
		}

		private void InitSpriteToolbox()
		{
			Bitmap originalImage = new Bitmap(Application.StartupPath + @"\..\..\..\..\image\Walls.png");
			Bitmap spritesImage = new Bitmap(PictureBoxSprites.Width, PictureBoxSprites.Height);
			Graphics gc = Graphics.FromImage(spritesImage);
			gc.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			gc.DrawImage(originalImage, 0, 0, spritesImage.Width, spritesImage.Height);

			// create a pen for drawing lines to split the sprites
			Pen linePen = new Pen(Color.Blue, 2);
			gc.DrawLine(linePen, new Point(spritesImage.Width / 2, 0), new Point(spritesImage.Width / 2, spritesImage.Height));
			int height = spritesImage.Height / 8;
			for (int i = 0; i < 8; ++i)
				gc.DrawLine(linePen, new Point(0, height * i), new Point(spritesImage.Width, height * i));

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
	}
}
