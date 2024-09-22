#include <iostream>
#include <map>

int main() {
    // 创建一个 multimap 容器
    std::multimap<int, std::string> studentMap;

    // 插入元素
    studentMap.insert(std::pair<int, std::string>(101, "Alice"));
    studentMap.insert(std::pair<int, std::string>(102, "Bob"));
    studentMap.insert(std::pair<int, std::string>(103, "Charlie"));
    studentMap.insert(std::pair<int, std::string>(101, "David")); // 允许重复键

    // 遍历 multimap 并输出元素
    std::cout << "Multimap Elements:" << std::endl;
    for (const auto& student : studentMap) {
        std::cout << "ID: " << student.first << ", Name: " << student.second << std::endl;
    }

    // 查找元素
    int searchId = 101;
    std::cout << "Students with ID " << searchId << ":" << std::endl;
    auto range = studentMap.equal_range(searchId);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << "ID: " << it->first << ", Name: " << it->second << std::endl;
    }

    // 删除元素
    studentMap.erase(searchId);

    // 再次遍历 multimap 并输出元素
    std::cout << "Multimap Elements after deletion:" << std::endl;
    for (const auto& student : studentMap) {
        std::cout << "ID: " << student.first << ", Name: " << student.second << std::endl;
    }

    return 0;
}
