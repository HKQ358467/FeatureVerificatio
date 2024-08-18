#include <iostream>
#include <vector>
#include <string>

// 函数声明
std::vector<int> computeLPSArray(const std::string& pattern);
void KMPSearch(const std::string& text, const std::string& pattern);

int main() {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";

    std::cout << "Text: " << text << std::endl;
    std::cout << "Pattern: " << pattern << std::endl;

    KMPSearch(text, pattern);

    return 0;
}

// 计算最长前缀后缀数组（LPS数组）
std::vector<int> computeLPSArray(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> lps(m);
    int len = 0; // 最长前缀后缀的长度
    lps[0] = 0; // lps[0]总是0

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// KMP搜索算法
void KMPSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();

    std::vector<int> lps = computeLPSArray(pattern);

    int i = 0; // 指向text的索引
    int j = 0; // 指向pattern的索引

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            std::cout << "Found pattern at index " << i - j << std::endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}
