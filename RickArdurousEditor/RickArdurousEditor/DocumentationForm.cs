using System.Windows.Forms;

namespace RickArdurousEditor
{
	public partial class DocumentationForm : Form
	{
		public DocumentationForm()
		{
			InitializeComponent();

			this.WebBrowserDocumentation.Url = new System.Uri(Application.StartupPath + @"/../../../../Doc/index.html");
		}

		private void DocumentationForm_FormClosed(object sender, FormClosedEventArgs e)
		{
			(this.Owner as MainForm).DocumentationFormClosedNotification();
		}
	}
}
