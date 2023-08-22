namespace RMSApproximateVerificatio
{
    internal class Program
    {
        static void Main(string[] args)
        {
            RMSApproximateVerificatio rmsApproximateVerificatio = new RMSApproximateVerificatio();
            double[] result = rmsApproximateVerificatio.GetRMSApproximateNum(30, 100, 28, 35);
            foreach (double num in result)
            {
                Console.WriteLine(num);
            }
        }
    }
}