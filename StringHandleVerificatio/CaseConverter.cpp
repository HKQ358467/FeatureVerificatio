#include <iostream>  // 包含标准输入输出流库，用于输入输出
#include <string>    // 包含字符串库，用于字符串操作
#include <cctype>    // 包含字符处理库，用于字符转换操作

// 函数声明
std::string toUpperCase(const std::string& str);
std::string toLowerCase(const std::string& str);

int main() {
    // 提示用户输入一个字符串
    std::cout << "请输入一个字符串: ";
    std::string input;
    std::getline(std::cin, input);  // 读取整行输入，包含空格

    // 将字符串转换为大写
    std::string upper = toUpperCase(input);
    // 将字符串转换为小写
    std::string lower = toLowerCase(input);

    // 输出转换后的结果
    std::cout << "大写转换: " << upper << std::endl;
    std::cout << "小写转换: " << lower << std::endl;

    return 0;
}

// 将字符串转换为大写的函数
std::string toUpperCase(const std::string& str) {
    std::string result;
    result.reserve(str.size());  // 预分配足够的空间，提高效率

    // 遍历字符串的每一个字符
    for (char ch : str) {
        // 使用std::toupper函数将字符转换为大写
        result += std::toupper(static_cast<unsigned char>(ch));
    }

    return result;
}

// 将字符串转换为小写的函数
std::string toLowerCase(const std::string& str) {
    std::string result;
    result.reserve(str.size());  // 预分配足够的空间，提高效率

    // 遍历字符串的每一个字符
    for (char ch : str) {
        // 使用std::tolower函数将字符转换为小写
        result += std::tolower(static_cast<unsigned char>(ch));
    }

    return result;
}
