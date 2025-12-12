#include <bits/stdc++.h>
using namespace std;

// 类可以定义空类，只占1byte
// 空类也必须有非零大小（通常是 1 字节），以保证每个对象都有唯一地址。
class Empty {};

// 对象：Animal dog   （&dog 起始地址）
// 偏移（bytes）:  0                   8                  16
//                 +-------------------+------------------+
//  offset 0..7    | vptr (8 bytes)    |  指向 vtable 的指针 |
//  offset 8..11   | legs (int, 4B)    |
//  offset 12..15  | padding (4B)      | （对齐） 
//                 +-------------------+------------------+
class Animal {
public:
    int legs;
    virtual void speak();           // 只要有了虚函数，就会有一个虚函数表指针vptr，在64位系统地址变量都占8B
    virtual void run(int i);
};

void Animal::run(int i) {cout << "---Animal::run() " << endl;}
void Animal::speak() {cout << "---Animal::speak() " << endl;}

int main() {
    cout << "sizeof(Empty) : " << sizeof(Empty) << endl;        
    cout << "sizeof(Animal) : " << sizeof(Animal) << endl;     
    Animal dog;

    // cout << (void *)&dog << endl;
    // cout << &dog << endl;

    // void* dogptr = (void*)&dog;      // 由于不能对void*解引用，所以这个不行
    void** dogptr = reinterpret_cast<void**>(&dog);
    cout << dogptr << endl;             // 拿到dog的地址
    cout << *dogptr << endl;            // 拿到dog地址下的那个值    
    void** vtable = reinterpret_cast<void**>(*dogptr);      // 将&dog地址下的那个值转换成void**
    void (*speakptr) () = reinterpret_cast<void (*) ()>(vtable[0]); 
    speakptr();
    void (*runptr) (int) = reinterpret_cast<void (*) (int)>(vtable[1]);
    runptr(100);


    // cout << ptr << endl;
    
    // cout << *ptr << endl;

    // void *vptr = *reinterpret_cast<void**>(&dog);
    // void** vtable = reinterpret_cast<void**>(vptr);
    // void (*speak_fptr)() = reinterpret_cast<void (*)()>(vtable[0]);
    // speak_fptr();
    return 0;
}