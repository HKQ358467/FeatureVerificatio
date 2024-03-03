#include <iostream>
#include <vector>

// 函数声明，它执行线性搜索。它接收一个整数向量和一个要搜索的键值。
int linearSearch(const std::vector<int>& arr, int key);

int main() {
    // 创建一个示例向量数组
    std::vector<int> arr = {3, 5, 2, 4, 9};

    // 我们要搜索的键值
    int key = 4;

    // 调用线性搜索函数，并接收搜索结果
    int result = linearSearch(arr, key);

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

// 线性搜索函数的实现
int linearSearch(const std::vector<int>& arr, int key) {
    // 逐个遍历数组中的每个元素
    for (int i = 0; i < arr.size(); i++) {
        // 如果当前元素与搜索键值匹配
        if (arr[i] == key) {
            // 返回当前索引
            return i;
        }
    }
    // 如果遍历完数组还没有找到，返回-1表示没有找到
    return -1;
}
