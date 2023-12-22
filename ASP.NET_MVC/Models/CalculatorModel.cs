using System.Runtime.InteropServices;

namespace WebAppMVC.Models
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

        private nint _cppCalculatorModel = nint.Zero;

        public string Input { get; set; } = "";
        public double ArgumentX { get; set; } = 0;
        public double Result { get; set; } = 0;
        public string Error { get; set; } = "";
        public CalculatorModel(string input, double argX)
        {
            Input = input;
            ArgumentX = argX;
            _cppCalculatorModel = CreateCalculationClass();
            if (_cppCalculatorModel != nint.Zero && input != null && input != "")
            {
                GetMeaningByAgrument(argX);
            }
        }

        ~CalculatorModel()
        {
            DisposeCalculationClass(_cppCalculatorModel);
            _cppCalculatorModel = nint.Zero;
        }

        public void GetMeaningByAgrument(double argX)
        {
            ArgumentX = argX;
            nint stringBuilder = Marshal.StringToHGlobalAnsi(CalculatorModel.PrepareInputStringForModel(Input));
            CallCalculate(_cppCalculatorModel, stringBuilder, argX);
            Input = PrepareInputStringForView(Marshal.PtrToStringAnsi(CallGetInput(_cppCalculatorModel))!);
            Result = CallGetData(_cppCalculatorModel);
            Error = Marshal.PtrToStringAnsi(CallGetError(_cppCalculatorModel))!;
        }
        private static string PrepareInputStringForModel(string input)
        {
            string res = input;
            res = res.Replace(",", ".");
            res = res.Replace("=", "");
            res = res.Replace("÷", "/");
            res = res.Replace("×", "*");
            res = res.Replace("√", "sqrt");
            res = res.Replace("π", "P");
            return res;
        }
        private static string PrepareInputStringForView(string input)
        {
            string res = input;
            res = res.Replace("/", "÷");
            res = res.Replace("*", "×");
            res = res.Replace("sqrt", "√");
            res = res.Replace("P", "π");
            return res;
        }
    }
}
