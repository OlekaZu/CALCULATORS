using System.Runtime.InteropServices;

namespace WebAppMVC.Models
{
    public class CreditModel
    {
        private const string DllPath = "Libraries/ModelLibrary.dll";
        [DllImport(DllPath, EntryPoint = "CreateCreditClass")]
        private static extern nint CreateCreditClass();

        [DllImport(DllPath, EntryPoint = "DisposeCreditClass")]
        private static extern void DisposeCreditClass(nint pCreditClass);

        [DllImport(DllPath, EntryPoint = "CallCreditCalculate")]
        private static extern void CallCreditCalculate(nint pCreditClass, double sum, double term, double percent, int method);

        [DllImport(DllPath, EntryPoint = "CallCreditTotalSum")]
        private static extern double CallCreditTotalSum(nint pCreditClass);
        [DllImport(DllPath, EntryPoint = "CallCreditMonthlyPayment")]
        private static extern double CallCreditMonthlyPayment(nint pCreditClass);
        [DllImport(DllPath, EntryPoint = "CallCreditOverpayment")]
        private static extern double CallCreditOverpayment(nint pCreditClass);

        [DllImport(DllPath, EntryPoint = "CallCreditGetError", CharSet = CharSet.Ansi)]
        private static extern nint CallCreditGetError(nint pCreditClass);
        private nint _cppCreditModel = nint.Zero;
        public double CreditSum { get; set; } = 0;
        public double CreditTerm { get; set; } = 0;
        public double CreditPercent { get; set; } = 0;
        public int CreditMethod { get; set; } = 0;
        public double CreditTotalSum { get; set; } = 0;
        public double CreditMonthlyPayment { get; set; } = 0;
        public double CreditOverpayment { get; set; } = 0;
        public string CreditError { get; set; } = "";
        public CreditModel() { }
        ~CreditModel()
        {
            DisposeCreditClass(_cppCreditModel);
            _cppCreditModel = nint.Zero;
        }
        public void CreditCalculate()
        {
            _cppCreditModel = CreateCreditClass();
            if (IsValid())
            {
                CallCreditCalculate(_cppCreditModel, CreditSum, CreditTerm, CreditPercent, CreditMethod);
                CreditError = Marshal.PtrToStringAnsi(CallCreditGetError(_cppCreditModel))!;
                CreditTotalSum = CallCreditTotalSum(_cppCreditModel);
                CreditMonthlyPayment = CallCreditMonthlyPayment(_cppCreditModel);
                CreditOverpayment = CallCreditOverpayment(_cppCreditModel);
            }
            else
            {
                CreditError = "Incorrect Data";
            }

        }

        private bool IsValid() => (_cppCreditModel != nint.Zero && CreditSum > 0 && CreditTerm > 0 && CreditPercent > 0 && CreditMethod > 0);
    }
}
