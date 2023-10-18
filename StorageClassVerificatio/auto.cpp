#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用auto关键字声明一个迭代器，无需显式指定类型
    auto it = numbers.begin();

    // 使用auto关键字声明另一个迭代器
    auto end = numbers.end();

    // 使用auto关键字声明变量，推断为int类型
    auto sum = 0;

    // 遍历向量并计算总和
    while (it != end) {
        sum += *it;
        ++it;
    }

    std::cout << "Sum of numbers: " << sum << std::endl;

    return 0;
}
