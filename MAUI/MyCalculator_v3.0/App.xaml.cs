namespace MyCalculator
{
    public partial class App : Application
    {
        public App()
        {
            InitializeComponent();

            MainPage = new AppShell();
        }

        protected override Window CreateWindow(IActivationState? activationState)
        {
            var windows = base.CreateWindow(activationState);
            windows.MaximumHeight = 750;
            windows.MaximumWidth = 550;
            windows.MinimumHeight = 750;
            windows.MinimumWidth = 550;
            windows.Title = "MyCalculator";

            return windows;
        }
    }
}
