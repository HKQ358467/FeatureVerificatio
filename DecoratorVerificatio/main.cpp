#include <iostream>
#include <string>

// 抽象组件
class Component {
public:
    virtual void operation() = 0;
};

// 具体组件
class ConcreteComponent : public Component {
public:
    void operation() override {
        std::cout << "执行具体组件的操作" << std::endl;
    }
};

// 抽象装饰器
class Decorator : public Component {
protected:
    Component* component_;

public:
    Decorator(Component* component) : component_(component) {}

    void operation() override {
        if (component_) {
            component_->operation();
        }
    }
};

// 具体装饰器A
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* component) : Decorator(component) {}

    void operation() override {
        Decorator::operation();
        std::cout << "执行具体装饰器A的操作" << std::endl;
    }
};

// 具体装饰器B
class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* component) : Decorator(component) {}

    void operation() override {
        Decorator::operation();
        std::cout << "执行具体装饰器B的操作" << std::endl;
    }
};

int main() {
    // 创建具体组件对象
    Component* component = new ConcreteComponent();

    // 使用具体装饰器A装饰具体组件
    Component* decoratorA = new ConcreteDecoratorA(component);
    decoratorA->operation();

    std::cout << std::endl;

    // 使用具体装饰器B装饰具体组件
    Component* decoratorB = new ConcreteDecoratorB(component);
    decoratorB->operation();

    delete component;
    delete decoratorA;
    delete decoratorB;

    return 0;
}