using System;
using System.Collections.Generic;
using System.Drawing;
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
		}

		// type of the item
		private Type mType = Type.HORIZONTAL_SPIKE;

		// coordinate of the Item
		private int mX = 0;
		private int mY = 0;

		// sprite of the item
		Bitmap mSprite = null;

		public Item(Type type, bool isMirrored, int x, int y)
		{
			mType = type;
			mX = x;
			mY = y;
			UpdateSprite(isMirrored);
		}

		private void UpdateSprite(bool isMirrored)
		{
			switch (mType)
			{
				case Type.HORIZONTAL_SPIKE:
					mSprite = ImageProvider.GetHorizontalSpikeImage(isMirrored);
					break;
				case Type.VERTICAL_SPIKE:
					mSprite = ImageProvider.GetVerticalSpikeImage(isMirrored);
					break;
			}
		}

		public void Draw(Graphics gc, int pixelSize)
		{
			gc.DrawImage(mSprite, mX * pixelSize, mY * pixelSize, mSprite.Width * pixelSize, mSprite.Height * pixelSize);
		}
	}
}
