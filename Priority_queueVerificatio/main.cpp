#include <iostream>
#include <queue>

int main() {
    std::priority_queue<int> myPriorityQueue;

    // 插入元素
    myPriorityQueue.push(30);
    myPriorityQueue.push(10);
    myPriorityQueue.push(50);
    myPriorityQueue.push(20);

    // 访问元素
    std::cout << "Top element: " << myPriorityQueue.top() << std::endl;

    // 删除元素
    myPriorityQueue.pop();

    std::cout << "Top element after pop: " << myPriorityQueue.top() << std::endl;

    // 遍历并输出队列中的元素
    std::cout << "Elements in the priority queue: ";
    while (!myPriorityQueue.empty()) {
        std::cout << myPriorityQueue.top() << " ";
        myPriorityQueue.pop();
    }
    std::cout << std::endl;

    return 0;
}
