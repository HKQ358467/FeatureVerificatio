#include <iostream>
#include <string>

// 接口类
class Logger {
public:
    virtual void log(const std::string& message) = 0;
};

// 真实主题类
class FileLogger : public Logger {
public:
    void log(const std::string& message) override {
        std::cout << "Logging to file: " << message << std::endl;
    }
};

// 代理类
class LoggerProxy : public Logger {
private:
    Logger* logger;

public:
    LoggerProxy() {
        logger = new FileLogger();
    }

    ~LoggerProxy() {
        delete logger;
    }

    void log(const std::string& message) override {
        // 在调用真实主题之前可以执行一些额外的操作
        std::cout << "Preparing to log..." << std::endl;

        // 调用真实主题的方法
        logger->log(message);

        // 在调用真实主题之后可以执行一些额外的操作
        std::cout << "Logging completed." << std::endl;
    }
};

int main() {
    // 创建代理对象
    LoggerProxy loggerProxy;

    // 通过代理对象调用方法
    loggerProxy.log("Hello, world!");

    return 0;
}