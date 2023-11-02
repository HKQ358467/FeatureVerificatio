#include <iostream>
#include <fstream>
#include <string>

// 自定义异常类，继承自标准异常类，用于表示文件不存在异常
class FileNotExistException : public std::exception {
public:
    // 重写父类的what()方法，提供异常信息
    const char* what() const noexcept {
        return "文件不存在异常：文件未找到。";
    }
};

int main() {
    std::string filename = "nonexistent.txt";

    try {
        // 尝试打开文件
        std::ifstream file(filename);

        // 如果文件打开失败，抛出自定义异常
        if (!file.is_open()) {
            throw FileNotExistException();
        }

        // 这里可以处理文件操作，但在本示例中不需要

        // 关闭文件
        file.close();
    } catch (const FileNotExistException& ex) {
        // 捕获FileNotExistException异常
        std::cerr << "捕获到异常：" << ex.what() << std::endl;
    } catch (const std::exception& ex) {
        // 捕获其他标准异常
        std::cerr << "捕获到标准异常：" << ex.what() << std::endl;
    } catch (...) {
        // 捕获所有其他异常
        std::cerr << "捕获到未知异常" << std::endl;
    }

    std::cout << "程序继续执行..." << std::endl;

    return 0;
}
