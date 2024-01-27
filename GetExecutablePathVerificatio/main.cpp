#include <iostream>
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <windows.h>
#elif __APPLE__ || __linux__ || __unix__ // Mac OS, Linux, and Unix
    #include <unistd.h>
    #include <limits.h>
#endif

std::string GetCurrentExecutablePath() {
    char buffer[PATH_MAX];

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        // Windows代码
        GetModuleFileName(NULL, buffer, PATH_MAX);
    #elif __APPLE__ || __linux__ || __unix__
        // Mac OS, Linux, 或 Unix代码
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
        if (len != -1) {
            buffer[len] = '\0';
        } else {
            // 处理错误
            std::cerr << "Error reading symbolic link /proc/self/exe." << std::endl;
            return "";
        }
    #else
        #error "Unknown compiler, please define your own GetCurrentExecutablePath function."
    #endif

    return std::string(buffer);
}

int main() {
    std::string path = GetCurrentExecutablePath();
    std::cout << "The current executable path is: " << path << std::endl;
    return 0;
}
