#include <iostream>
#include <deque>

int main() {
    std::deque<int> myDeque; // 创建一个空的deque集合

    // 在deque的后面插入元素
    myDeque.push_back(10);
    myDeque.push_back(20);
    myDeque.push_back(30);

    // 在deque的前面插入元素
    myDeque.push_front(5);
    myDeque.push_front(15);

    // 遍历deque并打印元素
    std::cout << "Deque elements: ";
    for (const int &value : myDeque) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // 删除deque的前面和后面的元素
    myDeque.pop_front();
    myDeque.pop_back();

    // 再次遍历并打印deque的元素
    std::cout << "Updated Deque elements: ";
    for (const int &value : myDeque) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
