namespace MyCalculator
{
    public partial class AppShell : Shell
    {
        public AppShell()
        {
            InitializeComponent();
            // add route to new pages
            Routing.RegisterRoute(nameof(GraphPage), typeof(GraphPage));
            Routing.RegisterRoute(nameof(HelpPage), typeof(HelpPage));
        }
    }
}
