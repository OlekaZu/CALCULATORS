using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using System.Globalization;
using WebAppMVC.Models;
using WebAppMVC.ViewModels;

namespace WebAppMVC.Controllers
{
    public class DepositController : Controller
    {
        private readonly Serilog.ILogger _logger;
        private DepositModel _model;

        public DepositController(DepositModel model, Serilog.ILogger logger)
        {
            CultureInfo.CurrentCulture = new CultureInfo("en-US");
            _logger = logger;
            _model = model;
        }
        [HttpGet]
        public ActionResult Index()
        {
            _logger.Information("Open Home Page: /Deposit/Index");
            return View(_model);
        }
        [HttpPost]
        public ActionResult Index(DepositModel model)
        {
            _logger.Information("Calculate deposit");
            model.DepositCalculate();
            return View(model);
        }
        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            _logger.Error($"{HttpContext.Request.Path} {HttpContext.TraceIdentifier}");
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
