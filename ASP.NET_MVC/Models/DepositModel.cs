using System.Runtime.InteropServices;

namespace WebAppMVC.Models
{
    public class DepositModel
    {
        private const string DllPath = "Libraries/ModelLibrary.dll";
        [DllImport(DllPath, EntryPoint = "CreateDepositClass")]
        private static extern nint CreateDepositClass();

        [DllImport(DllPath, EntryPoint = "DisposeDepositClass")]
        private static extern void DisposeDepositClass(nint pDepositClass);

        [DllImport(DllPath, EntryPoint = "CallDepositCalculate")]
        private static extern void CallDepositCalculate(nint pDepositClass, double sum, double term, double percent, double tax, int method, double put_flow, double draw_flow);

        [DllImport(DllPath, EntryPoint = "CallDepositPercentSum")]
        private static extern double CallDepositPercentSum(nint pDepositClass);
        [DllImport(DllPath, EntryPoint = "CallDepositTaxSum")]
        private static extern double CallDepositTaxSum(nint pDepositClass);
        [DllImport(DllPath, EntryPoint = "CallDepositTotalSum")]
        private static extern double CallDepositTotalSum(nint pDepositClass);

        [DllImport(DllPath, EntryPoint = "CallDepositGetError", CharSet = CharSet.Ansi)]
        private static extern nint CallDepositGetError(nint pDepositClass);

        private nint _cppDepositModel = nint.Zero;
        public double DepositSum { get; set; } = 0;
        public double DepositTerm { get; set; } = 0;
        public double DepositPercent { get; set; } = 0;
        public double DepositTax { get; set; } = 0;
        public int CapitalizationMethod { get; set; } = 0;
        public double DepositPutFlow { get; set; } = 0;
        public double DepositDrawFlow { get; set; } = 0;
        public double DepositPercentSum { get; set; } = 0;
        public double DepositTaxSum { get; set; } = 0;
        public double DepositTotalSum { get; set; } = 0;
        public string DepositError { get; set; } = "";
        public DepositModel() { }

        ~DepositModel()
        {
            DisposeDepositClass(_cppDepositModel);
            _cppDepositModel = nint.Zero;
        }

        public void DepositCalculate()
        {
            _cppDepositModel = CreateDepositClass();
            if (IsValid())
            {
                CallDepositCalculate(_cppDepositModel, DepositSum, DepositTerm, DepositPercent, DepositTax, CapitalizationMethod, DepositPutFlow, DepositDrawFlow);
                DepositError = Marshal.PtrToStringAnsi(CallDepositGetError(_cppDepositModel))!;
                DepositPercentSum = CallDepositPercentSum(_cppDepositModel);
                DepositTaxSum = CallDepositTaxSum(_cppDepositModel);
                DepositTotalSum = CallDepositTotalSum(_cppDepositModel);
            }
            else
            {
                DepositError = "Incorrect Data";
            }
        }

        private bool IsValid() => (_cppDepositModel != nint.Zero && DepositSum > 0 && DepositTerm > 0 && DepositPercent > 0 && DepositTax >= 0 && CapitalizationMethod > 0 && DepositPutFlow >= 0 && DepositDrawFlow >= 0);
    }
}
