// 求二叉树的任意一个节点的高度

#include <iostream>
#include <queue>

using namespace std;

struct Treenode {
    Treenode* lchild;
    int data;
    Treenode* rchild;
};

// 逐层传入节点的值
void CreateBT(Treenode*& root) {
    int x; 
    queue<Treenode*> fifo;
    cout << "Input root value : ";
    cin >> x;
    root = new Treenode {nullptr, x, nullptr};
    fifo.push(root);
    while(!fifo.empty()) {
        Treenode* tmp = fifo.front();
        cout << "Input lchild value, -1 means you don't want now node to have lchild: ";
        cin >> x;
        if(x != -1) {
            Treenode* newnode = new Treenode {nullptr, x, nullptr};
            tmp->lchild = newnode;
            fifo.push(newnode);
        }
        else 
            tmp->lchild = nullptr;
        cout << "Input rchild value, -1 means you don't want now node to have rchild: ";
        cin >> x;
        if(x != -1) {
            Treenode* newnode = new Treenode {nullptr, x, nullptr};
            tmp->rchild = newnode;
            fifo.push(newnode);
        }
        else
            tmp->rchild = nullptr;
        fifo.pop();
    }
}

void PrintInorder(Treenode* node) {
    if(node == nullptr) return;
    PrintInorder(node->lchild);
    cout << node->data << ' ';
    PrintInorder(node->rchild);
}

// null 高度为-1
// leaf 高度为0
int Getheight(Treenode* node) {
    if(node == nullptr) return -1;
    return max(Getheight(node->lchild), Getheight(node->rchild)) + 1;
}

int main() {
    Treenode* root = nullptr;
    // test case : 10 20 30 15 50 -1 40 -1 -1 -1 -1 70 60 -1 -1 -1 -1
    CreateBT(root);
    PrintInorder(root);

    cout << endl;
    cout << Getheight(root->rchild);
    return 0;
}
