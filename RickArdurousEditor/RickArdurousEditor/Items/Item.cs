using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RickArdurousEditor.Items
{
	class Item
	{
		public enum Type
		{
			RICK,
			HORIZONTAL_SPIKE,
			VERTICAL_SPIKE,

			// the type count
			COUNT,
		}

		private static Pen mSelectedPen = new Pen(Color.Yellow, 2);

		// type of the item
		private Type mType = Type.HORIZONTAL_SPIKE;
		private bool mIsMirror = false;

		// coordinate of the Item
		private int mX = 0;
		private int mY = 0;

		// sprite of the item
		Bitmap mSprite = null;

		#region get/set
		public int X
		{
			get { return mX; }
		}

		public int Y
		{
			get { return mY; }
		}

		public Type ItemType
		{
			get { return mType; }
		}
		#endregion

		public Item(Type type, bool isMirrored, int x, int y)
		{
			mType = type;
			mX = x;
			mY = y;
			UpdateSprite();
		}

		#region edition
		private void UpdateSprite()
		{
			switch (mType)
			{
				case Type.HORIZONTAL_SPIKE:
					mSprite = ImageProvider.GetHorizontalSpikeImage();
					break;
				case Type.VERTICAL_SPIKE:
					mSprite = ImageProvider.GetVerticalSpikeImage(mIsMirror);
					break;
				case Type.RICK:
					mSprite = ImageProvider.GetRickImage();
					break;
			}
		}

		public void Mirror()
		{
			mIsMirror = !mIsMirror;
			UpdateSprite();
		}

		public void Move(Point location)
		{
			mX = location.X;
			mY = location.Y;
		}
		#endregion

		#region read/write
		private string GetInstanceName(int instanceNumber)
		{
			string instanceNumberString = instanceNumber.ToString();
			switch (mType)
			{
				case Type.HORIZONTAL_SPIKE:
				case Type.VERTICAL_SPIKE:
					return "spike" + instanceNumberString;
			}
			return string.Empty;
		}

		public void WriteInstance(StreamWriter writer, int instanceNumber)
		{
			string instanceName = GetInstanceName(instanceNumber);
			switch (mType)
			{
				case Type.HORIZONTAL_SPIKE:
					writer.WriteLine("Spike " + instanceName + ";");
					break;
				case Type.VERTICAL_SPIKE:
					if (mIsMirror)
						writer.WriteLine("Spike " + instanceName + ";");
					else
						writer.WriteLine("Spike " + instanceName + ";");
					break;
			}
		}

		public void WriteAddToManager(StreamWriter writer, int instanceNumber)
		{
			if (mType == Type.RICK)
				writer.WriteLine("\tMapManager::MemorizeCheckPoint(" + mX.ToString() + ", " + mY.ToString() + ");");
			else
				writer.WriteLine("\tMapManager::AddItem(&" + GetInstanceName(instanceNumber) + ");");
		}

		public void WriteInitPosition(StreamWriter writer, int instanceNumber)
		{
			switch (mType)
			{
				case Type.HORIZONTAL_SPIKE:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::SPECIAL);");
					break;
				case Type.VERTICAL_SPIKE:
					if (mIsMirror)
						writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::MIRROR_X);");
					else
						writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::NONE);");
					break;
			}
		}
		#endregion

		public bool IsUnder(int x, int y)
		{
			return (x >= mX) && (x < mX + mSprite.Width) && (y >= mY) && (y < mY + mSprite.Height);
		}

		public bool IsInPuzzleScreen(int left, int top, int right, int bottom)
		{
			return (mX >= left) && (mX < right) && (mY >= top) && (mY < bottom);
		}

		public void Draw(Graphics gc, int pixelSize, int cameraXWorld, int cameraYWorld, bool isSelected)
		{
			Rectangle drawArea = new Rectangle((mX - cameraXWorld) * pixelSize, (mY - cameraYWorld) * pixelSize, mSprite.Width * pixelSize, mSprite.Height * pixelSize);
			gc.DrawImage(mSprite, drawArea);
			if (isSelected)
				gc.DrawRectangle(mSelectedPen, drawArea);
		}
	}
}
