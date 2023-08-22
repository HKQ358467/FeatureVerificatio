using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RMSApproximateVerificatio
{
    public class RMSApproximateVerificatio
    {
        /// <summary>
        /// 生成一个随机数组，该数组的均方根接近于给定的rms值
        /// </summary>
        /// <param name="rms">期望的均方根值</param>
        /// <param name="arrayLen">生成的数组长度</param>
        /// <param name="min">生成的随机数范围最小值</param>
        /// <param name="max">生成的随机数范围最大值</param>
        /// <returns></returns>
        public double[] GetRMSApproximateNum(double rms, int arrayLen, double min, double max)
        {
            double[] array = new double[arrayLen];
            const double learningRate = 0.01;
            const double tolerance = 0.0001;
            Random rand = new Random();
            // 首先生成[min,max)范围内的随机数组
            for (int i = 0; i < arrayLen; i++)
            {
                array[i] = min + (max - min) * rand.NextDouble();
            }
            for (; ; )
            {
                double sum = 0;
                for (int i = 0; i < arrayLen; i++)
                {
                    sum += array[i] * array[i];
                }


                double currentRms = Math.Sqrt(sum / arrayLen);

                // 计算误差为目标rms值和当前rms值的差
                double error = currentRms - rms;

                // 如果误差小于指定的公差，则停止
                if (Math.Abs(error) < tolerance)
                {
                    break;
                }
                // 更新数组的值
                for (int i = 0; i < arrayLen; i++)
                {
                    double gradient = 2 * array[i] / arrayLen;
                    array[i] -= learningRate * error * gradient;

                    // 确保新的值仍在[min, max]范围内
                    array[i] = Math.Max(min, Math.Min(max, array[i]));
                }
            }
            // 对数组进行四舍五入
            for (int i = 0; i < arrayLen; i++)
            {
                array[i] = Math.Round(array[i], 1);
            }
            return array;
        }
    }
}
