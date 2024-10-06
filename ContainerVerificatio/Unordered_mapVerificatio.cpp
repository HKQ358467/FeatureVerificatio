#include <iostream>
#include <unordered_map>

int main() {
    // 创建一个unordered_map对象，将整数映射到字符串
    std::unordered_map<int, std::string> myMap;

    // 插入键值对
    myMap[1] = "One";
    myMap[2] = "Two";
    myMap[3] = "Three";
    myMap[4] = "Four";

    // 查找元素
    int keyToFind = 2;
    auto it = myMap.find(keyToFind);
    if (it != myMap.end()) {
        std::cout << "Key " << keyToFind << " is mapped to: " << it->second << std::endl;
    } else {
        std::cout << "Key " << keyToFind << " not found in the unordered_map." << std::endl;
    }

    // 删除元素
    int keyToRemove = 3;
    size_t numErased = myMap.erase(keyToRemove);
    if (numErased > 0) {
        std::cout << "Key " << keyToRemove << " and its value are removed from the unordered_map." << std::endl;
    } else {
        std::cout << "Key " << keyToRemove << " not found in the unordered_map. Nothing to erase." << std::endl;
    }

    // 遍历unordered_map中的所有元素
    std::cout << "All elements in the unordered_map:" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return 0;
}
