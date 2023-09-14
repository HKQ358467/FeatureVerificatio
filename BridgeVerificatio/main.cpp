#include <iostream>
#include <string>

// Abstract base class for the implementation
class Implementor {
public:
    virtual void operationImpl() = 0;
};

// Concrete implementation classes
class ConcreteImplementorA : public Implementor {
public:
    void operationImpl() override {
        std::cout << "ConcreteImplementorA operation" << std::endl;
    }
};

class ConcreteImplementorB : public Implementor {
public:
    void operationImpl() override {
        std::cout << "ConcreteImplementorB operation" << std::endl;
    }
};

// Abstract base class for the abstraction
class Abstraction {
protected:
    Implementor* implementor;

public:
    Abstraction(Implementor* impl) : implementor(impl) {}

    virtual void operation() = 0;
};

// Refined abstraction classes
class RefinedAbstractionA : public Abstraction {
public:
    RefinedAbstractionA(Implementor* impl) : Abstraction(impl) {}

    void operation() override {
        std::cout << "RefinedAbstractionA operation" << std::endl;
        implementor->operationImpl();
    }
};

class RefinedAbstractionB : public Abstraction {
public:
    RefinedAbstractionB(Implementor* impl) : Abstraction(impl) {}

    void operation() override {
        std::cout << "RefinedAbstractionB operation" << std::endl;
        implementor->operationImpl();
    }
};

int main() {
    // Create concrete implementor objects
    ConcreteImplementorA* implA = new ConcreteImplementorA();
    ConcreteImplementorB* implB = new ConcreteImplementorB();

    // Create refined abstraction objects with different implementors
    RefinedAbstractionA* refinedA = new RefinedAbstractionA(implA);
    RefinedAbstractionB* refinedB = new RefinedAbstractionB(implB);

    // Call operations on the refined abstractions
    refinedA->operation();
    refinedB->operation();

    // Clean up memory
    delete refinedA;
    delete refinedB;
    delete implA;
    delete implB;

    return 0;
}