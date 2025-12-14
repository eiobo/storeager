// #include <iostream>
// #include <queue>
// #include <stack>

// using namespace std;

// struct TreeNode{
//     TreeNode* lchild;
//     int data;
//     TreeNode* rchild;
// };

// TreeNode* root;             // global variable

// void CreateBT() {
//     TreeNode *p, *tmp;
//     int x;
//     queue<TreeNode*> fifo;
//     cout << "Enter root value : ";
//     cin >> x;
//     root = new TreeNode{nullptr, x, nullptr};
//     fifo.push(root);
//     while (!fifo.empty()) {
//         p = fifo.front();
//         fifo.pop();
//         cout << "Enter lchild value, enter `-1` means you don't want this node to have lchild node : ";
//         cin >> x;
//         if(x != -1) {                                       // enter -1 means you want tempory node don't have left child
//             tmp = new TreeNode{nullptr, x, nullptr};
//             p->lchild = tmp;
//             fifo.push(tmp);
//         }
//         cout << "Enter rchild value, enter `-1` means you don't want this node to have rchild node : ";
//         cin >> x;
//         if(x != -1) {                                       // enter -1 means you want tempory node don't have left child
//             tmp = new TreeNode{nullptr, x, nullptr};
//             p->rchild = tmp;
//             fifo.push(tmp);
//         }
//     }
// }

// void PreOrder(TreeNode* node) {
//     if(node != nullptr) {
//         cout << node->data << " ";
//         PreOrder(node->lchild);
//         PreOrder(node->rchild);
//     }
// }


// int main() {
//     // queue<int> q;
//     // q.push(100);
//     // q.push(20);
//     // q.push(1123);

//     // cout << q.front() << endl;
//     // cout << q.back() << endl;

//     CreateBT();
//     PreOrder(root);
//     return 0;
// }

#include <iostream>
#include <queue>
#include <stack>

using namespace std;


void allset_zero(int* arr, int len) {
    for(int i = 0; i < len; i++) {
        arr[i] = 0;
    }
}

int main() {
    int arr[5] = {1,2,3,4,5};
    // cout << *arr << endl;
    // allset_zero(arr, 5);
    // cout << *(arr + 3) << endl;
    cout << arr << endl;                // 数组名是数组首元素的指针，是int* 型
    cout << &arr << endl;               // 这个是取首元素的地址
    cout << &arr[0] << endl;            // arr[0]是int型，而&arr[0]是取int型的地址，所以&arr[0]int* 变量
    return 0;
}