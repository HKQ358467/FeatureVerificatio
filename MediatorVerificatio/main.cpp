#include <iostream>
#include <string>
#include <vector>

class User;

class ChatMediator {
public:
    virtual void sendMessage(const std::string& message, User* user) = 0;
};

class User {
public:
    User(const std::string& name, ChatMediator* mediator) : name(name), mediator(mediator) {}

    void sendMessage(const std::string& message) {
        mediator->sendMessage(message, this);
    }

    void receiveMessage(const std::string& message) {
        std::cout << name << " received message: " << message << std::endl;
    }

private:
    std::string name;
    ChatMediator* mediator;
};

class ConcreteChatMediator : public ChatMediator {
public:
    void addUser(User* user) {
        users.push_back(user);
    }

    void sendMessage(const std::string& message, User* sender) override {
        for (User* user : users) {
            if (user != sender) {
                user->receiveMessage(message);
            }
        }
    }

private:
    std::vector<User*> users;
};

int main() {
    ConcreteChatMediator chatMediator;

    User user1("Alice", &chatMediator);
    User user2("Bob", &chatMediator);
    User user3("Charlie", &chatMediator);

    chatMediator.addUser(&user1);
    chatMediator.addUser(&user2);
    chatMediator.addUser(&user3);

    user1.sendMessage("Hello, everyone!");
    user2.sendMessage("Hi, Alice!");
    user3.sendMessage("Hey there!");

    return 0;
}
