#include <iostream>
#include <memory>

// 抽象产品类A
class AbstractProductA {
public:
    virtual void use() = 0;
};

// 具体产品类A1
class ConcreteProductA1 : public AbstractProductA {
public:
    void use() override {
        std::cout << "使用具体产品A1" << std::endl;
    }
};

// 具体产品类A2
class ConcreteProductA2 : public AbstractProductA {
public:
    void use() override {
        std::cout << "使用具体产品A2" << std::endl;
    }
};

// 抽象产品类B
class AbstractProductB {
public:
    virtual void eat() = 0;
};

// 具体产品类B1
class ConcreteProductB1 : public AbstractProductB {
public:
    void eat() override {
        std::cout << "使用具体产品B1" << std::endl;
    }
};

// 具体产品类B2
class ConcreteProductB2 : public AbstractProductB {
public:
    void eat() override {
        std::cout << "使用具体产品B2" << std::endl;
    }
};

// 抽象工厂类
class AbstractFactory {
public:
    virtual std::unique_ptr<AbstractProductA> createProductA() = 0;
    virtual std::unique_ptr<AbstractProductB> createProductB() = 0;
};

// 具体工厂类1
class ConcreteFactory1 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() override {
        return std::make_unique<ConcreteProductA1>();
    }

    std::unique_ptr<AbstractProductB> createProductB() override {
        return std::make_unique<ConcreteProductB1>();
    }
};

// 具体工厂类2
class ConcreteFactory2 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() override {
        return std::make_unique<ConcreteProductA2>();
    }

    std::unique_ptr<AbstractProductB> createProductB() override {
        return std::make_unique<ConcreteProductB2>();
    }
};

int main() {
    // 使用具体工厂1创建产品A和B
    std::unique_ptr<AbstractFactory> factory1 = std::make_unique<ConcreteFactory1>();
    std::unique_ptr<AbstractProductA> productA1 = factory1->createProductA();
    std::unique_ptr<AbstractProductB> productB1 = factory1->createProductB();
    productA1->use();
    productB1->eat();

    // 使用具体工厂2创建产品A和B
    std::unique_ptr<AbstractFactory> factory2 = std::make_unique<ConcreteFactory2>();
    std::unique_ptr<AbstractProductA> productA2 = factory2->createProductA();
    std::unique_ptr<AbstractProductB> productB2 = factory2->createProductB();
    productA2->use();
    productB2->eat();

    return 0;
}