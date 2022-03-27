using System.Windows.Forms;

namespace RickArdurousEditor
{
	public partial class DocumentationForm : Form
	{
		public DocumentationForm()
		{
			InitializeComponent();

			this.WebBrowserDocumentation.Url = new System.Uri(GetDocPath() + "index.html");
		}

		private string GetDocPath()
		{
			// add a folder separator at the end of the path
			string gamePath = Properties.Settings.Default.DocRelativePath;
			if (gamePath[gamePath.Length - 1] != '/')
				gamePath += '/';

			// check if the path is local or global
			if (System.IO.Path.IsPathRooted(gamePath))
				return gamePath;
			return Application.StartupPath + gamePath;
		}

		private void DocumentationForm_FormClosed(object sender, FormClosedEventArgs e)
		{
			(this.Owner as MainForm).DocumentationFormClosedNotification();
		}
	}
}
