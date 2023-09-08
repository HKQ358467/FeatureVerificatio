#include <iostream>
#include <string>

class Product {
public:
    void SetPartA(const std::string& partA) {
        partA_ = partA;
    }

    void SetPartB(const std::string& partB) {
        partB_ = partB;
    }

    void SetPartC(const std::string& partC) {
        partC_ = partC;
    }

    void Show() const {
        std::cout << "Part A: " << partA_ << std::endl;
        std::cout << "Part B: " << partB_ << std::endl;
        std::cout << "Part C: " << partC_ << std::endl;
    }

private:
    std::string partA_;
    std::string partB_;
    std::string partC_;
};

class Builder {
public:
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual void BuildPartC() = 0;
    virtual Product GetProduct() = 0;
};

class ConcreteBuilder : public Builder {
public:
    void BuildPartA() override {
        product_.SetPartA("Part A");
    }

    void BuildPartB() override {
        product_.SetPartB("Part B");
    }

    void BuildPartC() override {
        product_.SetPartC("Part C");
    }

    Product GetProduct() override {
        return product_;
    }

private:
    Product product_;
};

class Director {
public:
    void Construct(Builder& builder) {
        builder.BuildPartA();
        builder.BuildPartB();
        builder.BuildPartC();
    }
};

int main() {
    ConcreteBuilder builder;
    Director director;

    director.Construct(builder);
    Product product = builder.GetProduct();

    product.Show();

    return 0;
}