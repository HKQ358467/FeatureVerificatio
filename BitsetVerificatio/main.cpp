#include <iostream>
#include <bitset>

int main() {
    // 创建一个长度为8的bitset，初始值为0
    std::bitset<8> bits1;
    std::cout << "bits1: " << bits1 << std::endl;

    // 创建一个长度为8的bitset，初始值为二进制"10101010"
    std::bitset<8> bits2("10101010");
    std::cout << "bits2: " << bits2 << std::endl;

    // 通过整数初始化bitset
    std::bitset<8> bits3(170); // 170的二进制表示为"10101010"
    std::cout << "bits3: " << bits3 << std::endl;

    // 访问bitset中的位
    bool bitValue = bits2[3]; // 获取bits2的第3位的值，应为1
    std::cout << "bits2[3]: " << bitValue << std::endl;

    // 修改bitset中的位
    bits1.set(2); // 将bits1的第2位设置为1
    bits1.reset(5); // 将bits1的第5位设置为0
    bits1.flip(6); // 将bits1的第6位翻转（0变为1，1变为0）
    std::cout << "Modified bits1: " << bits1 << std::endl;

    // 使用位操作
    std::bitset<8> result = bits2 & bits3; // 按位与操作
    std::cout << "bits2 & bits3: " << result << std::endl;

    // 获取位数量
    size_t bitCount = bits2.count(); // 计算bits2中位值为1的数量
    std::cout << "Number of set bits in bits2: " << bitCount << std::endl;

    // 将bitset转换为整数
    int intValue = bits2.to_ulong();
    std::cout << "bits2 as an integer: " << intValue << std::endl;

    return 0;
}
