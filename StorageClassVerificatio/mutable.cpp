#include <iostream>

class Cache {
public:
    Cache(int initialValue) : value(initialValue) {}

    // const 成员函数，用于获取缓存值
    int getValue() const {
        // 在 const 成员函数中修改 mutable 成员变量
        // 这是合法的，因为 value 声明为 mutable
        counter++; // 增加访问计数
        return value;
    }

    // 非 const 成员函数，用于修改缓存值
    void updateValue(int newValue) {
        value = newValue;
        counter = 0; // 重置访问计数
    }

    // 打印访问计数
    void printAccessCount() const {
        std::cout << "Access Count: " << counter << std::endl;
    }

private:
    int value;
    mutable int counter; // mutable 成员变量，允许在 const 成员函数中修改
};

int main() {
    Cache myCache(42);

    std::cout << "Initial Value: " << myCache.getValue() << std::endl;
    myCache.printAccessCount();

    myCache.updateValue(100);
    std::cout << "Updated Value: " << myCache.getValue() << std::endl;
    myCache.printAccessCount();

    return 0;
}
