#include <iostream>
#include <set>

int main() {
    // 创建一个std::set容器
    std::set<int> mySet;

    // 插入元素
    mySet.insert(5);
    mySet.insert(2);
    mySet.insert(8);
    mySet.insert(1);

    // 插入重复元素（不会被插入）
    mySet.insert(2);

    // 查看容器大小
    std::cout << "Size of mySet: " << mySet.size() << std::endl;

    // 遍历并输出元素
    std::cout << "Elements in mySet:";
    for (const int& element : mySet) {
        std::cout << " " << element;
    }
    std::cout << std::endl;

    // 查找元素
    int key = 8;
    std::set<int>::iterator it = mySet.find(key);
    if (it != mySet.end()) {
        std::cout << key << " found in mySet." << std::endl;
    } else {
        std::cout << key << " not found in mySet." << std::endl;
    }

    // 删除元素
    mySet.erase(2);

    // 遍历并输出修改后的元素
    std::cout << "Elements in mySet after erasing 2:";
    for (const int& element : mySet) {
        std::cout << " " << element;
    }
    std::cout << std::endl;

    return 0;
}
