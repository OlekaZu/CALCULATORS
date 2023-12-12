using System.Runtime.InteropServices;

namespace MyCalculator.Model
{
    public class CalculatorModel
    {
        private const string DllPath = "Libraries/ModelLibrary.dll";
        [DllImport(DllPath, EntryPoint = "CreateCalculationClass")]
        private static extern nint CreateCalculationClass();

        [DllImport(DllPath, EntryPoint = "DisposeCalculationClass")]
        private static extern void DisposeCalculationClass(nint pCalculationClass);

        [DllImport(DllPath, EntryPoint = "CallCalculate", CharSet = CharSet.Ansi)]
        private static extern void CallCalculate(nint pCalculationClass, nint input, double argX);

        [DllImport(DllPath, EntryPoint = "CallGetData")]
        private static extern double CallGetData(nint pCalculationClass);

        [DllImport(DllPath, EntryPoint = "CallGetError", CharSet = CharSet.Ansi)]
        private static extern nint CallGetError(nint pCalculationClass);

        [DllImport(DllPath, EntryPoint = "CallGetInput", CharSet = CharSet.Ansi)]
        private static extern nint CallGetInput(nint pCalculationClass);

        private nint _cppModel = nint.Zero;

        public string Input { get; set; } = "";

        public double ArgumentX { get; set; } = 0;

        public double Result { get; set; } = 0;

        public string? Error { get; set; } = "";

        public CalculatorModel(string input, double argX)
        {
            Input = input;
            ArgumentX = argX;
            _cppModel = CreateCalculationClass();
            if (_cppModel != nint.Zero)
            {
                nint stringBuilder = Marshal.StringToHGlobalAnsi(PrepareInputStringForModel(input));
                CallCalculate(_cppModel, stringBuilder, argX);
                Input = PrepareInputStringForView(Marshal.PtrToStringAnsi(CallGetInput(_cppModel))!);
                Result = CallGetData(_cppModel);
                Error = Marshal.PtrToStringAnsi(CallGetError(_cppModel));
            }
        }

        ~CalculatorModel()
        {
            DisposeCalculationClass(_cppModel);
            _cppModel = nint.Zero;
        }

        private static string PrepareInputStringForModel(string? input)
        {
            if (input == null)
                return string.Empty;
            string res = input;
            res = res.Replace("=", "");
            res = res.Replace("÷", "/");
            res = res.Replace("×", "*");
            res = res.Replace("√", "sqrt");
            res = res.Replace("π‎", "P");
            return res;
        }

        private static string PrepareInputStringForView(string input)
        {
            string res = input;
            res = res.Replace("/", "÷");
            res = res.Replace("*", "×");
            res = res.Replace("sqrt", "√");
            res = res.Replace("P", "π‎");
            return res;
        }
    }
}
