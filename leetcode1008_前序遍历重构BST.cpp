#include <iostream>
#include <stack>

using namespace std;

struct Treenode{
    Treenode* lc;
    int data;
    Treenode* rc;
};

void BSTCreateFromPre(Treenode*& root, int *pre, int n) {
    // using pre[0] create root node
    int i = 1;
    Treenode* curr;
    stack<Treenode*> lifo;
    root = new Treenode{nullptr, pre[0], nullptr};
    curr = root;
    while(i < n) {
        // 待插节点值 < 当前节点值 -> 插左子节点
        if(pre[i] < curr->data) {
            curr->lc = new Treenode{nullptr, pre[i], nullptr};
            lifo.push(curr);
            curr = curr->lc;
            i++;
        }
        // 当前节点 < 待插节点值 < 栈顶节点值， 插右子节点
        else if(pre[i] > curr->data && (!lifo.empty() && pre[i] < lifo.top()->data)) {
            curr->rc = new Treenode{nullptr, pre[i], nullptr};
            curr = curr->rc;
            i++;
        }
        // 栈空直接插右节点
        else if(lifo.empty()) {
            curr->rc = new Treenode{nullptr, pre[i], nullptr};
            curr = curr->rc;
            i++;
        }
        // else，弹栈并将指针移到出栈节点
        else {
            curr = lifo.top();
            lifo.pop();
        }
    }
}

void inOrder(Treenode* node) {
    if(node == nullptr) return;
    inOrder(node->lc);
    cout << node->data << ' ';
    inOrder(node->rc);
}

// test case : 
// 30 20 10 15 25 40 50 45 
//         30
//        /  \
//      20    40
//     /  \     \
//   10   25    50
//     \        /
//     15     45
int main() {
    Treenode* root = nullptr;
    int pre[100];
    int n; 
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> pre[i];
    BSTCreateFromPre(root, pre, n);
    inOrder(root);
    return 0;
}


// #include <iostream>
// using namespace std;

// void setPointer(int* p) { // 必须用引用
//     p = new int(42);      // 让p指向新分配的内存
// }

// int main() {
//     int* ptr = nullptr;
//     setPointer(ptr);      // 传引用，main里的ptr会被修改
//     cout << *ptr << endl; // 输出42
//     delete ptr;
//     return 0;
// }