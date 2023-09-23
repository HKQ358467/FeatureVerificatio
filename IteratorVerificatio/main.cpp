#include <iostream>
#include <vector>
#include <list>

// 抽象迭代器接口
template <typename T>
class Iterator {
public:
    virtual T getNext() = 0;
    virtual bool hasNext() = 0;
};

// 具体迭代器 - 向量迭代器
template <typename T>
class VectorIterator : public Iterator<T> {
private:
    std::vector<T> collection;
    int index = 0;

public:
    VectorIterator(const std::vector<T>& vec) : collection(vec) {}

    T getNext() override {
        return collection[index++];
    }

    bool hasNext() override {
        return index < collection.size();
    }
};

// 具体迭代器 - 链表迭代器
template <typename T>
class ListIterator : public Iterator<T> {
private:
    std::list<T> collection;
    typename std::list<T>::iterator it;

public:
    ListIterator(const std::list<T>& lst) : collection(lst) {
        it = collection.begin();
    }

    T getNext() override {
        return *(it++);
    }

    bool hasNext() override {
        return it != collection.end();
    }
};

// 抽象集合接口
template <typename T>
class Collection {
public:
    virtual Iterator<T>* createIterator() = 0;
};

// 具体集合 - 向量
template <typename T>
class VectorCollection : public Collection<T> {
private:
    std::vector<T> collection;

public:
    void add(const T& item) {
        collection.push_back(item);
    }

    Iterator<T>* createIterator() override {
        return new VectorIterator<T>(collection);
    }
};

// 具体集合 - 链表
template <typename T>
class ListCollection : public Collection<T> {
private:
    std::list<T> collection;

public:
    void add(const T& item) {
        collection.push_back(item);
    }

    Iterator<T>* createIterator() override {
        return new ListIterator<T>(collection);
    }
};

int main() {
    // 创建向量集合
    VectorCollection<int> vectorCollection;
    vectorCollection.add(1);
    vectorCollection.add(2);
    vectorCollection.add(3);

    // 创建链表集合
    ListCollection<std::string> listCollection;
    listCollection.add("apple");
    listCollection.add("banana");
    listCollection.add("cherry");

    // 使用向量迭代器遍历向量集合
    Iterator<int>* vectorIterator = vectorCollection.createIterator();
    std::cout << "Vector Collection:" << std::endl;
    while (vectorIterator->hasNext()) {
        std::cout << vectorIterator->getNext() << " ";
    }
    std::cout << std::endl;

    // 使用链表迭代器遍历链表集合
    Iterator<std::string>* listIterator = listCollection.createIterator();
    std::cout << "List Collection:" << std::endl;
    while (listIterator->hasNext()) {
        std::cout << listIterator->getNext() << " ";
    }
    std::cout << std::endl;

    delete vectorIterator;
    delete listIterator;

    return 0;
}
