using System.Collections.Generic;

namespace RickArdurousEditor.Action
{
	public class ActionManager
	{
		List<Action> mDoneActions = new List<Action>();
		List<Action> mUndoneActions = new List<Action>();

		public void Do(Action action)
		{
			mUndoneActions.Clear();
			mDoneActions.Add(action);
			action.Redo();
		}

		public void Redo()
		{
			if (mUndoneActions.Count > 0)
			{
				Action action = mUndoneActions[mUndoneActions.Count - 1];
				action.Redo();
				mDoneActions.Add(action);
				mUndoneActions.RemoveAt(mUndoneActions.Count - 1);
			}
		}

		public void Undo()
		{
			if (mDoneActions.Count > 0)
			{
				Action action = mDoneActions[mDoneActions.Count - 1];
				action.Undo();
				mUndoneActions.Add(action);
				mDoneActions.RemoveAt(mDoneActions.Count - 1);
			}
		}

		public bool CanUndo()
		{
			return mDoneActions.Count > 0;
		}

		public bool CanRedo()
		{
			return mUndoneActions.Count > 0;
		}
	}
}
