using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;

namespace RickArdurousEditor
{
	class ImageProvider
	{
		private static void SetGCInPixelMode(ref Graphics gc)
		{
			gc.CompositingMode = System.Drawing.Drawing2D.CompositingMode.SourceOver;
			gc.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.Default;
			gc.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			gc.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.None;
			gc.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.None;
		}

		private static void CreateTaintedAndMirroredImage(Bitmap sourceImage, Rectangle sourceRectangle, ref Bitmap resultImage, bool shouldMirror, float red, float green, float blue, Rectangle destinationRectangle = default)
		{
			// is the destination rectangle is empty use the full result image size
			if (destinationRectangle.IsEmpty)
				destinationRectangle = new Rectangle(0, 0, resultImage.Width, resultImage.Height);

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

			// set the color key so that the black becomes transparent
			imageAttributes.SetColorKey(Color.Black, Color.Gray, ColorAdjustType.Bitmap);

			// check if the source rectangle is empty, use the full source image
			if (sourceRectangle.IsEmpty)
				sourceRectangle = new Rectangle(0, 0, sourceImage.Width, sourceImage.Height);

			// paint the image in the mirrored one with the image attribute
			Graphics gc = Graphics.FromImage(resultImage);
			SetGCInPixelMode(ref gc);
			gc.DrawImage(sourceImage,       // source image
				destinationRectangle,  // destination rectangle 
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

		public static Bitmap GetRickImage(Items.Item.RespawnType respawnType)
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"Rick.png");
			Bitmap result = new Bitmap(9, 16);
			float red = 0.1f;
			float green = 0.4f;
			float blue = 1f;
			switch (respawnType)
			{
				case Items.Item.RespawnType.START:
					red = 0f;
					green = 1f;
					blue = 1f;
					break;
			}
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 9, 16), ref result, false, red, green, blue);
			return result;
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

		public static Bitmap GetMummyImage()
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"Mummy.png");
			Bitmap result = new Bitmap(9, 16);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 9, 16), ref result, false, 1f, 1f, 0f);
			return result;
		}

		public static Bitmap GetSkeletonImage()
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"Skeleton.png");
			Bitmap result = new Bitmap(6, 16);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 6, 16), ref result, false, 1f, 1f, 0f);
			return result;
		}

		public static Bitmap GetScorpionImage()
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"Scorpion.png");
			Bitmap result = new Bitmap(8, 4);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 8, 4), ref result, false, 1f, 1f, 0f);
			return result;
		}

		public static Bitmap GetGraalImage()
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"Graal.png");
			Bitmap result = new Bitmap(5, 8);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 5, 8), ref result, false, 0f, 1f, 1f);
			return result;
		}

		public static Bitmap GetStatuetteImage()
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"Statuette.png");
			Bitmap result = new Bitmap(5, 8);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 5, 8), ref result, false, 0f, 1f, 1f);
			return result;
		}

		public static Bitmap GetBulletCrateImage()
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"CrateBullet.png");
			Bitmap result = new Bitmap(11, 8);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 11, 8), ref result, false, 0f, 0.8f, 0.8f);
			return result;
		}

		public static Bitmap GetDynamiteCrateImage()
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"CrateDynamite.png");
			Bitmap result = new Bitmap(11, 8);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 11, 8), ref result, false, 0f, 0.8f, 0.8f);
			return result;
		}

		public static Bitmap GetStalagmiteImage()
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"Stalagmite.png");
			Bitmap result = new Bitmap(7, 8);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 3, 8), ref result, false, 1f, 0.65f, 0.1f, new Rectangle(0, 0, 3, 8));
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 3, 8), ref result, true, 1f, 0.65f, 0.1f, new Rectangle(4, 0, 3, 8));
			return result;
		}

		public static Bitmap GetStalactiteImage()
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"Stalactite.png");
			Bitmap result = new Bitmap(7, 8);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 3, 8), ref result, false, 1f, 0.65f, 0.1f, new Rectangle(0, 0, 3, 8));
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 3, 8), ref result, true, 1f, 0.65f, 0.1f, new Rectangle(4, 0, 3, 8));
			return result;
		}

		public static Bitmap GetArrowLauncherImage(bool isLeft)
		{
			Bitmap sprite = new Bitmap(Application.StartupPath + Properties.Settings.Default.ImageRelativePath + @"ArrowLauncherFace.png");
			Bitmap result = new Bitmap(4, 8);
			CreateTaintedAndMirroredImage(sprite, new Rectangle(0, 0, 4, 8), ref result, isLeft, 1f, 0f, 1f, new Rectangle(0, 0, 3, 8));
			return result;
		}

		public static Bitmap GetItemsSpriteImage()
		{
			// get all the image of all the items
			List<Bitmap> itemImages = new List<Bitmap>();
			itemImages.Add(GetRickImage(Items.Item.RespawnType.NORMAL));
			itemImages.Add(GetBulletCrateImage());
			itemImages.Add(GetDynamiteCrateImage());
			itemImages.Add(GetStatuetteImage());
			itemImages.Add(GetGraalImage());
			itemImages.Add(GetHorizontalSpikeImage());
			itemImages.Add(GetVerticalSpikeImage(false));
			itemImages.Add(GetMummyImage());
			itemImages.Add(GetSkeletonImage());
			itemImages.Add(GetScorpionImage());
			itemImages.Add(GetStalagmiteImage());
			itemImages.Add(GetStalactiteImage());
			itemImages.Add(GetArrowLauncherImage(false));

			// declare the size, and numbers of items in the toolbars
			const int itemRows = 8;
			const int itemColumns = 2;
			const int cellSize = 64;
			Bitmap itemSpriteImage = new Bitmap(cellSize * itemColumns, cellSize * itemRows);
			Graphics gc = Graphics.FromImage(itemSpriteImage);
			SetGCInPixelMode(ref gc);
			gc.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;

			// clear the background
			gc.Clear(Color.Black);

			// decrease the item size to leave a margin
			int margin = 1;
			int itemSize = cellSize - (margin * 2);

			// coordinate of the item to draw
			int itemX = 0;
			int itemY = 0;

			// iterate on all the item images to draw them in the correct cell space
			foreach (Bitmap itemImage in itemImages)
			{
				// get the size of the image and get the biggest one to keep the aspect ratio
				int width = itemSize;
				int height = itemSize;
				if (itemImage.Width < itemImage.Height)
					width = (itemSize * itemImage.Width) / itemImage.Height;
				else if (itemImage.Width > itemImage.Height)
					height = (itemSize * itemImage.Height) / itemImage.Width;

				// draw the image in the correct cell
				gc.DrawImage(itemImage,
					new Rectangle((cellSize * itemX) + ((cellSize - width) / 2), (cellSize * itemY) + ((cellSize - height) / 2), width, height),
					new Rectangle(0, 0, itemImage.Width, itemImage.Height),
					GraphicsUnit.Pixel);

				// increase the item coordinates
				itemY++;
				if (itemY == itemRows)
				{
					itemY = 0;
					itemX++;
				}
			}

			return itemSpriteImage;
		}
	}
}
