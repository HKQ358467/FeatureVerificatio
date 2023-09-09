#include <iostream>
#include <unordered_map>

class Prototype {
public:
    virtual Prototype* clone() const = 0;
    virtual void printInfo() const = 0;
};

class ConcretePrototypeA : public Prototype {
public:
    Prototype* clone() const override {
        return new ConcretePrototypeA(*this);
    }

    void printInfo() const override {
        std::cout << "This is ConcretePrototypeA" << std::endl;
    }
};

class ConcretePrototypeB : public Prototype {
public:
    Prototype* clone() const override {
        return new ConcretePrototypeB(*this);
    }

    void printInfo() const override {
        std::cout << "This is ConcretePrototypeB" << std::endl;
    }
};

class PrototypeFactory {
private:
    std::unordered_map<std::string, Prototype*> prototypes_;

public:
    PrototypeFactory() {
        prototypes_["A"] = new ConcretePrototypeA();
        prototypes_["B"] = new ConcretePrototypeB();
    }

    ~PrototypeFactory() {
        for (auto& pair : prototypes_) {
            delete pair.second;
        }
    }

    Prototype* createPrototype(const std::string& type) {
        if (prototypes_.find(type) != prototypes_.end()) {
            return prototypes_[type]->clone();
        }
        return nullptr;
    }
};

int main() {
    PrototypeFactory factory;

    Prototype* prototypeA = factory.createPrototype("A");
    if (prototypeA) {
        prototypeA->printInfo();
        delete prototypeA;
    }

    Prototype* prototypeB = factory.createPrototype("B");
    if (prototypeB) {
        prototypeB->printInfo();
        delete prototypeB;
    }

    return 0;
}