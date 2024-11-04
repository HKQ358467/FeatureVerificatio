#include <iostream>
#include <list>
#include <algorithm> // for std::find

void printList(const std::list<int>& lst) {
    for (const int& item : lst) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 创建一个空的 list
    std::list<int> myList;

    // 在 list 的末尾添加元素
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    std::cout << "List after push_back operations: ";
    printList(myList);

    // 在 list 的开头添加元素
    myList.push_front(5);
    std::cout << "List after push_front operation: ";
    printList(myList);

    // 插入元素到 list 中间
    auto it = std::find(myList.begin(), myList.end(), 20);
    if (it != myList.end()) {
        myList.insert(it, 15);
    }
    std::cout << "List after insert operation: ";
    printList(myList);

    // 删除 list 开头的元素
    myList.pop_front();
    std::cout << "List after pop_front operation: ";
    printList(myList);

    // 删除 list 末尾的元素
    myList.pop_back();
    std::cout << "List after pop_back operation: ";
    printList(myList);

    // 删除特定的元素
    it = std::find(myList.begin(), myList.end(), 15);
    if (it != myList.end()) {
        myList.erase(it);
    }
    std::cout << "List after erase operation: ";
    printList(myList);

    // 清空 list
    myList.clear();
    std::cout << "List after clear operation: ";
    printList(myList);

    return 0;
}
