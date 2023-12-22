using WebAppMVC.Models;

namespace WebAppMVC.ViewModels
{
    public class GraphViewModel
    {
        private double _step = 0.01;
        private static readonly List<double> s_stepBorders = new() { 20, 200, 2000, 20000, 200000 };
        private static readonly List<double> s_stepValues = new() { 0.01, 0.1, 1.0, 5.0, 15.0, 50.0 };
        public CalculatorModel CalculatorData { get; set; } = new CalculatorModel("", 0);
        public Dictionary<string, double> GraphLimits { get; set; } = new() { { "xMin", -10 }, { "xMax", 10 }, { "yMin", -10 }, { "yMax", 10 } };

        public GraphViewModel() { }
        public Point[] CalculateData()
        {
            var points = new List<Point>();
            if (IsNotValid())
                return points.ToArray();
            CalculateStep();
            for (double i = GraphLimits["xMin"]; i <= GraphLimits["xMax"]; i += _step)
            {
                CalculatorData.GetMeaningByAgrument(i);
                var value = CalculatorData.Result;
                if (double.IsFinite(value) && value >= GraphLimits["yMin"] && value <= GraphLimits["yMax"])
                    points.Add(new Point(i, value));
                else
                    points.Add(new Point(i, null));
            }
            return points.ToArray();
        }
        private void CalculateStep()
        {
            var diff = GraphLimits["xMax"] - GraphLimits["xMin"];

            for (var i = 0; i < s_stepBorders.Count; i++)
            {
                _step = s_stepValues[i];
                if (diff <= s_stepBorders[i])
                    break;
                else
                    _step = s_stepValues[i + 1];
            }
        }

        private bool IsNotValid() => (string.IsNullOrWhiteSpace(CalculatorData.Input) || GraphLimits["xMax"] <= GraphLimits["xMin"] || GraphLimits["yMax"] <= GraphLimits["yMin"] || CalculatorData.Error == "Incorrect input");
    }

}
