#include <iostream>

// 全局变量，具有全局作用域，整个程序中可见
int globalVariable = 10;

namespace MyNamespace {
    // 命名空间内的变量，具有命名空间作用域
    int namespaceVariable = 5;
}

int main() {
    // 局部变量，具有局部作用域，只在main函数内可见
    int localVariable = 20;

    std::cout << "在全局作用域中访问全局变量: " << globalVariable << std::endl;
    std::cout << "在main函数内访问局部变量: " << localVariable << std::endl;

    {
        // 块作用域内的变量，只在此块内可见
        int blockVariable = 30;
        std::cout << "在块作用域内访问块变量: " << blockVariable << std::endl;
    }

    // 无法访问块内的变量，会导致编译错误
    // std::cout << "尝试在外部访问块变量: " << blockVariable << std::endl;

    // 在命名空间中访问命名空间内的变量
    std::cout << "在命名空间内访问命名空间变量: " << MyNamespace::namespaceVariable << std::endl;

    return 0;
}
