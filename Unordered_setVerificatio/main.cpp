#include <iostream>
#include <unordered_set>

int main() {
    // 创建一个unordered_set
    std::unordered_set<int> mySet;

    // 插入元素
    mySet.insert(10);
    mySet.insert(20);
    mySet.insert(30);

    // 查找元素
    int key = 20;
    if (mySet.find(key) != mySet.end()) {
        std::cout << key << " 存在于unordered_set中" << std::endl;
    } else {
        std::cout << key << " 不存在于unordered_set中" << std::endl;
    }

    // 删除元素
    key = 30;
    if (mySet.erase(key) > 0) {
        std::cout << key << " 已从unordered_set中删除" << std::endl;
    } else {
        std::cout << key << " 不存在于unordered_set中，无法删除" << std::endl;
    }

    // 遍历unordered_set
    std::cout << "unordered_set中的元素：";
    for (const auto& element : mySet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // 获取unordered_set的大小
    std::cout << "unordered_set的大小: " << mySet.size() << std::endl;

    // 检查unordered_set是否为空
    if (mySet.empty()) {
        std::cout << "unordered_set为空" << std::endl;
    } else {
        std::cout << "unordered_set不为空" << std::endl;
    }

    return 0;
}
