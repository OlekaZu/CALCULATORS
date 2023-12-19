using CommunityToolkit.Maui;
using MyCalculator.ViewModel;
using SkiaSharp.Views.Maui.Controls.Hosting;

namespace MyCalculator
{
    public static class MauiProgram
    {
        public static MauiApp CreateMauiApp()
        {
            var builder = MauiApp.CreateBuilder();
            builder
                       .UseSkiaSharp(true)
                       .UseMauiCommunityToolkit()
                       .UseMauiApp<App>()
                       .ConfigureFonts(fonts =>
                       {
                           fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
                           fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
                       });
            builder.Services.AddSingleton<MainPage>();
            builder.Services.AddTransient<GraphPage>();
            builder.Services.AddTransient<GraphViewModel>();

            return builder.Build();
        }
    }
}
