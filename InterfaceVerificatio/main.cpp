#include <iostream>

// 定义一个接口（抽象类），表示形状
class Shape {
public:
    // 纯虚函数，表示派生类必须实现这个方法
    virtual double area() const = 0;

    // 虚析构函数，用于安全释放资源
    virtual ~Shape() {
        std::cout << "Shape 的析构函数被调用" << std::endl;
    }
};

// 实现接口的第一个类：圆形
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    // 实现接口中的纯虚函数
    double area() const override {
        return 3.14159265359 * radius * radius;
    }

    // 析构函数
    ~Circle() {
        std::cout << "Circle 的析构函数被调用" << std::endl;
    }
};

// 实现接口的第二个类：矩形
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    // 实现接口中的纯虚函数
    double area() const override {
        return width * height;
    }

    // 析构函数
    ~Rectangle() {
        std::cout << "Rectangle 的析构函数被调用" << std::endl;
    }
};

int main() {
    // 创建两个不同的形状对象
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);

    // 创建一个形状指针数组，并将不同形状对象的地址存储在其中
    Shape* shapes[2];
    shapes[0] = &circle;
    shapes[1] = &rectangle;

    // 遍历形状对象，计算并输出它们的面积
    for (int i = 0; i < 2; ++i) {
        std::cout << "形状 " << i + 1 << " 的面积是: " << shapes[i]->area() << std::endl;
    }

    return 0;
}
