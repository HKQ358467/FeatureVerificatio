#include <iostream>

// 在这个源文件中定义全局变量
int globalVar = 42;

int main() {
    // 使用extern关键字引用全局变量
    extern int globalVar;

    // 访问全局变量globalVar
    std::cout << "The value of globalVar is: " << globalVar << std::endl;
    return 0;
}
