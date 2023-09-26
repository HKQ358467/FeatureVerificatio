#include <iostream>
#include <vector>
#include <string>
#include <ctime>

// Originator: 原始对象，需要保存状态
class Document {
private:
    std::string content;
    std::time_t lastModified;

public:
    Document(const std::string& initialContent) : content(initialContent), lastModified(std::time(0)) {}

    void edit(const std::string& newContent) {
        content = newContent;
        lastModified = std::time(0);
    }

    std::string getContent() const {
        return content;
    }

    std::time_t getLastModifiedTime() const {
        return lastModified;
    }

    // 创建备忘录对象以保存当前状态
    class Memento {
    private:
        std::string savedContent;
        std::time_t savedTime;

    public:
        Memento(const std::string& content, std::time_t time) : savedContent(content), savedTime(time) {}

        std::string getContent() const {
            return savedContent;
        }

        std::time_t getTime() const {
            return savedTime;
        }
    };

    // 保存当前状态到备忘录
    Memento save() const {
        return Memento(content, lastModified);
    }

    // 从备忘录中恢复状态
    void restore(const Memento& memento) {
        content = memento.getContent();
        lastModified = memento.getTime();
    }
};

// Caretaker: 管理备忘录
class History {
private:
    std::vector<Document::Memento> mementos;

public:
    void push(const Document::Memento& memento) {
        mementos.push_back(memento);
    }

    Document::Memento pop() {
        if (!mementos.empty()) {
            Document::Memento top = mementos.back();
            mementos.pop_back();
            return top;
        }
        throw std::runtime_error("No more mementos in history.");
    }
};

int main() {
    Document document("Initial content.");
    History history;

    // 修改文档并保存备忘录
    document.edit("Updated content.");
    history.push(document.save());

    // 再次修改文档
    document.edit("More changes.");
    history.push(document.save());

    // 恢复到之前的状态
    Document::Memento previousState = history.pop();
    document.restore(previousState);

    std::cout << "Current Content: " << document.getContent() << std::endl;
    std::cout << "Last Modified Time: " << std::ctime(&document.getLastModifiedTime()) << std::endl;

    return 0;
}
