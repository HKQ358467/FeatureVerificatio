namespace RangeDenseVerificatio
{
    internal class Program
    {
        static void Main(string[] args)
        {
             double[] testData = { 20, 20.2, 22, 21, 30，31，45， 50 };
			 int testRange = 2;
			 double result = ArrayHandle.GetRangeDense(testData, testRange);
			 Console.WriteLine("The result is: " + result);
        }
    }
}