#include <iostream>
#include <functional>

// 普通函数
int add(int a, int b) {
    return a + b;
}

// 函数对象类
struct Multiply {
    int operator()(int a, int b) {
        return a * b;
    }
};

// Lambda 表达式
auto subtract = [](int a, int b) {
    return a - b;
};

int main() {
    // 包装普通函数
    std::function<int(int, int)> func1 = add;
    int result1 = func1(3, 4); // 结果为7

    // 包装函数对象
    Multiply multiply;
    std::function<int(int, int)> func2 = multiply;
    int result2 = func2(3, 4); // 结果为12

    // 包装 Lambda 表达式
    std::function<int(int, int)> func3 = subtract;
    int result3 = func3(3, 4); // 结果为-1

    // 输出结果
    std::cout << "Result 1: " << result1 << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;
    std::cout << "Result 3: " << result3 << std::endl;

    return 0;
}
