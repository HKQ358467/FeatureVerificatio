#include <iostream>
#include <memory>

// 抽象产品类
class Product {
public:
    virtual void use() = 0;
};

// 具体产品类A
class ConcreteProductA : public Product {
public:
    void use() override {
        std::cout << "使用具体产品A" << std::endl;
    }
};

// 具体产品类B
class ConcreteProductB : public Product {
public:
    void use() override {
        std::cout << "使用具体产品B" << std::endl;
    }
};

// 抽象工厂类
class Factory {
public:
    virtual std::unique_ptr<Product> createProduct() = 0;
};

// 具体工厂类A
class ConcreteFactoryA : public Factory {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ConcreteProductA>();
    }
};

// 具体工厂类B
class ConcreteFactoryB : public Factory {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ConcreteProductB>();
    }
};

int main() {
    // 使用具体工厂A创建产品A
    std::unique_ptr<Factory> factoryA = std::make_unique<ConcreteFactoryA>();
    std::unique_ptr<Product> productA = factoryA->createProduct();
    productA->use();

    // 使用具体工厂B创建产品B
    std::unique_ptr<Factory> factoryB = std::make_unique<ConcreteFactoryB>();
    std::unique_ptr<Product> productB = factoryB->createProduct();
    productB->use();

    return 0;
}