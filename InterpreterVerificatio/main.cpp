#include <iostream>
#include <stack>
#include <string>
#include <map>

// 抽象表达式类
class Expression {
public:
    virtual int interpret(std::map<char, int>& context) = 0;
    virtual ~Expression() {}
};

// 终结符表达式类
class TerminalExpression : public Expression {
private:
    char variable;

public:
    TerminalExpression(char variable) : variable(variable) {}

    int interpret(std::map<char, int>& context) override {
        return context[variable];
    }
};

// 非终结符表达式类（加法）
class AddExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    AddExpression(Expression* left, Expression* right) : left(left), right(right) {}

    int interpret(std::map<char, int>& context) override {
        return left->interpret(context) + right->interpret(context);
    }

    ~AddExpression() {
        delete left;
        delete right;
    }
};

// 非终结符表达式类（减法）
class SubtractExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    SubtractExpression(Expression* left, Expression* right) : left(left), right(right) {}

    int interpret(std::map<char, int>& context) override {
        return left->interpret(context) - right->interpret(context);
    }

    ~SubtractExpression() {
        delete left;
        delete right;
    }
};

int main() {
    // 创建上下文，映射变量到值
    std::map<char, int> context;
    context['a'] = 5;
    context['b'] = 10;

    // 构建表达式解析树
    Expression* expression = new SubtractExpression(
            new TerminalExpression('b'),
            new AddExpression(
                    new TerminalExpression('a'),
                    new TerminalExpression('a')
            )
    );

    // 解释并计算表达式
    int result = expression->interpret(context);

    std::cout << "解释器计算结果: " << result << std::endl;

    delete expression;

    return 0;
}
