#include <iostream>

int main() {
    // 整数常量示例
    const int integerConstant = 42;  // 声明一个整数常量，值为42
    std::cout << "整数常量: " << integerConstant << std::endl;

    // 浮点常量示例
    const double pi = 3.1415926;    // 声明一个双精度浮点常量，代表圆周率
    std::cout << "浮点常量 (圆周率): " << pi << std::endl;

    // 字符常量示例
    const char grade = 'A';         // 声明一个字符常量，代表等级'A'
    std::cout << "字符常量 (等级): " << grade << std::endl;

    // 字符串常量示例
    const char* greeting = "你好，世界！";  // 声明一个字符串常量
    std::cout << "字符串常量: " << greeting << std::endl;

    return 0;
}
