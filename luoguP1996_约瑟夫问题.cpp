#include <bits/stdc++.h>

// 10 3
// 3 6 9 2 7 1 8 5 10 4

using namespace std;

struct Node{
    int data;
    Node* next;
};

int main() {
    int m = 10, n = 3;
    Node* head = nullptr;
    Node* tail = nullptr;
    for(int i = 0; i < m; i++) {
        Node* newnode = new Node{i+1, nullptr};
        if(head == nullptr && tail == nullptr) {
            head = newnode;
            tail = newnode;
        }
        else {
            tail->next = newnode;
            tail = newnode;
        }
    }
    // for(Node* p = head; p != nullptr; p=p->next) {
    //     cout << p->data << ' ';
    // }
    tail->next = head;          // 成环

    Node* curr = head;          // curr是每次都要删除掉的节点
    Node* prev = tail;
    while(prev->next != prev) {
        for(int i = 0; i < n - 1; curr = curr->next, prev = prev->next, i++);
        cout << curr->data << ' ';
        prev->next = curr->next;
        Node* tmp = curr;
        curr = curr->next;
        delete tmp;
    }

    cout << prev->data;         // 最后还剩下一个元素
    cout << endl;
    return 0;
}