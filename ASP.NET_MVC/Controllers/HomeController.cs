using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using System.Globalization;
using WebAppMVC.Models;
using WebAppMVC.ViewModels;

namespace WebAppMVC.Controllers
{
    public class HomeController : Controller
    {
        private readonly Serilog.ILogger _logger;
        private History _modelHistory;

        public HomeController(Serilog.ILogger logger, History modelHistory)
        {
            CultureInfo.CurrentCulture = new CultureInfo("en-US");
            _logger = logger;
            _modelHistory = modelHistory;
        }

        [HttpGet]
        public IActionResult Index()
        {
            _logger.Information("Open Home Page: /Home/Index");
            CalculatorViewModel viewModel = new() { HistoryData = _modelHistory };
            return View(viewModel);
        }

        [HttpPost]
        public IActionResult Index(string inputStr, double argumentX)
        {
            CalculatorModel model = new(inputStr, argumentX);
            _modelHistory.HistoryList?.Add(model.Input);
            _modelHistory.AddHistoryInFile();
            CalculatorViewModel viewModel = new() { CalculatorData = model, HistoryData = _modelHistory, PressEqual = "clickYes" };
            _logger.Information("Calculate the expression: " + model.Input);
            return View(viewModel);
        }

        [HttpGet]
        public IActionResult DeleteHistory()
        {
            _logger.Information("Delete Calculation History");
            _modelHistory.RemoveAllHistory();
            CalculatorViewModel viewModel = new() { HistoryData = _modelHistory };
            return View("Index", viewModel);
        }

        #region Graph
        public IActionResult Graph()
        {
            _logger.Information("Open Graph Page /Home/Graph");
            return View();
        }


        [HttpPost]
        public Point[] Graph(string inputFormula, double xMin, double xMax, double yMin, double yMax)
        {
            CalculatorModel model = new(inputFormula, 0);
            Dictionary<string, double> limits = new() { { "xMin", xMin }, { "xMax", xMax }, { "yMin", yMin }, { "yMax", yMax } };

            GraphViewModel viewGraph = new() { CalculatorData = model, GraphLimits = limits };
            Point[] result = viewGraph.CalculateData();
            _logger.Information("Draw graph: " + model.Input);
            return result;
        }
        #endregion

        [HttpGet]
        public IActionResult Help()
        {
            _logger.Information("Open Help Page /Home/Help");
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            _logger.Error($"{HttpContext.Request.Path} {HttpContext.TraceIdentifier}");
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}