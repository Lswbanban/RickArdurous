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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.ToolBar = new System.Windows.Forms.ToolStrip();
			this.toolStripButtonMirrorItem = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonDeleteItem = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonRespawnPointType = new System.Windows.Forms.ToolStripButton();
			this.SplitContainerToolAndLevel = new System.Windows.Forms.SplitContainer();
			this.SplitContainerWallAndItems = new System.Windows.Forms.SplitContainer();
			this.PictureBoxWallSprites = new System.Windows.Forms.PictureBox();
			this.PictureBoxItems = new System.Windows.Forms.PictureBox();
			this.PictureBoxLevel = new System.Windows.Forms.PictureBox();
			this.MenuStripMain = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
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
			((System.ComponentModel.ISupportInitialize)(this.PictureBoxLevel)).BeginInit();
			this.MenuStripMain.SuspendLayout();
			this.SuspendLayout();
			// 
			// ToolBar
			// 
			this.ToolBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButtonMirrorItem,
            this.toolStripButtonDeleteItem,
            this.toolStripButtonRespawnPointType});
			this.ToolBar.Location = new System.Drawing.Point(0, 24);
			this.ToolBar.Name = "ToolBar";
			this.ToolBar.Size = new System.Drawing.Size(800, 25);
			this.ToolBar.TabIndex = 0;
			this.ToolBar.Text = "toolStrip1";
			// 
			// toolStripButtonMirrorItem
			// 
			this.toolStripButtonMirrorItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonMirrorItem.Image = global::RickArdurousEditor.Properties.Resources.MirrorIcon;
			this.toolStripButtonMirrorItem.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonMirrorItem.Name = "toolStripButtonMirrorItem";
			this.toolStripButtonMirrorItem.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonMirrorItem.Text = "Mirror";
			this.toolStripButtonMirrorItem.Click += new System.EventHandler(this.toolStripButtonMirrorItem_Click);
			// 
			// toolStripButtonDeleteItem
			// 
			this.toolStripButtonDeleteItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonDeleteItem.Image = global::RickArdurousEditor.Properties.Resources.DeleteIcon;
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
			this.SplitContainerToolAndLevel.Panel2.Controls.Add(this.PictureBoxLevel);
			this.SplitContainerToolAndLevel.Size = new System.Drawing.Size(800, 401);
			this.SplitContainerToolAndLevel.SplitterDistance = 151;
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
			this.SplitContainerWallAndItems.Size = new System.Drawing.Size(151, 401);
			this.SplitContainerWallAndItems.SplitterDistance = 255;
			this.SplitContainerWallAndItems.TabIndex = 1;
			// 
			// PictureBoxWallSprites
			// 
			this.PictureBoxWallSprites.Dock = System.Windows.Forms.DockStyle.Fill;
			this.PictureBoxWallSprites.Location = new System.Drawing.Point(0, 0);
			this.PictureBoxWallSprites.Name = "PictureBoxWallSprites";
			this.PictureBoxWallSprites.Size = new System.Drawing.Size(147, 251);
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
			this.PictureBoxItems.Size = new System.Drawing.Size(147, 138);
			this.PictureBoxItems.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.PictureBoxItems.TabIndex = 0;
			this.PictureBoxItems.TabStop = false;
			this.PictureBoxItems.MouseClick += new System.Windows.Forms.MouseEventHandler(this.PictureBoxItems_MouseClick);
			// 
			// PictureBoxLevel
			// 
			this.PictureBoxLevel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.PictureBoxLevel.Location = new System.Drawing.Point(0, 0);
			this.PictureBoxLevel.Name = "PictureBoxLevel";
			this.PictureBoxLevel.Size = new System.Drawing.Size(641, 397);
			this.PictureBoxLevel.TabIndex = 0;
			this.PictureBoxLevel.TabStop = false;
			this.PictureBoxLevel.SizeChanged += new System.EventHandler(this.PictureBoxLevel_SizeChanged);
			this.PictureBoxLevel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PictureBoxLevel_MouseDown);
			this.PictureBoxLevel.MouseEnter += new System.EventHandler(this.PictureBoxLevel_MouseEnter);
			this.PictureBoxLevel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.PictureBoxLevel_MouseMove);
			this.PictureBoxLevel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.PictureBoxLevel_MouseUp);
			this.PictureBoxLevel.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.PictureBoxLevel_MouseWheel);
			// 
			// MenuStripMain
			// 
			this.MenuStripMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
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
			this.fileToolStripMenuItem.Size = new System.Drawing.Size(31, 20);
			this.fileToolStripMenuItem.Text = "File";
			// 
			// openToolStripMenuItem
			// 
			this.openToolStripMenuItem.Name = "openToolStripMenuItem";
			this.openToolStripMenuItem.Size = new System.Drawing.Size(95, 22);
			this.openToolStripMenuItem.Text = "Open";
			this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
			this.saveToolStripMenuItem.Size = new System.Drawing.Size(95, 22);
			this.saveToolStripMenuItem.Text = "Save";
			this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(92, 6);
			// 
			// exitToolStripMenuItem
			// 
			this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
			this.exitToolStripMenuItem.Size = new System.Drawing.Size(95, 22);
			this.exitToolStripMenuItem.Text = "Exit";
			this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
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
			((System.ComponentModel.ISupportInitialize)(this.PictureBoxLevel)).EndInit();
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
	}
}

