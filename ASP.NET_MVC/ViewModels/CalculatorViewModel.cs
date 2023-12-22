using WebAppMVC.Models;

namespace WebAppMVC.ViewModels
{
    public class CalculatorViewModel
    {
        public CalculatorModel CalculatorData { get; set; } = new CalculatorModel("", 0);
        public History HistoryData { get; set; } = new History();
        public string PressEqual { get; set; } = "clickNo";
    }
}
