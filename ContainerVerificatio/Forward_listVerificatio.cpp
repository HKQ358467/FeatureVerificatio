#include <iostream>
#include <forward_list>
#include <algorithm> // for std::find

// 打印 forward_list 的内容
void printForwardList(const std::forward_list<int>& flist) {
    for (const int& item : flist) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 创建一个空的 forward_list
    std::forward_list<int> myForwardList;

    // 在 forward_list 的开头添加元素
    myForwardList.push_front(10);
    myForwardList.push_front(20);
    myForwardList.push_front(30);

    std::cout << "Forward list after push_front operations: ";
    printForwardList(myForwardList);

    // 在 forward_list 中插入元素（在10后面插入15）
    auto it = std::find(myForwardList.begin(), myForwardList.end(), 10);
    if (it != myForwardList.end()) {
        // 因为 forward_list 没有 insert 方法，所以我们使用 insert_after
        myForwardList.insert_after(it, 15);
    }
    std::cout << "Forward list after insert_after operation: ";
    printForwardList(myForwardList);

    // 删除 forward_list 开头的元素
    myForwardList.pop_front();
    std::cout << "Forward list after pop_front operation: ";
    printForwardList(myForwardList);

    // 删除特定的元素（删除15）
    // 需要找到15之前的元素，因为 forward_list 没有直接的 erase 方法
    auto prev_it = myForwardList.before_begin();
    for (it = myForwardList.begin(); it != myForwardList.end(); ++prev_it, ++it) {
        if (*it == 15) {
            myForwardList.erase_after(prev_it);
            break;
        }
    }
    std::cout << "Forward list after erase_after operation: ";
    printForwardList(myForwardList);

    // 清空 forward_list
    myForwardList.clear();
    std::cout << "Forward list after clear operation: ";
    printForwardList(myForwardList);

    return 0;
}
