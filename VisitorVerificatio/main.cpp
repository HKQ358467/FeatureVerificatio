#include <iostream>
#include <vector>

// 前向声明访问者类
class ComputerPartVisitor;

// 抽象元素类：计算机部件
class ComputerPart {
public:
    virtual void accept(ComputerPartVisitor& visitor) = 0;
};

// 具体元素类：键盘
class Keyboard : public ComputerPart {
public:
    void accept(ComputerPartVisitor& visitor) override;
};

// 具体元素类：显示器
class Monitor : public ComputerPart {
public:
    void accept(ComputerPartVisitor& visitor) override;
};

// 具体元素类：鼠标
class Mouse : public ComputerPart {
public:
    void accept(ComputerPartVisitor& visitor) override;
};

// 抽象访问者类
class ComputerPartVisitor {
public:
    virtual void visit(Keyboard& keyboard) = 0;
    virtual void visit(Monitor& monitor) = 0;
    virtual void visit(Mouse& mouse) = 0;
};

// 具体访问者类：计算机部件显示
class ComputerPartDisplayVisitor : public ComputerPartVisitor {
public:
    void visit(Keyboard& keyboard) override {
        std::cout << "Displaying Keyboard" << std::endl;
    }

    void visit(Monitor& monitor) override {
        std::cout << "Displaying Monitor" << std::endl;
    }

    void visit(Mouse& mouse) override {
        std::cout << "Displaying Mouse" << std::endl;
    }
};

int main() {
    // 创建计算机部件列表
    std::vector<ComputerPart*> parts;
    parts.push_back(new Keyboard());
    parts.push_back(new Monitor());
    parts.push_back(new Mouse());

    // 创建访问者
    ComputerPartDisplayVisitor visitor;

    // 让访问者访问计算机部件
    for (auto part : parts) {
        part->accept(visitor);
    }

    // 释放内存
    for (auto part : parts) {
        delete part;
    }

    return 0;
}

// 实现具体元素类的accept方法
void Keyboard::accept(ComputerPartVisitor& visitor) {
    visitor.visit(*this);
}

void Monitor::accept(ComputerPartVisitor& visitor) {
    visitor.visit(*this);
}

void Mouse::accept(ComputerPartVisitor& visitor) {
    visitor.visit(*this);
}
