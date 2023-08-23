using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RangeDenseVerificatio
{
    public class RangeDenseVerificatio
    {
        /// <summary>
        /// 计算给定数据集中最密集的区间的平均值
        /// </summary>
        /// <param name="data">输入的数据集</param>
        /// <param name="range">定义密集的范围</param>
        /// <returns>返回最密集区间的平均值</returns>
        public static double GetRangeDense(double[] data, int range)
        {
            int Count = data.Length;
            double nSum = 0;
            int nCount = 0;
            int nSection = 0;
            double nAvg;

            int nMaxSection = 0;  //最密集的段的ID
            int nMaxSectionCount = 0;  //最密集的段的元素个数
            double nResult = data[0];  //计算后得出的平均值
            int nIndex = -1;  //段结束的下标
            for (int i = 0; i < Count; i++)
            {
                nSum += data[i];
                nCount++;
                nAvg = nSum / nCount;
                if (!(nAvg + range >= data[i] && nAvg - range <= data[i]))
                {
                    if (nCount - 1 > nMaxSectionCount)  //如果当前段比上一个段还大，则当前段设置成最大段
                                                        //如果存在多个数量相同的最大段，则使用大于取最后一个最大段，使用大于等于取第一个最大段
                    {
                        nMaxSectionCount = nCount - 1;
                        nMaxSection = nSection;
                        nResult = (nSum - data[i]) / nMaxSectionCount;
                        nIndex = i - 1;
                    }
                    nSum = data[i];
                    nCount = 1;
                    nSection++;
                }
            }
            return nResult;
        }
	}
}
