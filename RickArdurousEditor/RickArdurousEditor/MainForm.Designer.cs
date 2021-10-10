namespace RickArdurousEditor
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.ToolBar = new System.Windows.Forms.ToolStrip();
			this.toolStripButtonMirrorItem = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonDeleteItem = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonRespawnPointType = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonShowPuzzlePath = new System.Windows.Forms.ToolStripButton();
			this.SplitContainerToolAndLevel = new System.Windows.Forms.SplitContainer();
			this.SplitContainerWallAndItems = new System.Windows.Forms.SplitContainer();
			this.PictureBoxWallSprites = new System.Windows.Forms.PictureBox();
			this.PictureBoxItems = new System.Windows.Forms.PictureBox();
			this.splitContainerMapAndLogWindow = new System.Windows.Forms.SplitContainer();
			this.PictureBoxLevel = new System.Windows.Forms.PictureBox();
			this.textBoxLog = new System.Windows.Forms.TextBox();
			this.contextMenuStripLogWindow = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.toolStripMenuItemClear = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItemCopyToClipboard = new System.Windows.Forms.ToolStripMenuItem();
			this.MenuStripMain = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.undoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.redoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.ToolBar.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.SplitContainerToolAndLevel)).BeginInit();
			this.SplitContainerToolAndLevel.Panel1.SuspendLayout();
			this.SplitContainerToolAndLevel.Panel2.SuspendLayout();
			this.SplitContainerToolAndLevel.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.SplitContainerWallAndItems)).BeginInit();
			this.SplitContainerWallAndItems.Panel1.SuspendLayout();
			this.SplitContainerWallAndItems.Panel2.SuspendLayout();
			this.SplitContainerWallAndItems.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.PictureBoxWallSprites)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.PictureBoxItems)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.splitContainerMapAndLogWindow)).BeginInit();
			this.splitContainerMapAndLogWindow.Panel1.SuspendLayout();
			this.splitContainerMapAndLogWindow.Panel2.SuspendLayout();
			this.splitContainerMapAndLogWindow.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.PictureBoxLevel)).BeginInit();
			this.contextMenuStripLogWindow.SuspendLayout();
			this.MenuStripMain.SuspendLayout();
			this.SuspendLayout();
			// 
			// ToolBar
			// 
			this.ToolBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButtonMirrorItem,
            this.toolStripButtonDeleteItem,
            this.toolStripButtonRespawnPointType,
            this.toolStripButtonShowPuzzlePath});
			this.ToolBar.Location = new System.Drawing.Point(0, 24);
			this.ToolBar.Name = "ToolBar";
			this.ToolBar.Size = new System.Drawing.Size(800, 25);
			this.ToolBar.TabIndex = 0;
			this.ToolBar.Text = "toolStrip1";
			// 
			// toolStripButtonMirrorItem
			// 
			this.toolStripButtonMirrorItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonMirrorItem.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonMirrorItem.Image")));
			this.toolStripButtonMirrorItem.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonMirrorItem.Name = "toolStripButtonMirrorItem";
			this.toolStripButtonMirrorItem.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonMirrorItem.Text = "Mirror";
			this.toolStripButtonMirrorItem.Click += new System.EventHandler(this.toolStripButtonMirrorItem_Click);
			// 
			// toolStripButtonDeleteItem
			// 
			this.toolStripButtonDeleteItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonDeleteItem.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonDeleteItem.Image")));
			this.toolStripButtonDeleteItem.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonDeleteItem.Name = "toolStripButtonDeleteItem";
			this.toolStripButtonDeleteItem.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonDeleteItem.Click += new System.EventHandler(this.toolStripButtonDeleteItem_Click);
			// 
			// toolStripButtonRespawnPointType
			// 
			this.toolStripButtonRespawnPointType.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonRespawnPointType.Image = global::RickArdurousEditor.Properties.Resources.RespawnPointType;
			this.toolStripButtonRespawnPointType.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonRespawnPointType.Name = "toolStripButtonRespawnPointType";
			this.toolStripButtonRespawnPointType.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonRespawnPointType.Text = "toolStripButton1";
			this.toolStripButtonRespawnPointType.Click += new System.EventHandler(this.toolStripButtonRespawnPointType_Click);
			// 
			// toolStripButtonShowPuzzlePath
			// 
			this.toolStripButtonShowPuzzlePath.CheckOnClick = true;
			this.toolStripButtonShowPuzzlePath.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonShowPuzzlePath.Image = global::RickArdurousEditor.Properties.Resources.PuzzlePathIcon;
			this.toolStripButtonShowPuzzlePath.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonShowPuzzlePath.Name = "toolStripButtonShowPuzzlePath";
			this.toolStripButtonShowPuzzlePath.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonShowPuzzlePath.Text = "toolStripButton1";
			this.toolStripButtonShowPuzzlePath.CheckedChanged += new System.EventHandler(this.toolStripButtonShowPuzzlePath_CheckedChanged);
			// 
			// SplitContainerToolAndLevel
			// 
			this.SplitContainerToolAndLevel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.SplitContainerToolAndLevel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.SplitContainerToolAndLevel.Location = new System.Drawing.Point(0, 49);
			this.SplitContainerToolAndLevel.Name = "SplitContainerToolAndLevel";
			// 
			// SplitContainerToolAndLevel.Panel1
			// 
			this.SplitContainerToolAndLevel.Panel1.Controls.Add(this.SplitContainerWallAndItems);
			// 
			// SplitContainerToolAndLevel.Panel2
			// 
			this.SplitContainerToolAndLevel.Panel2.Controls.Add(this.splitContainerMapAndLogWindow);
			this.SplitContainerToolAndLevel.Size = new System.Drawing.Size(800, 401);
			this.SplitContainerToolAndLevel.SplitterDistance = 95;
			this.SplitContainerToolAndLevel.TabIndex = 1;
			// 
			// SplitContainerWallAndItems
			// 
			this.SplitContainerWallAndItems.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.SplitContainerWallAndItems.Dock = System.Windows.Forms.DockStyle.Fill;
			this.SplitContainerWallAndItems.Location = new System.Drawing.Point(0, 0);
			this.SplitContainerWallAndItems.Name = "SplitContainerWallAndItems";
			this.SplitContainerWallAndItems.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// SplitContainerWallAndItems.Panel1
			// 
			this.SplitContainerWallAndItems.Panel1.Controls.Add(this.PictureBoxWallSprites);
			// 
			// SplitContainerWallAndItems.Panel2
			// 
			this.SplitContainerWallAndItems.Panel2.Controls.Add(this.PictureBoxItems);
			this.SplitContainerWallAndItems.Size = new System.Drawing.Size(95, 401);
			this.SplitContainerWallAndItems.SplitterDistance = 255;
			this.SplitContainerWallAndItems.TabIndex = 1;
			// 
			// PictureBoxWallSprites
			// 
			this.PictureBoxWallSprites.Dock = System.Windows.Forms.DockStyle.Fill;
			this.PictureBoxWallSprites.Location = new System.Drawing.Point(0, 0);
			this.PictureBoxWallSprites.Name = "PictureBoxWallSprites";
			this.PictureBoxWallSprites.Size = new System.Drawing.Size(91, 251);
			this.PictureBoxWallSprites.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.PictureBoxWallSprites.TabIndex = 0;
			this.PictureBoxWallSprites.TabStop = false;
			this.PictureBoxWallSprites.MouseClick += new System.Windows.Forms.MouseEventHandler(this.PictureBoxSprites_MouseClick);
			// 
			// PictureBoxItems
			// 
			this.PictureBoxItems.Dock = System.Windows.Forms.DockStyle.Fill;
			this.PictureBoxItems.Location = new System.Drawing.Point(0, 0);
			this.PictureBoxItems.Name = "PictureBoxItems";
			this.PictureBoxItems.Size = new System.Drawing.Size(91, 138);
			this.PictureBoxItems.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.PictureBoxItems.TabIndex = 0;
			this.PictureBoxItems.TabStop = false;
			this.PictureBoxItems.MouseClick += new System.Windows.Forms.MouseEventHandler(this.PictureBoxItems_MouseClick);
			// 
			// splitContainerMapAndLogWindow
			// 
			this.splitContainerMapAndLogWindow.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.splitContainerMapAndLogWindow.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainerMapAndLogWindow.Location = new System.Drawing.Point(0, 0);
			this.splitContainerMapAndLogWindow.Name = "splitContainerMapAndLogWindow";
			this.splitContainerMapAndLogWindow.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// splitContainerMapAndLogWindow.Panel1
			// 
			this.splitContainerMapAndLogWindow.Panel1.Controls.Add(this.PictureBoxLevel);
			// 
			// splitContainerMapAndLogWindow.Panel2
			// 
			this.splitContainerMapAndLogWindow.Panel2.Controls.Add(this.textBoxLog);
			this.splitContainerMapAndLogWindow.Size = new System.Drawing.Size(701, 401);
			this.splitContainerMapAndLogWindow.SplitterDistance = 308;
			this.splitContainerMapAndLogWindow.TabIndex = 1;
			// 
			// PictureBoxLevel
			// 
			this.PictureBoxLevel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.PictureBoxLevel.Location = new System.Drawing.Point(0, 0);
			this.PictureBoxLevel.Name = "PictureBoxLevel";
			this.PictureBoxLevel.Size = new System.Drawing.Size(697, 304);
			this.PictureBoxLevel.TabIndex = 0;
			this.PictureBoxLevel.TabStop = false;
			this.PictureBoxLevel.SizeChanged += new System.EventHandler(this.PictureBoxLevel_SizeChanged);
			this.PictureBoxLevel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PictureBoxLevel_MouseDown);
			this.PictureBoxLevel.MouseEnter += new System.EventHandler(this.PictureBoxLevel_MouseEnter);
			this.PictureBoxLevel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.PictureBoxLevel_MouseMove);
			this.PictureBoxLevel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.PictureBoxLevel_MouseUp);
			this.PictureBoxLevel.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.PictureBoxLevel_MouseWheel);
			// 
			// textBoxLog
			// 
			this.textBoxLog.ContextMenuStrip = this.contextMenuStripLogWindow;
			this.textBoxLog.Dock = System.Windows.Forms.DockStyle.Fill;
			this.textBoxLog.Location = new System.Drawing.Point(0, 0);
			this.textBoxLog.Multiline = true;
			this.textBoxLog.Name = "textBoxLog";
			this.textBoxLog.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.textBoxLog.Size = new System.Drawing.Size(697, 85);
			this.textBoxLog.TabIndex = 0;
			// 
			// contextMenuStripLogWindow
			// 
			this.contextMenuStripLogWindow.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItemClear,
            this.toolStripMenuItemCopyToClipboard});
			this.contextMenuStripLogWindow.Name = "contextMenuStripLogWindow";
			this.contextMenuStripLogWindow.Size = new System.Drawing.Size(172, 48);
			this.contextMenuStripLogWindow.Text = "Clear";
			// 
			// toolStripMenuItemClear
			// 
			this.toolStripMenuItemClear.Name = "toolStripMenuItemClear";
			this.toolStripMenuItemClear.Size = new System.Drawing.Size(171, 22);
			this.toolStripMenuItemClear.Text = "Clear";
			this.toolStripMenuItemClear.Click += new System.EventHandler(this.toolStripMenuItemClear_Click);
			// 
			// toolStripMenuItemCopyToClipboard
			// 
			this.toolStripMenuItemCopyToClipboard.Name = "toolStripMenuItemCopyToClipboard";
			this.toolStripMenuItemCopyToClipboard.Size = new System.Drawing.Size(171, 22);
			this.toolStripMenuItemCopyToClipboard.Text = "Copy to Clipboard";
			this.toolStripMenuItemCopyToClipboard.Click += new System.EventHandler(this.toolStripMenuItemCopyToClipboard_Click);
			// 
			// MenuStripMain
			// 
			this.MenuStripMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem});
			this.MenuStripMain.Location = new System.Drawing.Point(0, 0);
			this.MenuStripMain.Name = "MenuStripMain";
			this.MenuStripMain.Size = new System.Drawing.Size(800, 24);
			this.MenuStripMain.TabIndex = 2;
			// 
			// fileToolStripMenuItem
			// 
			this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem});
			this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
			this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
			this.fileToolStripMenuItem.Text = "File";
			// 
			// openToolStripMenuItem
			// 
			this.openToolStripMenuItem.Name = "openToolStripMenuItem";
			this.openToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.openToolStripMenuItem.Text = "Open";
			this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
			this.saveToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.saveToolStripMenuItem.Text = "Save";
			this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(177, 6);
			// 
			// exitToolStripMenuItem
			// 
			this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
			this.exitToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.exitToolStripMenuItem.Text = "Exit";
			this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.undoToolStripMenuItem,
            this.redoToolStripMenuItem});
			this.editToolStripMenuItem.Name = "editToolStripMenuItem";
			this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
			this.editToolStripMenuItem.Text = "Edit";
			// 
			// undoToolStripMenuItem
			// 
			this.undoToolStripMenuItem.Name = "undoToolStripMenuItem";
			this.undoToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.undoToolStripMenuItem.Text = "Undo";
			this.undoToolStripMenuItem.Click += new System.EventHandler(this.undoToolStripMenuItem_Click);
			// 
			// redoToolStripMenuItem
			// 
			this.redoToolStripMenuItem.Name = "redoToolStripMenuItem";
			this.redoToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.redoToolStripMenuItem.Text = "Redo";
			this.redoToolStripMenuItem.Click += new System.EventHandler(this.redoToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.SplitContainerToolAndLevel);
			this.Controls.Add(this.ToolBar);
			this.Controls.Add(this.MenuStripMain);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.KeyPreview = true;
			this.MainMenuStrip = this.MenuStripMain;
			this.Name = "MainForm";
			this.Text = "Rick Ardurous Editor";
			this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.MainForm_KeyUp);
			this.ToolBar.ResumeLayout(false);
			this.ToolBar.PerformLayout();
			this.SplitContainerToolAndLevel.Panel1.ResumeLayout(false);
			this.SplitContainerToolAndLevel.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.SplitContainerToolAndLevel)).EndInit();
			this.SplitContainerToolAndLevel.ResumeLayout(false);
			this.SplitContainerWallAndItems.Panel1.ResumeLayout(false);
			this.SplitContainerWallAndItems.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.SplitContainerWallAndItems)).EndInit();
			this.SplitContainerWallAndItems.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.PictureBoxWallSprites)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.PictureBoxItems)).EndInit();
			this.splitContainerMapAndLogWindow.Panel1.ResumeLayout(false);
			this.splitContainerMapAndLogWindow.Panel2.ResumeLayout(false);
			this.splitContainerMapAndLogWindow.Panel2.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainerMapAndLogWindow)).EndInit();
			this.splitContainerMapAndLogWindow.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.PictureBoxLevel)).EndInit();
			this.contextMenuStripLogWindow.ResumeLayout(false);
			this.MenuStripMain.ResumeLayout(false);
			this.MenuStripMain.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ToolStrip ToolBar;
		private System.Windows.Forms.SplitContainer SplitContainerToolAndLevel;
		private System.Windows.Forms.PictureBox PictureBoxWallSprites;
		private System.Windows.Forms.PictureBox PictureBoxLevel;
		private System.Windows.Forms.MenuStrip MenuStripMain;
		private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
		private System.Windows.Forms.SplitContainer SplitContainerWallAndItems;
		private System.Windows.Forms.PictureBox PictureBoxItems;
		private System.Windows.Forms.ToolStripButton toolStripButtonMirrorItem;
		private System.Windows.Forms.ToolStripButton toolStripButtonDeleteItem;
		private System.Windows.Forms.ToolStripButton toolStripButtonRespawnPointType;
		private System.Windows.Forms.SplitContainer splitContainerMapAndLogWindow;
		private System.Windows.Forms.TextBox textBoxLog;
		private System.Windows.Forms.ToolStripButton toolStripButtonShowPuzzlePath;
		private System.Windows.Forms.ContextMenuStrip contextMenuStripLogWindow;
		private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemClear;
		private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemCopyToClipboard;
		private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem undoToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem redoToolStripMenuItem;
	}
}

