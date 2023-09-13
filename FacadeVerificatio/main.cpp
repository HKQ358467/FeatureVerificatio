#include <iostream>

// 子系统类A
class SubsystemA {
public:
    void operationA() {
        std::cout << "Subsystem A operation" << std::endl;
    }
};

// 子系统类B
class SubsystemB {
public:
    void operationB() {
        std::cout << "Subsystem B operation" << std::endl;
    }
};

// 外观类
class Facade {
private:
    SubsystemA subsystemA;
    SubsystemB subsystemB;

public:
    void operation() {
        subsystemA.operationA();
        subsystemB.operationB();
    }
};

int main() {
    // 创建外观对象
    Facade facade;

    // 调用外观对象的操作方法
    facade.operation();

    return 0;
}