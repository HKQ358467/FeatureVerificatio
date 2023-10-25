#include <iostream>
#include <queue>

int main() {
    // 创建一个整数队列
    std::queue<int> myQueue;

    // 向队列中添加元素
    myQueue.push(10);
    myQueue.push(20);
    myQueue.push(30);

    // 访问队列的前端元素
    std::cout << "Front element of the queue: " << myQueue.front() << std::endl;

    // 移除队列的前端元素
    myQueue.pop();

    // 再次访问队列的前端元素
    std::cout << "Front element of the queue after pop: " << myQueue.front() << std::endl;

    // 检查队列是否为空
    if (myQueue.empty()) {
        std::cout << "Queue is empty." << std::endl;
    } else {
        std::cout << "Queue is not empty." << std::endl;
    }

    // 获取队列的大小
    std::cout << "Queue size: " << myQueue.size() << std::endl;

    // 输出队列中的所有元素
    while (!myQueue.empty()) {
        std::cout << "Queue element: " << myQueue.front() << std::endl;
        myQueue.pop();
    }

    return 0;
}
