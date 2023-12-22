using Serilog;
using WebAppMVC.Models;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddControllersWithViews();
builder.Services.AddScoped<History>();
builder.Services.AddScoped<CreditModel>();
builder.Services.AddScoped<DepositModel>();

var logger = new LoggerConfiguration().WriteTo.File($"Logs/logs_{DateTime.Now.ToString("dd-MMMM-yyyy_hh_mm")}_.txt", rollingInterval: RollingInterval.Hour).CreateLogger();
builder.Services.AddSingleton<Serilog.ILogger>(logger);

var app = builder.Build();

if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();
app.UseAuthorization();


app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");
try
{
    app.Run();
}
catch (Exception ex)
{
    logger.Fatal("{0}", ex.Message);
}