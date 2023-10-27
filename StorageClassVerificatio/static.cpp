#include <iostream>

void exampleFunction() {
    // 静态局部变量，生命周期为整个程序运行期间
    static int count = 0;
    count++; // 每次调用函数时，count 值增加

    std::cout << "count: " << count << std::endl;
}

int main() {
    for (int i = 0; i < 5; i++) {
        exampleFunction();
    }

    return 0;
}
