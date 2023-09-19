#include <iostream>
#include <string>
#include <unordered_map>

// 享元（Flyweight）接口
class Character {
public:
    virtual void display() = 0;
};

// 具体享元类
class ConcreteCharacter : public Character {
private:
    char character;

public:
    ConcreteCharacter(char c) : character(c) {}

    void display() override {
        std::cout << character;
    }
};

// 享元工厂类
class CharacterFactory {
private:
    std::unordered_map<char, Character*> characters;

public:
    Character* getCharacter(char c) {
        if (characters.find(c) == characters.end()) {
            characters[c] = new ConcreteCharacter(c);
        }
        return characters[c];
    }
};

// 文本编辑器类，用于处理文本
class TextEditor {
private:
    std::string text;
    CharacterFactory characterFactory;

public:
    TextEditor(const std::string& initialText) : text(initialText) {}

    void displayText() {
        for (char c : text) {
            Character* character = characterFactory.getCharacter(c);
            character->display();
        }
        std::cout << std::endl;
    }

    void appendText(const std::string& newText) {
        text += newText;
    }
};

int main() {
    // 创建文本编辑器并初始化文本
    TextEditor editor("Hello, ");

    // 显示初始文本
    editor.displayText();

    // 添加新文本
    editor.appendText("World!");

    // 显示新文本
    editor.displayText();

    return 0;
}
