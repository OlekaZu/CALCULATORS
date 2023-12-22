namespace WebAppMVC.Models
{
    public class History
    {
        private readonly string _historyFilePath;
        public List<string> HistoryList { get; set; } = new List<string>();

        public History()
        {
            _historyFilePath = Path.Combine(Directory.GetCurrentDirectory(), "history.txt");
            if (File.Exists(_historyFilePath))
                ReadHistoryFromFile();
        }

        public void AddHistoryInFile()
        {
            using (StreamWriter writer = new StreamWriter(_historyFilePath, true))
            {
                writer.WriteLine(HistoryList.Last());
            }
        }
        public void RemoveAllHistory()
        {
            HistoryList.Clear();
            if (File.Exists(_historyFilePath))
                File.Delete(_historyFilePath);
        }
        private void ReadHistoryFromFile()
        {
            using (StreamReader reader = new StreamReader(_historyFilePath))
            {
                string line;
                while ((line = reader.ReadLine()!) is not null)
                {
                    HistoryList.Add(line);
                }
            }
        }
    }
}
