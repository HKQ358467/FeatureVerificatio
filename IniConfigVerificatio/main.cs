using System.IO;
using System.Collections.Specialized;

public class IniReader
{
    private string _filePath;

    public IniReader(string filePath)
    {
        _filePath = filePath;
    }

    public NameValueCollection GetAllSettings()
    {
        NameValueCollection data = new NameValueCollection();

        foreach (var row in File.ReadAllLines(_filePath))
        {
            if (!string.IsNullOrEmpty(row) && !row.StartsWith(";"))
            {
                var idx = row.IndexOf('=');
                if (idx != -1)
                {
                    string key = row.Substring(0, idx).Trim();
                    string value = row.Substring(idx + 1).Trim();

                    data.Add(key, value);
                }
            }
        }

        return data;
    }
}