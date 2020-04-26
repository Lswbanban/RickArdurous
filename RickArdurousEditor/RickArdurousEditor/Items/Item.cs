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
			GRAAL,
			HORIZONTAL_SPIKE,
			VERTICAL_SPIKE,
			MUMMY,
			SKELETON,
			SCORPION,

			// the type count
			COUNT,
		}

		public enum RespawnType
		{
			NORMAL,
			START,
		}

		private static Pen mSelectedPen = new Pen(Color.Yellow, 2);

		// type of the item
		private Type mType = Type.HORIZONTAL_SPIKE;
		private bool mIsMirror = false;

		// two special flags for the Rick type of Item that can identify the first and last puzzle screen
		private RespawnType mRickRespawnType = RespawnType.NORMAL;

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

		public RespawnType RickRespawnType
		{
			get { return mRickRespawnType; }
			set
			{
				mRickRespawnType = value;
				UpdateSprite();
			}
		}
		#endregion

		public Item(Type type, bool isMirrored, int x, int y)
		{
			mType = type;
			mX = x;
			mY = y;
			mIsMirror = isMirrored;
			UpdateSprite();
		}

		#region edition
		private void UpdateSprite()
		{
			switch (mType)
			{
				case Type.RICK:
					mSprite = ImageProvider.GetRickImage(mRickRespawnType);
					break;
				case Type.GRAAL:
					mSprite = ImageProvider.GetGraalImage();
					break;
				case Type.HORIZONTAL_SPIKE:
					mSprite = ImageProvider.GetHorizontalSpikeImage();
					break;
				case Type.VERTICAL_SPIKE:
					mSprite = ImageProvider.GetVerticalSpikeImage(mIsMirror);
					break;
				case Type.MUMMY:
					mSprite = ImageProvider.GetMummyImage();
					break;
				case Type.SKELETON:
					mSprite = ImageProvider.GetSkeletonImage();
					break;
				case Type.SCORPION:
					mSprite = ImageProvider.GetScorpionImage();
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
			return GetInstanceName(mType, instanceNumber);
		}

		private static string GetInstanceName(Type type, int instanceNumber)
		{
			string instanceNumberString = instanceNumber.ToString();
			switch (type)
			{
				case Type.GRAAL:
					return "graal" + instanceNumberString;
				case Type.HORIZONTAL_SPIKE:
				case Type.VERTICAL_SPIKE:
					return "spike" + instanceNumberString;
				case Type.MUMMY:
				case Type.SKELETON:
				case Type.SCORPION:
					return "enemy" + instanceNumberString;
			}
			return string.Empty;
		}

		public static Type GetInstanceTypeFromName(string instanceName, bool isSpecial, bool isSpecial2)
		{
			if (instanceName.StartsWith("graal"))
				return Type.GRAAL;
			else if (instanceName.StartsWith("spike"))
				return isSpecial ? Type.HORIZONTAL_SPIKE : Type.VERTICAL_SPIKE;
			else if (instanceName.StartsWith("enemy"))
				return isSpecial ? Type.SCORPION : (isSpecial2 ? Type.SKELETON : Type.MUMMY);

			return Type.HORIZONTAL_SPIKE;
		}

		public static void WriteInstance(StreamWriter writer, Type type, int instanceNumber)
		{
			string instanceName = GetInstanceName(type, instanceNumber);
			switch (type)
			{
				case Type.GRAAL:
					writer.WriteLine("Graal " + instanceName + ";");
					break;
				case Type.HORIZONTAL_SPIKE:
				case Type.VERTICAL_SPIKE:
					writer.WriteLine("Spike " + instanceName + ";");
					break;
				case Type.MUMMY:
				case Type.SKELETON:
				case Type.SCORPION:
					writer.WriteLine("Enemy " + instanceName + ";");
					break;
			}
		}

		public static bool WriteProgressInit(StreamWriter writer, Type type, int instanceNumber, int instanceCount)
		{
			string instanceName = GetInstanceName(type, instanceNumber);
			switch (type)
			{
				case Type.GRAAL:
				case Type.MUMMY:
				case Type.SKELETON:
				case Type.SCORPION:
					writer.WriteLine("\tProgress::InitItem(&" + instanceName + ", " + instanceCount.ToString() + ");");
					return true;
			}
			return false;
		}

		public void WriteCheckpoint(StreamWriter writer, int instanceNumber)
		{
			if (mType == Type.RICK)
				writer.WriteLine("\tMapManager::MemorizeCheckPoint(" + mX.ToString() + ", " + mY.ToString() + ");");
		}

		public void WriteInit(StreamWriter writer, int instanceNumber)
		{
			switch (mType)
			{
				case Type.GRAAL:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::NONE, shouldRespawn);");
					break;
				case Type.HORIZONTAL_SPIKE:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::SPECIAL);");
					break;
				case Type.VERTICAL_SPIKE:
					if (mIsMirror)
						writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::MIRROR_X);");
					else
						writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::NONE);");
					break;
				case Type.MUMMY:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::NONE, shouldRespawn);");
					break;
				case Type.SKELETON:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::SPECIAL_2, shouldRespawn);");
					break;
				case Type.SCORPION:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::SPECIAL, shouldRespawn);");
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
