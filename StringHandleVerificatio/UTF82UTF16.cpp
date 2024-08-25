#include <iostream>
#include <string>
#include <codecvt>
#include <locale>
#include <cstdint>

int main() {
    // 使用std::u8string存储一个UTF-8编码的字符串
    std::u8string utf8_string = u8"你好，世界！"; // u8表示UTF-8编码

    // 创建一个UTF-16字符串，用来存储转换后的结果
    std::u16string utf16_string;

    // 使用std::wstring_convert进行编码转换
    // std::codecvt_utf8_utf16是一个专用的转换器，可以在UTF-8和UTF-16之间进行转换
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;

    try {
        // 进行从UTF-8向UTF-16的转换
        utf16_string = convert.from_bytes(reinterpret_cast<const char*>(utf8_string.data()));
    } catch (const std::range_error& e) {
        // 如果转换过程中出现范围错误，则捕获并处理
        std::cerr << "Error during UTF-8 to UTF-16 conversion: " << e.what() << std::endl;
        return 1;
    }

    // 输出原始的UTF-8字符串
    std::cout << "Original UTF-8 string: " << reinterpret_cast<const char*>(utf8_string.data()) << std::endl;

    // 输出转换后的UTF-16字符串
    std::cout << "Converted UTF-16 string (hex representation): ";
    for (char16_t ch : utf16_string) {
        // 将UTF-16字符值以十六进制形式输出，转换为uint16_t以便正确显示
        std::cout << std::hex << std::showbase << static_cast<uint16_t>(ch) << " ";
    }
    std::cout << std::endl;

    return 0;
}
