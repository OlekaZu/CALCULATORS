using System.Globalization;

namespace MyCalculator.View
{
    public class StringToDoubleConverter : IValueConverter
    {
        public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
        {
            return ((double)value!).ToString();
        }
        public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
        {
            if (double.TryParse(value!.ToString(), out var res))
                return res;
            else
                return 0.0;
        }
    }
}

