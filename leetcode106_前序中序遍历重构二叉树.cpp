#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    TreeNode* lc;
    int data;
    TreeNode* rc;
};

// pre: 前序遍历序列
// in: 中序遍历序列
// n: 在中序遍历序列中搜索的范围
TreeNode* build(int* pre, int* in, int n) {
    if(n <= 0)  return nullptr;
    // 前序遍历的第一个作为根节点
    int root_val = pre[0];
    TreeNode* root = new TreeNode{nullptr, root_val, nullptr};
    // 在中序遍历中找根节点，根据这个节点把序列划分开
    int idx = find(in, in + n, root_val) - in;
    // 递归调用
    root->lc = build(pre+1, in, idx);
    root->rc = build(pre+1+idx, in+idx+1, n-idx-1);
    return root;
}

void CreateFromPostin(TreeNode*& root) {
    int n;
    cin >> n;
    int pre[100], in[100];
    for(int i = 0; i < n; i++) cin >> in[i];
    for(int i = 0; i < n; i++) cin >> pre[i];
    root = build(pre, in, n);
}

void inorder(TreeNode* node) {
    if(node == nullptr) return;
    inorder(node->lc);
    cout << node->data << ' ';
    inorder(node->rc);
}

// test case :
// in : 7 6 9 3 4 5 8 2 1
// pre: 4 7 9 6 3 2 5 8 1
// n = 9
int main() {
    TreeNode* root = nullptr;
    CreateFromPostin(root);
    inorder(root);

    // int arr[5] = {1,2,3,4,5};
    // int* idx = find(arr, arr+5, 4);
    // cout << idx << endl;
    return 0;
}