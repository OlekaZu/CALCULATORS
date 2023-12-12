using MyCalculator;
using MyCalculator.Model;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Input;

namespace MyCalculator.ViewModel
{
    public class CalculatorViewModel : INotifyPropertyChanged
    {
        private string _input = "";
        private double _result = 0;
        private string _error = "";
        private readonly string _historyFilePath;

        public event PropertyChangedEventHandler? PropertyChanged;
        public ICommand CalculateCommand { get; set; }
        public ICommand SelectFromHistoryCommand { get; set; }
        public ICommand RemoveHistoryCommand { get; set; }
        public ICommand DrawGraphCommand { get; set; }
        public ICommand OpenManualCommand { get; set; }
        public ObservableCollection<CalculatorModel> CalculatorHistory { get; } = new();

        public CalculatorViewModel()
        {
            Directory.SetCurrentDirectory(AppDomain.CurrentDomain.BaseDirectory);
            _historyFilePath = Path.Combine(Directory.GetCurrentDirectory(), "History", "history.txt");
            if (File.Exists(_historyFilePath))
                ReadHistoryFromFile();

            CalculateCommand = new Command(() =>
                {
                    CalculatorModel model = new(Input, ArgumentX);
                    CalculatorHistory.Add(model);
                    AddHistoryInFile();
                    Input = model.Input;
                    _result = model.Result;
                    _error = model.Error!;
                });
            SelectFromHistoryCommand = new Command((args) =>
                {
                    if (args is CalculatorModel model)
                    {
                        Input = model.Input;
                    }
                });
            RemoveHistoryCommand = new Command(() =>
            {
                CalculatorHistory.Clear();
                if (File.Exists(_historyFilePath))
                    File.Delete(_historyFilePath);
            });
            DrawGraphCommand = new Command(async () =>
                {
                    // добавляем в историю
                    CalculatorModel model = new(Input, ArgumentX);
                    CalculatorHistory.Add(model);
                    AddHistoryInFile();
                    await Shell.Current.GoToAsync($"{nameof(GraphPage)}?GraphFormula={Uri.EscapeDataString(Input)}");
                });
            OpenManualCommand = new Command(async () =>
                await Shell.Current.GoToAsync(nameof(HelpPage))
            );
        }

        public string Input
        {
            get => _input;
            set
            {
                if (_input != value)
                {
                    _input = value;
                    OnPropertyChanged();
                }
            }
        }

        public double ArgumentX { get; set; } = 0;

        public double Result
        {
            get => _result;
            set
            {
                if (_result != value)
                {
                    _result = value;
                    OnPropertyChanged();
                }
            }
        }
        public string Error
        {
            get => _error;
            set
            {
                if (_error != value)
                {
                    _error = value;
                    OnPropertyChanged();
                }
            }
        }
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }

        public void AddHistoryInFile()
        {
            if (Directory.Exists(Path.Combine(Directory.GetCurrentDirectory(), "History")))
                Directory.CreateDirectory(Path.Combine(Directory.GetCurrentDirectory(), "History"));
            using (StreamWriter writer = new StreamWriter(_historyFilePath, true))
            {
                writer.WriteLine(CalculatorHistory.Last().Input);
            }
        }

        private void ReadHistoryFromFile()
        {
            using (StreamReader reader = new StreamReader(_historyFilePath))
            {
                string line;
                while ((line = reader.ReadLine()!) != null)
                {
                    CalculatorModel model = new(line, 0);
                    CalculatorHistory.Add(model);
                }
            }
        }
    }
}
