#include <iostream>

// 定义一个匿名类
class {
public:
    int add(int a, int b) {
        return a + b;
    }

    int subtract(int a, int b) {
        return a - b;
    }

    void displayMessage(const std::string& message) {
        std::cout << "Message: " << message << std::endl;
    }
} myAnonymousClass;  // 创建匿名类对象

int main() {
    // 使用匿名类对象调用成员函数
    int sum = myAnonymousClass.add(5, 3);
    int difference = myAnonymousClass.subtract(5, 3);
    std::string message = "Hello, Anonymous Class!";
    myAnonymousClass.displayMessage(message);

    // 输出结果
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << difference << std::endl;

    return 0;
}
