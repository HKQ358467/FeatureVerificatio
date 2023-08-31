#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr != nullptr) {
        ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }

    return prev;
}

void printList(ListNode* head) {
    ListNode* curr = head;

    while (curr != nullptr) {
        std::cout << curr->val << " ";
        curr = curr->next;
    }

    std::cout << std::endl;
}

int main() {
    // 创建一个示例链表: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(4);
    ListNode* node5 = new ListNode(5);

    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    std::cout << "原始链表: ";
    printList(head);

    ListNode* reversedHead = reverseList(head);

    std::cout << "逆转后的链表: ";
    printList(reversedHead);

    return 0;
}