#include <iostream>
#include <tuple>
#include <string>

int main() {
    // 创建一个包含不同类型的元素的元组
    std::tuple<int, double, std::string> myTuple(42, 3.14, "Hello, World");

    // 获取元组中的元素
    int intElement = std::get<0>(myTuple);
    double doubleElement = std::get<1>(myTuple);
    std::string stringElement = std::get<2>(myTuple);

    // 输出元组的内容
    std::cout << "Tuple elements: " << intElement << ", " << doubleElement << ", " << stringElement << std::endl;

    // 修改元组中的元素
    std::get<0>(myTuple) = 100;
    std::get<2>(myTuple) = "New Value";

    // 再次输出元组的内容
    std::cout << "Modified tuple elements: " << std::get<0>(myTuple) << ", " << std::get<1>(myTuple) << ", " << std::get<2>(myTuple) << std::endl;

    // 使用结构化绑定获取元组中的元素
    auto [intValue, doubleValue, stringValue] = myTuple;
    std::cout << "Structured binding: " << intValue << ", " << doubleValue << ", " << stringValue << std::endl;

    return 0;
}
