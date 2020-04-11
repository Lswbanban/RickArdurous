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
			HORIZONTAL_SPIKE,
			VERTICAL_SPIKE,

			RICK = 255,
		}

		private static Pen mSelectedPen = new Pen(Color.Yellow, 2);

		// type of the item
		private Type mType = Type.HORIZONTAL_SPIKE;
		private bool mIsMirror = false;

		// coordinate of the Item
		private int mX = 0;
		private int mY = 0;

		// unique id used during the export of the map
		private readonly int mId = 0;

		// sprite of the item
		Bitmap mSprite = null;

		public Type ItemType
		{
			get { return mType; }
		}

		public Item(Type type, int uniqueId, bool isMirrored, int x, int y)
		{
			mType = type;
			mId = uniqueId;
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
		private string GetInstanceName()
		{
			string instanceNumberString = mId.ToString();
			switch (mType)
			{
				case Type.HORIZONTAL_SPIKE:
				case Type.VERTICAL_SPIKE:
					return "spike" + instanceNumberString;
			}
			return string.Empty;
		}

		public void WriteInstance(StreamWriter writer)
		{
			string instanceName = GetInstanceName();
			switch (mType)
			{
				case Type.HORIZONTAL_SPIKE:
					writer.WriteLine("Spike " + instanceName + "(Item::PropertyFlags::NONE);");
					break;
				case Type.VERTICAL_SPIKE:
					if (mIsMirror)
						writer.WriteLine("Spike " + instanceName + "(Item::PropertyFlags::SPECIAL | Item::PropertyFlags::MIRROR_X);");
					else
						writer.WriteLine("Spike " + instanceName + "(Item::PropertyFlags::SPECIAL);");
					break;
			}
		}

		public void WriteAddToManager(StreamWriter writer)
		{
			if (mType == Type.RICK)
				writer.WriteLine("\tMapManager::MemorizeCheckPoint(" + mX.ToString() + ", " + mY.ToString() + ");");
			else
				writer.WriteLine("\tMapManager::AddItem(&" + GetInstanceName() + ");");
		}

		public void WriteInitPosition(StreamWriter writer)
		{
			if (mType != Type.RICK)
				writer.WriteLine("\t" + GetInstanceName() + ".Init(" + mX.ToString() + ", " + mY.ToString() + ");");
		}
		#endregion

		public bool IsUnder(int x, int y)
		{
			return (x >= mX) && (x < mX + mSprite.Width) && (y >= mY) && (y < mY + mSprite.Height);
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
