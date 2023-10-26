#include <iostream>
#include <stack>

int main() {
    std::stack<int> myStack; // 创建一个整数类型的栈

    // 入栈操作
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);
    myStack.push(4);
    myStack.push(5);

    // 查看栈顶元素
    std::cout << "栈顶元素: " << myStack.top() << std::endl;

    // 出栈操作
    myStack.pop(); // 移除栈顶元素

    // 输出栈中的元素
    std::cout << "栈中的元素: ";
    while (!myStack.empty()) {
        std::cout << myStack.top() << " ";
        myStack.pop();
    }
    std::cout << std::endl;

    // 检查栈是否为空
    if (myStack.empty()) {
        std::cout << "栈为空。" << std::endl;
    } else {
        std::cout << "栈不为空。" << std::endl;
    }

    return 0;
}
