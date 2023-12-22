using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using System.Globalization;
using WebAppMVC.Models;
using WebAppMVC.ViewModels;

namespace WebAppMVC.Controllers
{
    public class CreditController : Controller
    {
        private readonly Serilog.ILogger _logger;
        private CreditModel _model;

        public CreditController(CreditModel model, Serilog.ILogger logger)
        {
            CultureInfo.CurrentCulture = new CultureInfo("en-US");
            _logger = logger;
            _model = model;
        }
        [HttpGet]
        public ActionResult Index()
        {
            _logger.Information("Open Home Page: /Credit/Index");
            return View(_model);
        }
        [HttpPost]
        public ActionResult Index(CreditModel model)
        {
            _logger.Information("Calculate Credit");
            model.CreditCalculate();

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