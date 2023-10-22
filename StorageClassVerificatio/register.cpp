#include <iostream>

int main() {
    register int counter; // 声明一个寄存器变量

    // 初始化计数器
    counter = 0;

    for (int i = 0; i < 1000000; ++i) {
        counter++; // 将计数器的值递增
    }

    std::cout << "Counter: " << counter << std::endl;

    return 0;
}
