#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename T>
class AsyncQueue {
public:
    AsyncQueue() : shutdown(false) {}

    void Push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(item);
        cv.notify_one();
    }

    bool Pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex);
        // 使用while循环防止虚假唤醒
        while (queue.empty() && !shutdown) {
            cv.wait(lock);
        }

        if (!queue.empty()) {
            item = queue.front();
            queue.pop();
            return true;
        }
        return false;
    }

    void Shutdown() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            shutdown = true;
        }
        cv.notify_all();
    }

private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cv;
    bool shutdown;
};

// 测试程序
int main() {
    AsyncQueue<int> asyncQueue;

    // 生产者线程，不断往队列中添加元素
    std::thread producer([&asyncQueue]() {
        for (int i = 0; i < 10000; ++i) {
            asyncQueue.Push(i);
            std::cout << "Produced: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        asyncQueue.Shutdown();
    });

    // 消费者线程，从队列中取出元素并打印
    std::thread consumer([&asyncQueue]() {
        int item;
        while (asyncQueue.Pop(item)) {
            std::cout << "Consumed: " << item << std::endl;
        }
    });

    producer.join();
    consumer.join();

    return 0;
}