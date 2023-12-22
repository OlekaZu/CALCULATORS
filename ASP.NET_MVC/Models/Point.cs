namespace WebAppMVC.Models
{
    public struct Point
    {
        public double? X { get; set; }
        public double? Y { get; set; }

        public Point(double? x, double? y) => (X, Y) = (x, y);
    }
}

