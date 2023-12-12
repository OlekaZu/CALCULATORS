using MyCalculator.View;
using MyCalculator.ViewModel;
using System.Text.RegularExpressions;

namespace MyCalculator
{
    public partial class MainPage : ContentPage
    {
        private readonly string[] _operatorsSymbols = { ".", "+", "-", "*", "×", "÷", "^" };
        private readonly string[] _functionsSymbols = { "sin", "cos", "tan", "acos", "asin", "acos", "atan", "log", "ln", "√" };
        private readonly string _argumentX = "Arg X";
        private bool _equalSignPressed = false;

        public MainPage()
        {
            InitializeComponent();
            // привязка к ViewModel
            BindingContext = new CalculatorViewModel();
            // привязка конвертора к вводу аргумента X
            InputArgX.SetBinding(Entry.TextProperty, "ArgumentX", converter: new StringToDoubleConverter());
        }

        private void OnSelectInputSymbol(object sender, EventArgs e)
        {
            if (_equalSignPressed == true)
                ClearAll();
            Button button = (Button)sender;
            var buttonName = button.Text;
            int lengthInputStr = 0;
            if (InputStr.Text != null)
                lengthInputStr = InputStr.Text.Length;

            if (lengthInputStr > 255)
            {
                ClearAll();
                throw new Exception("The maximun size of input is exceeded");
            }
            // запрет на ввод нескольких операторов подряд
            if (lengthInputStr > 0 && _operatorsSymbols.Contains(buttonName) && _operatorsSymbols.Contains(InputStr.Text![lengthInputStr - 1].ToString()))
            {
                InputStr.Text += "";
            }
            // автоматически дописывает "(" при нажатии на кнопки-функции
            else if (_functionsSymbols.Any(x => x.Equals(buttonName)))
            {
                InputStr.Text += buttonName + "(";
            }
            else
            {
                if (buttonName == _argumentX)
                    buttonName = "x";
                InputStr.Text += buttonName;
            }

        }
        private void OnClearLastSymbol(object sender, EventArgs e)
        {
            if (InputStr.Text != "")
            {
                int lastIndex = InputStr.Text.Length - 1;
                InputStr.Text = InputStr.Text?.Remove(lastIndex);
            }

        }
        private void OnClear(object sender, EventArgs e)
        {
            ClearAll();
        }

        private void OnEqualSignClicked(object sender, EventArgs e)
        {
            _equalSignPressed = true;
            ResultStr.SetBinding(Label.TextProperty, "Error");
            if (string.IsNullOrEmpty(ResultStr.Text))
                ResultStr.SetBinding(Label.TextProperty, "Result");
        }
        private void OnSelectItemClicked(object sender, EventArgs e)
        {
            Reset();
        }
        private void ClearAll()
        {
            InputStr.Text = "";
            Reset();
        }

        private void Reset()
        {
            _equalSignPressed = false;
            ResultStr.Text = "0";
            InputArgX.Text = "0";
        }

        private void InputArgX_TextChanged(object sender, TextChangedEventArgs e)
        {
            string newText = e.NewTextValue;
            int lastIndex = newText.Length - 1;
            if (!string.IsNullOrEmpty(newText) && !MyRegex().IsMatch(newText))
                InputArgX.Text = newText.Remove(lastIndex);
        }

        [GeneratedRegex("^[\\-]?[0-9]*[,\\.]?[0-9]*$")]
        private static partial Regex MyRegex();
    }

}
