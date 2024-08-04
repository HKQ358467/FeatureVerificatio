#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

// 函数声明
std::unordered_map<char, int> buildBadCharTable(const std::string& pattern);
void boyerMooreSearch(const std::string& text, const std::string& pattern);

int main() {
    std::string text = "ABAAABCD";
    std::string pattern = "ABC";

    std::cout << "Text: " << text << std::endl;
    std::cout << "Pattern: " << pattern << std::endl;

    boyerMooreSearch(text, pattern);

    return 0;
}

// 构建坏字符表
std::unordered_map<char, int> buildBadCharTable(const std::string& pattern) {
    std::unordered_map<char, int> badChar;
    int m = pattern.length();

    // 初始化坏字符表
    for (int i = 0; i < m; i++) {
        badChar[pattern[i]] = i;
    }

    return badChar;
}

// Boyer-Moore搜索算法
void boyerMooreSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();

    std::unordered_map<char, int> badChar = buildBadCharTable(pattern);

    int s = 0; // 滑动窗口的起始位置
    while (s <= (n - m)) {
        int j = m - 1;

        // 从右向左匹配
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            std::cout << "Pattern found at index " << s << std::endl;

            // 滑动模式的长度，或者根据坏字符规则滑动
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        } else {
            // 根据坏字符规则滑动
            s += std::max(1, j - badChar[text[s + j]]);
        }
    }
}
