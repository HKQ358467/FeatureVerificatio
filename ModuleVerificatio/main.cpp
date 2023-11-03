#include <iostream>
#include <cmath>

// 定义一个模板函数，用于交换两个值
template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 定义一个模板类，用于表示一个二维向量
template <typename T>
class Vector2D {
private:
    T x;
    T y;

public:
    Vector2D(T x, T y) : x(x), y(y) {}

    // 获取向量的X分量
    T getX() const {
        return x;
    }

    // 获取向量的Y分量
    T getY() const {
        return y;
    }

    // 设置向量的X分量
    void setX(T newX) {
        x = newX;
    }

    // 设置向量的Y分量
    void setY(T newY) {
        y = newY;
    }

    // 计算向量的长度
    double length() const {
        return std::sqrt(x * x + y * y);
    }

    // 重载加法运算符
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // 重载输出运算符
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};

int main() {
    // 演示模板函数
    int a = 5, b = 10;
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    swapValues(a, b);
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;

    // 演示模板类
    Vector2D<double> vec1(3.0, 4.0);
    Vector2D<double> vec2(1.0, 2.0);
    std::cout << "vec1 = " << vec1 << std::endl;
    std::cout << "vec2 = " << vec2 << std::endl;
    Vector2D<double> vec3 = vec1 + vec2;
    std::cout << "vec1 + vec2 = " << vec3 << std::endl;
    std::cout << "Length of vec1: " << vec1.length() << std::endl;

    return 0;
}