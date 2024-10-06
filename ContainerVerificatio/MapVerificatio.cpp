#include <iostream>
#include <map>
#include <string>

int main() {
    // 创建一个 std::map 容器，用于存储学生的成绩，键为学生姓名（字符串），值为分数（整数）
    std::map<std::string, int> studentScores;

    // 插入元素到 map
    studentScores["Alice"] = 95;
    studentScores["Bob"] = 87;
    studentScores["Charlie"] = 92;
    studentScores["David"] = 78;

    // 使用 insert 函数插入元素
    studentScores.insert(std::make_pair("Eve", 88));

    // 使用 pair 类型插入元素
    studentScores.insert(std::pair<std::string, int>("Frank", 76));

    // 使用迭代器遍历 map，并输出键值对
    std::cout << "Student Scores:\n";
    for (const auto& pair : studentScores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 检查是否存在特定键
    std::string searchName = "Alice";
    if (studentScores.find(searchName) != studentScores.end()) {
        std::cout << searchName << " found. Score: " << studentScores[searchName] << std::endl;
    } else {
        std::cout << searchName << " not found." << std::endl;
    }

    // 删除元素
    std::string removeName = "Charlie";
    auto it = studentScores.find(removeName);
    if (it != studentScores.end()) {
        studentScores.erase(it);
        std::cout << removeName << " removed from the map." << std::endl;
    } else {
        std::cout << removeName << " not found in the map." << std::endl;
    }

    // 检查 map 是否为空
    if (studentScores.empty()) {
        std::cout << "The map is empty." << std::endl;
    } else {
        std::cout << "The map is not empty." << std::endl;
    }

    // 获取 map 的大小
    std::cout << "Size of the map: " << studentScores.size() << std::endl;

    return 0;
}
