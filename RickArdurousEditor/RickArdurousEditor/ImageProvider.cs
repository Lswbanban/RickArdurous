using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;

namespace RickArdurousEditor
{
	class ImageProvider
	{
		private static void SetGCInPixelMode(ref Graphics gc)
		{
			gc.CompositingMode = System.Drawing.Drawing2D.CompositingMode.SourceCopy;
			gc.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.Default;
			gc.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			gc.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.None;
			gc.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;
		}

		private static void CreateTaintedAndMirroredImage(Bitmap sourceImage, Rectangle sourceRectangle, ref Bitmap resultImage, bool shouldMirror, float red, float green, float blue)
		{
			// Create some image attribut to change the color of the mirrored image
			ImageAttributes imageAttributes = new ImageAttributes();
			float[][] colorMatrixElements = {
			   new float[] {red,  0,  0,  0, 0},     // red scaling factor
			   new float[] {0,  green,  0,  0, 0},     // green scaling factor
			   new float[] {0,  0,  blue,  0, 0},     // blue scaling factor
			   new float[] {0,  0,  0,  1, 0},     // alpha scaling factor of 1
			   new float[] {0,  0,  0,  0, 1}};    // translations
			ColorMatrix colorMatrix = new ColorMatrix(colorMatrixElements);
			imageAttributes.SetColorMatrix(colorMatrix, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);

			// check if the source rectangle is empty, use the full source image
			if (sourceRectangle.IsEmpty)
				sourceRectangle = new Rectangle(0, 0, sourceImage.Width, sourceImage.Height);

			// paint the image in the mirrored one with the image attribute
			Graphics gc = Graphics.FromImage(resultImage);
			SetGCInPixelMode(ref gc);
			gc.DrawImage(sourceImage,       // source image
				new Rectangle(0, 0, resultImage.Width, resultImage.Height),  // destination rectangle 
				sourceRectangle.X,
				sourceRectangle.Y,          // upper-left corner of source rectangle 
				sourceRectangle.Width,      // width of source rectangle
				sourceRectangle.Height,     // height of source rectangle
				GraphicsUnit.Pixel,
				imageAttributes);

			// and mirror it if needed
			if (shouldMirror)
				resultImage.RotateFlip(RotateFlipType.RotateNoneFlipX);
		}


		public static Bitmap GetWallSpriteImage()
		{
			return new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"Walls.png");
		}

		public static Bitmap GetHorizontalSpikeImage()
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"SpikeHorizontal.png");
			Bitmap result = new Bitmap(3, 8);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 3, 8), ref result, false, 1f, 0f, 0f);
			return result;
		}

		public static Bitmap GetVerticalSpikeImage(bool isLeft)
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"SpikeVertical.png");
			Bitmap result = new Bitmap(4, 8);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 4, 8), ref result, isLeft, 1f, 0f, 0f);
			return result;
		}

		public static Bitmap GetItemsSpriteImage()
		{
			int itemSize = 16;
			Bitmap itemSpriteImage = new Bitmap(itemSize * 2, itemSize * 8);
			Graphics gc = Graphics.FromImage(itemSpriteImage);
			SetGCInPixelMode(ref gc);

			// clear the background
			gc.Clear(Color.Black);

			// decrease the item size to leave a margin
			itemSize -= 2;

			// draw all the items in a grid
			gc.DrawImage(GetHorizontalSpikeImage(), 0, 0, itemSize, itemSize);
			gc.DrawImage(GetVerticalSpikeImage(false), 0, itemSize, itemSize, itemSize);

			return itemSpriteImage;
		}
	}
}
