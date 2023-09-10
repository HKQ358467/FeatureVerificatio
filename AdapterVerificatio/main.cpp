#include <iostream>

// 旧的接口
class OldInterface {
public:
    virtual void oldMethod() = 0;
};

// 旧的实现类
class OldImplementation : public OldInterface {
public:
    void oldMethod() override {
        std::cout << "Calling oldMethod() from OldImplementation" << std::endl;
    }
};

// 新的接口
class NewInterface {
public:
    virtual void newMethod() = 0;
};

// 新的实现类
class NewImplementation : public NewInterface {
public:
    void newMethod() override {
        std::cout << "Calling newMethod() from NewImplementation" << std::endl;
    }
};

// 适配器类
class Adapter : public NewInterface {
private:
    OldInterface* oldInterface;

public:
    Adapter(OldInterface* oldInterface) : oldInterface(oldInterface) {}

    void newMethod() override {
        std::cout << "Calling newMethod() through Adapter" << std::endl;
        oldInterface->oldMethod();
    }
};

int main() {
    // 创建旧的实现类对象
    OldImplementation oldImplementation;

    // 创建适配器对象，将旧的实现类对象传入适配器构造函数
    Adapter adapter(&oldImplementation);

    // 调用新的接口方法，实际上会通过适配器调用旧的接口方法
    adapter.newMethod();

    return 0;
}