#include <iostream>
#include <string>

// 抽象产品类
class Product {
public:
    virtual void operation() = 0;
};

// 具体产品类A
class ConcreteProductA : public Product {
public:
    void operation() override {
        std::cout << "具体产品A的操作" << std::endl;
    }
};

// 具体产品类B
class ConcreteProductB : public Product {
public:
    void operation() override {
        std::cout << "具体产品B的操作" << std::endl;
    }
};

// 简单工厂类
class SimpleFactory {
public:
    static Product* createProduct(std::string type) {
        if (type == "A") {
            return new ConcreteProductA();
        } else if (type == "B") {
            return new ConcreteProductB();
        } else {
            return nullptr;
        }
    }
};

int main() {
    // 使用简单工厂创建产品对象
    Product* productA = SimpleFactory::createProduct("A");
    Product* productB = SimpleFactory::createProduct("B");

    // 调用产品对象的操作方法
    productA->operation();
    productB->operation();

    // 释放内存
    delete productA;
    delete productB;

    return 0;
}