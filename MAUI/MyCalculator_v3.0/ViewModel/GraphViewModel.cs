using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LiveChartsCore;
using LiveChartsCore.Defaults;
using LiveChartsCore.SkiaSharpView;
using LiveChartsCore.SkiaSharpView.Painting;
using LiveChartsCore.SkiaSharpView.Painting.Effects;
using MyCalculator.Model;
using SkiaSharp;
using System.Collections.ObjectModel;

namespace MyCalculator.ViewModel
{
    // связывает свойство текущего класс (Text) с передаемым свойством (GraphFomula)
    [QueryProperty("Text", "GraphFormula")]
    public partial class GraphViewModel : ObservableObject
    {
        private static readonly SKColor _myGrey = new(93, 87, 113);
        private static readonly SKColor _myRed = new(226, 104, 125);
        private static readonly SKColor _myBrown = new(208, 157, 128);
        private static readonly SKColor _myPink = new(255, 208, 203);
        private const double StepBorder1 = 20;
        private const double StepBorder2 = 200;
        private const double StepBorder3 = 2000;
        private const double StepBorder4 = 20000;
        private const double StepBorder5 = 200000;

        private readonly ObservableCollection<ObservablePoint> _observablePoints;
        private readonly Axis _axeX;
        private readonly Axis _axeY;
        private double _step;

        // Свойство Text сформируется автоматически благораря Toolkit
        [ObservableProperty]
        private string? text;

        public double BeginMeaningX { get; set; } = -10;
        public double EndMeaningX { get; set; } = 10;
        public double BeginMeaningY { get; set; } = -10;
        public double EndMeaningY { get; set; } = 10;

        public ObservableCollection<ISeries> Series { get; set; }
        public Axis[] XAxes { get; set; }
        public Axis[] YAxes { get; set; }

        public DrawMarginFrame Frame { get; set; } = new()
        {
            Stroke = new SolidColorPaint(_myGrey, 1)
        };


        public GraphViewModel()
        {
            _observablePoints = new ObservableCollection<ObservablePoint> { };
            Series = new ObservableCollection<ISeries>
                {
                     new LineSeries<ObservablePoint>
                     {
                        Values = _observablePoints,
                        Fill = null,
                        GeometrySize = 0,
                        Stroke = new SolidColorPaint(_myBrown, 3)
                     }
                };

            _axeX = new Axis
            {
                MaxLimit = 10,
                MinLimit = -10,
                LabelsPaint = new SolidColorPaint(_myRed),
                TextSize = 10,
                SeparatorsPaint = new SolidColorPaint
                {
                    Color = _myGrey,
                    StrokeThickness = 1,
                    PathEffect = new DashEffect(new float[] { 3, 3 })
                },
                SubseparatorsPaint = new SolidColorPaint(_myPink, 0.5f),
                ZeroPaint = new SolidColorPaint(_myRed, 2)
            };
            XAxes = new Axis[] { _axeX };

            _axeY = new Axis
            {
                MaxLimit = 10,
                MinLimit = -10,
                LabelsPaint = new SolidColorPaint(_myRed),
                TextSize = 10,
                SeparatorsPaint = new SolidColorPaint
                {
                    Color = _myGrey,
                    StrokeThickness = 1,
                    PathEffect = new DashEffect(new float[] { 3, 3 })
                },
                SubseparatorsPaint = new SolidColorPaint(_myPink, 0.5f),
                ZeroPaint = new SolidColorPaint(_myRed, 2)
            };
            YAxes = new Axis[] { _axeY };
        }

        [RelayCommand]
        public void ShowGraph()
        {
            if (_observablePoints.Count > 0)
            { _observablePoints.Clear(); }
            CalculateStep();
            for (double x = BeginMeaningX; x <= EndMeaningX; x += _step)
            {
                CalculatorModel model = new(Text!, x);
                if (!double.IsNaN(model.Result) && string.IsNullOrEmpty(model.Error) && !double.IsInfinity(model.Result))
                    _observablePoints.Add(new ObservablePoint(x, model.Result));
                if (double.IsInfinity(model.Result))
                    _observablePoints.Add(new ObservablePoint(x, null));
            }
            _axeX.MinLimit = BeginMeaningX;
            _axeX.MaxLimit = EndMeaningX;
            _axeY.MinLimit = BeginMeaningY;
            _axeY.MaxLimit = EndMeaningY;
        }

        private void CalculateStep()
        {
            var diff = EndMeaningX - BeginMeaningX;
            if (diff <= StepBorder1)
                _step = 0.01f;
            else if (diff <= StepBorder2)
                _step = 0.1f;
            else if (diff <= StepBorder3)
                _step = 1.0f;
            else if (diff <= StepBorder4)
                _step = 5.0f;
            else if (diff <= StepBorder5)
                _step = 15.0f;
            else
                _step = 50.0;
        }

        [RelayCommand]
        private async Task GoBack()
        {
            await Shell.Current.GoToAsync("..");
        }
    }
}
