#include <iostream>
using namespace std;

void swap(int* a, int* b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int lchild_idx(int i, int len) {
    int idx = 2*i + 1;
    if(idx >= len || i < 0 || i >= len)
        return -1;
    return idx;
}

int rchild_idx(int i, int len) {
    int idx = 2*i + 2;
    if(idx >= len || i < 0 || i >= len)
        return -1;
    return idx;
}

// 非根节点才能求父节点
// idx must with in the len
int parent_idx(int i, int len) {
    if(i <= 0 || i >= len)
        return -1;
    return (i - 1) / 2;
}

void PrintArr(int* arr, int len) {
    for(int i = 0; i<len; i++) 
        cout << arr[i] << ' ';
    cout << endl;
}

void Heapify(int* arr, int len, int i) {
    int curr_idx = i;
    int lc_idx = lchild_idx(curr_idx, len);
    int rc_idx = rchild_idx(curr_idx, len);

    // has both left and right child
    if(lc_idx != -1 && rc_idx != -1) {
        // curr >= lchild and rchild
        if(arr[curr_idx] >= arr[rc_idx] && arr[curr_idx] >= arr[lc_idx]) return;
        // curr < lchild or curr < rchild
        // pick the larger child to swap with curr
        else if(arr[curr_idx] < arr[rc_idx] || arr[curr_idx] < arr[lc_idx]) {
            if(arr[rc_idx] < arr[lc_idx]) {
                swap(&arr[curr_idx], &arr[lc_idx]);
                Heapify(arr, len, lc_idx);
            }
            else {
                swap(&arr[curr_idx], &arr[rc_idx]);
                Heapify(arr, len, rc_idx);
            }
        }
    }
    // has only 1 child, it must be lchild
    else if(lc_idx != -1 && rc_idx == -1) {
        if(arr[lc_idx] <= arr[curr_idx]) return;
        else {
            swap(&arr[lc_idx], &arr[curr_idx]);
            Heapify(arr, len, lc_idx);
        }
    }
    // has no child, leaf node, return
    else
        return;
}


void HeapifyArray(int* arr, int len) {
    int start = len / 2 - 1;
    for(int i = start; i >= 0; i--) 
        Heapify(arr, len, i);
}



int main() {
    int arr[] = {123,12,31,85,35,1512,3,99};
    // int arr[] = {100, 90, 80, 70, 60, 50, 40, 30};
    // int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    // int arr[] = {5, 3, 5, 2, 5, 1, 5};


    int len = sizeof(arr) / sizeof(arr[0]);

    PrintArr(arr, len);

    HeapifyArray(arr, len);

    PrintArr(arr, len);

    return 0;
}