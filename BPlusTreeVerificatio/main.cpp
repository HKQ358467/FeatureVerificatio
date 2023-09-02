#include <iostream>
#include <vector>

// B+树节点的定义
struct BPlusTreeNode {
    std::vector<int> keys;
    std::vector<BPlusTreeNode*> children;
    bool isLeaf;

    BPlusTreeNode() {
        isLeaf = false;
    }
};

// B+树的定义
class BPlusTree {
private:
    BPlusTreeNode* root;

public:
    BPlusTree() {
        root = nullptr;
    }

    // 插入键值对
    void insert(int key) {
        if (root == nullptr) {
            root = new BPlusTreeNode();
            root->isLeaf = true;
            root->keys.push_back(key);
        } else {
            // 在适当的叶子节点插入键值对
            insertInLeaf(root, key);
        }
    }

    // 在叶子节点中插入键值对
    void insertInLeaf(BPlusTreeNode* node, int key) {
        // 找到插入位置
        int i = 0;
        while (i < node->keys.size() && node->keys[i] < key) {
            i++;
        }

        // 在插入位置插入键值对
        node->keys.insert(node->keys.begin() + i, key);
    }

    // 打印B+树
    void print() {
        printNode(root);
    }

    // 递归打印节点
    void printNode(BPlusTreeNode* node) {
        if (node == nullptr) {
            return;
        }

        // 打印节点的键值对
        for (int i = 0; i < node->keys.size(); i++) {
            std::cout << node->keys[i] << " ";
        }
        std::cout << std::endl;

        // 递归打印子节点
        if (!node->isLeaf) {
            for (int i = 0; i < node->children.size(); i++) {
                printNode(node->children[i]);
            }
        }
    }

    // 查找键值对
    bool search(int key) {
        return searchNode(root, key);
    }

    // 在节点中查找键值对
    bool searchNode(BPlusTreeNode* node, int key) {
        if (node == nullptr) {
            return false;
        }

        // 在节点中查找键值对
        int i = 0;
        while (i < node->keys.size() && node->keys[i] < key) {
            i++;
        }

        // 如果找到键值对，则返回true
        if (i < node->keys.size() && node->keys[i] == key) {
            return true;
        }

        // 如果是叶子节点，则表示未找到键值对
        if (node->isLeaf) {
            return false;
        }

        // 递归在子节点中查找键值对
        return searchNode(node->children[i], key);
    }
};

int main() {
    BPlusTree tree;

    // 插入一些键值对
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);

    // 打印B+树
    std::cout << "B+树的内容：" << std::endl;
    tree.print();

    // 查找键值对
    int keyToSearch = 15;
    bool found = tree.search(keyToSearch);
    if (found) {
        std::cout << "键值对 " << keyToSearch << " 存在于B+树中。" << std::endl;
    } else {
        std::cout << "键值对 " << keyToSearch << " 不存在于B+树中。" << std::endl;
    }

    return 0;
}