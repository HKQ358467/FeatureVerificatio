#include <iostream>

// 抽象基类，定义了算法的骨架
class CaffeineBeverage {
public:
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) {
            addCondiments();
        }
    }

    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    void boilWater() {
        std::cout << "煮沸水" << std::endl;
    }

    void pourInCup() {
        std::cout << "倒入杯子" << std::endl;
    }

    // 钩子方法，默认为true，子类可以选择性地覆盖
    virtual bool customerWantsCondiments() {
        return true;
    }
};

// 具体子类，实现了特定的步骤
class Coffee : public CaffeineBeverage {
public:
    void brew() override {
        std::cout << "用沸水冲泡咖啡" << std::endl;
    }

    void addCondiments() override {
        std::cout << "加入糖和牛奶" << std::endl;
    }

    // 覆盖钩子方法，选择不添加调料
    bool customerWantsCondiments() override {
        char answer;
        std::cout << "您想要加入糖和牛奶吗？ (y/n): ";
        std::cin >> answer;
        return (answer == 'y' || answer == 'Y');
    }
};

class Tea : public CaffeineBeverage {
public:
    void brew() override {
        std::cout << "用沸水浸泡茶叶" << std::endl;
    }

    void addCondiments() override {
        std::cout << "加入柠檬" << std::endl;
    }
};

int main() {
    CaffeineBeverage* coffee = new Coffee();
    CaffeineBeverage* tea = new Tea();

    std::cout << "制作咖啡：" << std::endl;
    coffee->prepareRecipe();

    std::cout << "\n制作茶：" << std::endl;
    tea->prepareRecipe();

    delete coffee;
    delete tea;

    return 0;
}
