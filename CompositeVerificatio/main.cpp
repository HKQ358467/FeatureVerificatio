#include <iostream>
#include <string>
#include <vector>

// Component 抽象基类
class OrganizationComponent {
public:
    OrganizationComponent(const std::string& name) : name(name) {}

    virtual void display(int depth) = 0;

protected:
    std::string name;
};

// Leaf 叶节点 - 员工
class Employee : public OrganizationComponent {
public:
    Employee(const std::string& name) : OrganizationComponent(name) {}

    void display(int depth) override {
        std::string indentation(depth, '-');
        std::cout << indentation << " Employee: " << name << std::endl;
    }
};

// Composite 容器节点 - 部门
class Department : public OrganizationComponent {
public:
    Department(const std::string& name) : OrganizationComponent(name) {}

    void add(OrganizationComponent* component) {
        children.push_back(component);
    }

    void display(int depth) override {
        std::string indentation(depth, '-');
        std::cout << indentation << " Department: " << name << std::endl;
        for (OrganizationComponent* component : children) {
            component->display(depth + 2);
        }
    }

private:
    std::vector<OrganizationComponent*> children;
};

int main() {
    // 创建员工
    Employee emp1("John");
    Employee emp2("Alice");
    Employee emp3("Bob");

    // 创建部门
    Department hr("HR");
    Department engineering("Engineering");

    // 向部门中添加员工
    hr.add(&emp1);
    hr.add(&emp2);
    engineering.add(&emp3);

    // 创建总公司
    Department company("XYZ Company");

    // 向总公司中添加部门
    company.add(&hr);
    company.add(&engineering);

    // 显示整个组织结构
    company.display(0);

    return 0;
}
