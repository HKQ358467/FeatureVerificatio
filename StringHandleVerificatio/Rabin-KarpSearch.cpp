#include <iostream>
#include <string>
#include <vector>

const int d = 256;  // 字母表的大小
const int q = 101;  // 一个大素数，用于计算哈希值

// Rabin-Karp算法
void rabinKarpSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    int p = 0;  // 模式的哈希值
    int t = 0;  // 文本的哈希值
    int h = 1;  // 用于计算哈希值的权重

    // 计算h的值,h相当于d^(m-1)
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // 计算模式和文本的初始哈希值
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // 滑动模式，进行比较
    for (int i = 0; i <= n - m; i++) {
        // 如果当前哈希值匹配，进一步检查字符
        if (p == t) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                std::cout << "Pattern found at index " << i << std::endl;
            }
        }

        // 计算下一个窗口的哈希值
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // 确保t是正数
            if (t < 0) {
                t = t + q;
            }
        }
    }
}

int main() {
    std::string text = "GEEKS FOR GEEKS";
    std::string pattern = "GEEK";

    std::cout << "Text: " << text << std::endl;
    std::cout << "Pattern: " << pattern << std::endl;

    rabinKarpSearch(text, pattern);

    return 0;
}
