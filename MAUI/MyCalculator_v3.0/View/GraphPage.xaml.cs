using MyCalculator.View;
using MyCalculator.ViewModel;
using System.Text.RegularExpressions;

namespace MyCalculator;

public partial class GraphPage : ContentPage
{
    public GraphPage(GraphViewModel graphVM)
    {
        InitializeComponent();
        BindingContext = graphVM;
        // привязка конвертора к вводу аргументов
        MinX.SetBinding(Entry.TextProperty, "BeginMeaningX", converter: new StringToDoubleConverter());
        MaxX.SetBinding(Entry.TextProperty, "EndMeaningX", converter: new StringToDoubleConverter());
        MinY.SetBinding(Entry.TextProperty, "BeginMeaningY", converter: new StringToDoubleConverter());
        MaxY.SetBinding(Entry.TextProperty, "EndMeaningY", converter: new StringToDoubleConverter());
    }

    private void MinX_TextChanged(object sender, TextChangedEventArgs e)
    {
        string newText = e.NewTextValue;
        int lastIndex = newText.Length - 1;
        if (!string.IsNullOrEmpty(newText) && !MyRegex().IsMatch(newText))
            MinX.Text = newText.Remove(lastIndex);
    }

    private void MinY_TextChanged(object sender, TextChangedEventArgs e)
    {
        string newText = e.NewTextValue;
        int lastIndex = newText.Length - 1;
        if (!string.IsNullOrEmpty(newText) && !MyRegex().IsMatch(newText))
            MinY.Text = newText.Remove(lastIndex);
    }

    private void MaxX_TextChanged(object sender, TextChangedEventArgs e)
    {
        string newText = e.NewTextValue;
        int lastIndex = newText.Length - 1;
        if (!string.IsNullOrEmpty(newText) && !MyRegex().IsMatch(newText))
            MaxX.Text = newText.Remove(lastIndex);
    }

    private void MaxY_TextChanged(object sender, TextChangedEventArgs e)
    {
        string newText = e.NewTextValue;
        int lastIndex = newText.Length - 1;
        if (!string.IsNullOrEmpty(newText) && !MyRegex().IsMatch(newText))
            MaxY.Text = newText.Remove(lastIndex);
    }

    [GeneratedRegex("^[\\-]?[0-9]*[,\\.]?[0-9]*$")]
    private static partial Regex MyRegex();
}