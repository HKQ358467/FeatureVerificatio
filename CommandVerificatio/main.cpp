#include <iostream>
#include <vector>

// 命令接口
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

// 接收者类，实际执行操作的对象
class Receiver {
public:
    void performAction1() {
        std::cout << "Receiver: Performing Action 1" << std::endl;
    }

    void performAction2() {
        std::cout << "Receiver: Performing Action 2" << std::endl;
    }
};

// 具体命令类，实现了Command接口
class ConcreteCommand1 : public Command {
private:
    Receiver* receiver;

public:
    ConcreteCommand1(Receiver* rec) : receiver(rec) {}

    void execute() override {
        receiver->performAction1();
    }
};

class ConcreteCommand2 : public Command {
private:
    Receiver* receiver;

public:
    ConcreteCommand2(Receiver* rec) : receiver(rec) {}

    void execute() override {
        receiver->performAction2();
    }
};

// 调用者类，负责执行命令
class Invoker {
private:
    std::vector<Command*> commands;

public:
    void addCommand(Command* cmd) {
        commands.push_back(cmd);
    }

    void executeCommands() {
        for (Command* cmd : commands) {
            cmd->execute();
        }
        commands.clear();
    }
};

int main() {
    // 创建接收者对象
    Receiver* receiver = new Receiver();

    // 创建具体命令对象
    Command* command1 = new ConcreteCommand1(receiver);
    Command* command2 = new ConcreteCommand2(receiver);

    // 创建调用者对象
    Invoker invoker;

    // 将命令添加到调用者队列
    invoker.addCommand(command1);
    invoker.addCommand(command2);

    // 执行命令
    invoker.executeCommands();

    // 释放资源
    delete receiver;
    delete command1;
    delete command2;

    return 0;
}
