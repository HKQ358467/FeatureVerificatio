#include <iostream>
#include <vector>
#include <algorithm> // 用于std::sort

// 函数声明，它执行二分搜索。它接收一个整数向量和一个要搜索的键值。
int binarySearch(const std::vector<int>& arr, int key);

int main() {
    // 创建一个示例向量数组，并保证它是有序的
    std::vector<int> arr = {3, 5, 2, 4, 9};

    // 使用标准库函数对数组进行排序
    std::sort(arr.begin(), arr.end());

    // 我们要搜索的键值
    int key = 4;

    // 调用二分搜索函数，并接收搜索结果
    int result = binarySearch(arr, key);

    // 检查返回值，确定是否找到了键值
    if (result != -1) {
        // 如果找到了，输出它的位置
        std::cout << "Element found at index: " << result << "\n";
    } else {
        // 如果没有找到，输出相应的消息
        std::cout << "Element not found in the array.\n";
    }

    return 0;
}

// 二分搜索函数的实现
int binarySearch(const std::vector<int>& arr, int key) {
    // 定义搜索的初始边界
    int left = 0;
    int right = arr.size() - 1;

    // 当左边界不大于右边界时，执行搜索
    while (left <= right) {
        // 计算中间位置
        int mid = left + (right - left) / 2;

        // 检查中间的元素是否是我们要找的键值
        if (arr[mid] == key) {
            // 如果是，返回中间位置的索引
            return mid;
        }

        // 如果中间元素小于键值，说明键值在右侧
        if (arr[mid] < key) {
            left = mid + 1; // 将左边界移动到中间位置的右侧
        } else {
            // 否则键值在左侧
            right = mid - 1; // 将右边界移动到中间位置的左侧
        }
    }

    // 如果搜索完整个区间还没有找到，返回-1表示没有找到
    return -1;
}
