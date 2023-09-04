#include <atomic>
#include <thread>
#include <iostream>

template<typename T>
class LockFreeQueue {
public:
    LockFreeQueue(int capacity) : capacity_(capacity), buffer_(new T[capacity]), head_(0), tail_(0) {}

    ~LockFreeQueue() {
        delete[] buffer_;
    }

    bool Enqueue(const T& value) {
        int currentTail = tail_.load(std::memory_order_relaxed);
        int nextTail = (currentTail + 1) % capacity_;

        if (nextTail == head_.load(std::memory_order_acquire)) {
            return false; // Queue is full
        }

        buffer_[currentTail] = value;
        std::atomic_thread_fence(std::memory_order_release); // Memory barrier

        tail_.store(nextTail, std::memory_order_relaxed);

        return true;
    }

    bool Dequeue(T& value) {
        int currentHead = head_.load(std::memory_order_relaxed);

        if (currentHead == tail_.load(std::memory_order_acquire)) {
            return false; // Queue is empty
        }

        value = buffer_[currentHead];
        std::atomic_thread_fence(std::memory_order_release); // Memory barrier

        head_.store((currentHead + 1) % capacity_, std::memory_order_relaxed);

        return true;
    }

private:
    int capacity_;
    T* buffer_;
    alignas(64) std::atomic<int> head_; // Align to cache line boundary
    alignas(64) std::atomic<int> tail_; // Align to cache line boundary
};

void Producer(LockFreeQueue<int>& queue, int numItems) {
    for (int i = 0; i < numItems; ++i) {
        while (!queue.Enqueue(i)) {
            // 如果队列已满，则等待
            std::this_thread::yield();
        }
        std::cout << "Produced: " << i << std::endl;
    }
}

void Consumer(LockFreeQueue<int>& queue, int numItems) {
    for (int i = 0; i < numItems; ++i) {
        int value;
        while (!queue.Dequeue(value)) {
            // 如果队列为空，则等待
            std::this_thread::yield();
        }
        std::cout << "Consumed: " << value << std::endl;
    }
}

int main() {
    const int capacity = 10;
    const int numItems = 20;

    LockFreeQueue<int> queue(capacity);

    std::thread producerThread(Producer, std::ref(queue), numItems);
    std::thread consumerThread(Consumer, std::ref(queue), numItems);

    producerThread.join();
    consumerThread.join();

    return 0;
}