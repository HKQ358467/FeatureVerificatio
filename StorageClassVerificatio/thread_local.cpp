#include <iostream>
#include <thread>

// 定义一个全局的thread_local变量
thread_local int threadLocalVariable = 0;

// 线程函数，将线程局部变量增加并显示
void ThreadFunction(int threadId) {
    threadLocalVariable += 1;
    std::cout << "Thread " << threadId << ": threadLocalVariable = " << threadLocalVariable << std::endl;
}

int main() {
    // 创建两个线程
    std::thread t1(ThreadFunction, 1);
    std::thread t2(ThreadFunction, 2);

    // 等待线程完成
    t1.join();
    t2.join();

    // 在主线程中访问线程局部变量
    threadLocalVariable += 10;
    std::cout << "Main Thread: threadLocalVariable = " << threadLocalVariable << std::endl;

    return 0;
}
