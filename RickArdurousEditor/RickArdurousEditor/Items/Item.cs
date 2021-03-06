﻿using System;
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
			BULLET_CRATE,
			DYNAMITE_CRATE,
			STATUETTE,
			GRAAL,
			HORIZONTAL_SPIKE,
			VERTICAL_SPIKE,
			MUMMY,
			SKELETON,
			SCORPION,
			STALAGMITE,
			STALACTITE,
			ARROW_LAUNCHER,
			DESTROYABLE_BLOCK,

			// the type count
			COUNT,
		}

		public enum RespawnType
		{
			NORMAL,
			START,
		}

		private static Pen mSelectedPen = new Pen(Color.Yellow, 2);
		private static Pen mArrowLauncherPen = new Pen(Color.Magenta, 1);

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

		// distance of the arrow launcher
		private int mArrowLauncherDistance = 80;

		#region get/set
		public int X
		{
			get { return mX; }
		}

		public int Y
		{
			get { return mY; }
		}

		public bool IsMirror
		{
			get { return mIsMirror; }
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

		public int SensorDistance
		{
			get { return mArrowLauncherDistance; }
			set { mArrowLauncherDistance = value; }
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
				case Type.BULLET_CRATE:
					mSprite = ImageProvider.GetBulletCrateImage();
					break;
				case Type.DYNAMITE_CRATE:
					mSprite = ImageProvider.GetDynamiteCrateImage();
					break;
				case Type.STATUETTE:
					mSprite = ImageProvider.GetStatuetteImage();
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
				case Type.STALAGMITE:
					mSprite = ImageProvider.GetStalagmiteImage();
					break;
				case Type.STALACTITE:
					mSprite = ImageProvider.GetStalactiteImage();
					break;
				case Type.ARROW_LAUNCHER:
					mSprite = ImageProvider.GetArrowLauncherImage(mIsMirror);
					break;
				case Type.DESTROYABLE_BLOCK:
					mSprite = ImageProvider.GetDestroyableBlockImage();
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
				case Type.BULLET_CRATE:
					return "bulletCrate" + instanceNumberString;
				case Type.DYNAMITE_CRATE:
					return "dynamiteCrate" + instanceNumberString;
				case Type.STATUETTE:
					return "statuette" + instanceNumberString;
				case Type.GRAAL:
					return "graal" + instanceNumberString;
				case Type.HORIZONTAL_SPIKE:
				case Type.VERTICAL_SPIKE:
					return "spike" + instanceNumberString;
				case Type.MUMMY:
				case Type.SKELETON:
				case Type.SCORPION:
					return "enemy" + instanceNumberString;
				case Type.STALAGMITE:
					return "stalagmite" + instanceNumberString;
				case Type.STALACTITE:
					return "stalactite" + instanceNumberString;
				case Type.ARROW_LAUNCHER:
					return "arrowLauncher" + instanceNumberString;
				case Type.DESTROYABLE_BLOCK:
					return "destBlock" + instanceNumberString;
			}
			return string.Empty;
		}

		public static Type GetInstanceTypeFromName(string instanceName, bool isSpecial, bool isSpecial2)
		{
			if (instanceName.StartsWith("bulletCrate"))
				return Type.BULLET_CRATE;
			else if (instanceName.StartsWith("dynamiteCrate"))
				return Type.DYNAMITE_CRATE;
			else if (instanceName.StartsWith("statuette"))
				return Type.STATUETTE;
			else if (instanceName.StartsWith("graal"))
				return Type.GRAAL;
			else if (instanceName.StartsWith("spike"))
				return isSpecial ? Type.HORIZONTAL_SPIKE : Type.VERTICAL_SPIKE;
			else if (instanceName.StartsWith("enemy"))
				return isSpecial ? Type.SCORPION : (isSpecial2 ? Type.SKELETON : Type.MUMMY);
			else if (instanceName.StartsWith("stalagmite"))
				return Type.STALAGMITE;
			else if (instanceName.StartsWith("stalactite"))
				return Type.STALACTITE;
			else if (instanceName.StartsWith("arrowLauncher"))
				return Type.ARROW_LAUNCHER;
			else if (instanceName.StartsWith("destBlock"))
				return Type.DESTROYABLE_BLOCK;

			return Type.HORIZONTAL_SPIKE;
		}

		public static void WriteInstance(StreamWriter writer, Type type, int instanceNumber)
		{
			string instanceName = GetInstanceName(type, instanceNumber);
			switch (type)
			{
				case Type.BULLET_CRATE:
					writer.WriteLine("BulletCrate " + instanceName + ";");
					break;
				case Type.DYNAMITE_CRATE:
					writer.WriteLine("DynamiteCrate " + instanceName + ";");
					break;
				case Type.STATUETTE:
					writer.WriteLine("Statuette " + instanceName + ";");
					break;
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
				case Type.STALAGMITE:
					writer.WriteLine("Stalagmite " + instanceName + ";");
					break;
				case Type.STALACTITE:
					writer.WriteLine("Stalactite " + instanceName + ";");
					break;
				case Type.ARROW_LAUNCHER:
					writer.WriteLine("ArrowLauncher " + instanceName + ";");
					break;
				case Type.DESTROYABLE_BLOCK:
					writer.WriteLine("DestroyableBlock " + instanceName + ";");
					break;
			}
		}

		public static bool WriteSaveAndLoadLivingStatus(StreamWriter writer, Type type, int instanceNumber, int instanceCount)
		{
			string instanceName = GetInstanceName(type, instanceNumber);
			switch (type)
			{
				case Type.BULLET_CRATE:
				case Type.DYNAMITE_CRATE:
				case Type.STATUETTE:
				case Type.GRAAL:
				case Type.MUMMY:
				case Type.SKELETON:
				case Type.SCORPION:
				case Type.STALAGMITE:
				case Type.STALACTITE:
				case Type.DESTROYABLE_BLOCK:
					writer.WriteLine("\t" + instanceName + ".SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);");
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
			string mirrorFlag = mIsMirror ? "Item::PropertyFlags::MIRROR_X" : "Item::PropertyFlags::NONE";
			switch (mType)
			{
				case Type.BULLET_CRATE:
				case Type.DYNAMITE_CRATE:
				case Type.STATUETTE:
				case Type.GRAAL:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::NONE, shouldRespawn);");
					break;
				case Type.HORIZONTAL_SPIKE:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::SPECIAL);");
					break;
				case Type.VERTICAL_SPIKE:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", " + mirrorFlag  + ");");
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
				case Type.STALAGMITE:
				case Type.STALACTITE:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::NONE, shouldRespawn);");
					break;
				case Type.ARROW_LAUNCHER:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", " + mirrorFlag + ", " + mArrowLauncherDistance .ToString() + ");");
					break;
				case Type.DESTROYABLE_BLOCK:
					writer.WriteLine("\t" + GetInstanceName(instanceNumber) + ".Init(" + mX.ToString() + ", " + mY.ToString() + ", Item::PropertyFlags::NONE, shouldRespawn);");
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

		public bool IsCoordOnMySensorExtrimity(Point coord, int mouseSensivity)
		{
			// only the arrow launcher has sensor for now
			if (mType != Type.ARROW_LAUNCHER)
				return false;

			// compute the sensible area around the extrimity of my sensor
			int sensorExtremity = GetSensorExtremity();
			int minX = sensorExtremity - mouseSensivity;
			int maxX = sensorExtremity + mouseSensivity;

			return (coord.X >= minX) && (coord.X <= maxX) && (coord.Y >= mY) && (coord.Y <= mY + mSprite.Height);
		}

		private int GetSensorExtremity()
		{
			return mIsMirror ? mX + mSprite.Width - mArrowLauncherDistance : mX + mArrowLauncherDistance;
		}

		public void Draw(Graphics gc, int pixelSize, int cameraXWorld, int cameraYWorld, bool isSelected)
		{
			Rectangle drawArea = new Rectangle((mX - cameraXWorld) * pixelSize, (mY - cameraYWorld) * pixelSize, mSprite.Width * pixelSize, mSprite.Height * pixelSize);
			gc.DrawImage(mSprite, drawArea);
			if (isSelected)
				gc.DrawRectangle(mSelectedPen, drawArea);

			// special case for the Arrow launcher, draw the sensor area
			if (mType == Type.ARROW_LAUNCHER)
			{
				int x = mIsMirror ? mX + mSprite.Width - mArrowLauncherDistance : mX;
				Rectangle arrowLauncherArea = new Rectangle((x - cameraXWorld) * pixelSize, (mY - cameraYWorld) * pixelSize, mArrowLauncherDistance * pixelSize, mSprite.Height * pixelSize);
				gc.DrawRectangle(mArrowLauncherPen, arrowLauncherArea);
			}
		}
	}
}
