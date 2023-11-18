#include <iostream>

int main() {
    // 动态分配整数
    int* dynamicInt = new int;

    // 使用动态分配的内存
    *dynamicInt = 42;
    std::cout << "动态分配的整数值为: " << *dynamicInt << std::endl;

    // 动态分配数组
    const int arraySize = 5;
    double* dynamicArray = new double[arraySize];

    // 使用动态分配的数组
    std::cout << "请输入 " << arraySize << " 个双精度数值:" << std::endl;
    for (int i = 0; i < arraySize; ++i) {
        std::cin >> dynamicArray[i];
    }

    std::cout << "动态分配的数组值为: ";
    for (int i = 0; i < arraySize; ++i) {
        std::cout << dynamicArray[i] << " ";
    }
    std::cout << std::endl;

    // 释放动态分配的内存
    delete dynamicInt;
    delete[] dynamicArray;

    return 0;
}
